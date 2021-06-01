/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      bring_up.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2021-03-24 09:00:00
 * @brief     person_detection flow.
 ******************************************************************************************
 */

/* Includes ---------------------------------------------------------- */
#include <stdbool.h>
#include "GOWIN_M1.h"
#include "ahb_convolution.h"
#include "bring_up.h"
#include "helper.h"
#include "command_responder.h"
#include "tflite_person_detection_parameters.h"

/* Macros ---------------------------------------------------------- */
#define IMG_SIZE 				(96)				//image size
#define USE_PSRAM									//use psram as convolution data buffer

#define TXT_OFFSET				0x0000B000			//HDMI output address

/* Functions ---------------------------------------------------------- */
//Initialization
void setup(void)
{
  SystemInit();				//Initializes system clock
  GPIOInit();				//Initializes GPIO
  I2CInit();				//Initializes I2C
}

//Convolution loop flow
void loop(void)
{
	AhbTFLiteConvolution_t core;
	
	uint32_t* im_buf = (uint32_t *) AHB2PERIPH_BASE;					//image input
	uint32_t* infer_num = (uint32_t *) (AHB2PERIPH_BASE + TXT_OFFSET);	//hdmi output
	uint32_t im_pix;
	int8_t image[2];

	//Initializes AHB convolution
	AhbTFLiteConvolutionInit(&core, AHB2PERIPH_BASE+0x0000A000);

	while(1)
	{
		AhbTFLiteConvolutionSetMemSelector(&core, 0);
		
		/* ---------------------------------------- Images Provider --------------------------------------*/
		//input image data
		for (int i=0; i< IMG_SIZE*IMG_SIZE/4; i++)
		{
			im_pix = (*(im_buf+i)) ^ 0x80808080; //Inverted MSB to turn Uint8 to Int8

			AhbTFLiteConvolutionLoadImagePixel(&core, (im_pix&0x000000ff)>> 0, 4*i+0);
			AhbTFLiteConvolutionLoadImagePixel(&core, (im_pix&0x0000ff00)>> 8, 4*i+1);	
			AhbTFLiteConvolutionLoadImagePixel(&core, (im_pix&0x00ff0000)>>16, 4*i+2);	
			AhbTFLiteConvolutionLoadImagePixel(&core, (im_pix&0xff000000)>>24, 4*i+3);
		}
		
		/* ------------------------------------- Convolution Inference ----------------------------------*/
		uint32_t wt_bias_mem_offset = 0;
		bool mem_selector = false;
		int wt_mem_offset = 0;
		int bias_mem_offset = 0;
		
		for(int i = 0; i < STAGES; i++)
		{
			uint32_t conv_result_size = CONV_OUT_CH[i] * CONV_OUT_DIM_HEIGHT[i] * CONV_OUT_DIM_WIDTH[i];
     
			core.depthwise = DEPTHWISE[i];
			core.conv_dim_im_in_x = CONV_IN_DIM_WIDTH[i];			//x <--> width
			core.conv_dim_im_in_y = CONV_IN_DIM_HEIGHT[i];		//y <--> height
			core.conv_ch_im_in = CONV_IN_CH[i];
			core.conv_ch_im_out = CONV_OUT_CH[i];
			core.conv_dim_kernel = CONV_KER_DIM_WIDTH[i];			//x = y
			core.conv_padding = CONV_PADDING_WIDTH[i];				//x = y
			core.conv_stride = CONV_STRIDE_WIDTH[i];					//x = y
			core.conv_dilation = DILATION_FACTOR_WIDTH[i];		//x = y
			core.conv_dim_im_out_x = CONV_OUT_DIM_WIDTH[i];
			core.conv_dim_im_out_y = CONV_OUT_DIM_HEIGHT[i];
			core.conv_batch = BATCH[i];
			core.conv_input_offset = IN_OFFSET[i];
			core.conv_filter_offset = WT_OFFSET[i];
			
			core.conv_output_offset = OUT_OFFSET[i];
			core.conv_activation_max = OUT_ACTIVATION_MAX[i];
			core.conv_activation_min = OUT_ACTIVATION_MIN[i];
			core.conv_depth_multiplier = DEPTH_MULTIPLIER[i];
			core.pool_ch_im_in = CONV_OUT_CH[i];
			core.pool_dim_im_in_x = CONV_OUT_DIM_WIDTH[i];
			core.pool_dim_im_in_y = CONV_OUT_DIM_HEIGHT[i];
			core.pool_dim_im_out_x = POOL_OUT_DIM_WIDTH[i];
			core.pool_dim_im_out_y = POOL_OUT_DIM_HEIGHT[i];
			core.pool_dim_kernel =  POOL_KER_DIM_WIDTH[i];	//x = y
			core.pool_padding = POOL_PADDING_WIDTH[i];			//x = y
			core.pool_stride = POOL_STRIDE_WIDTH[i];
			core.pool_en = POOL_EN[i];
			core.pool_mode =  POOL_MODE[i]; 

			int wt_size = CONV_KER_DIM_HEIGHT[i] * CONV_KER_DIM_WIDTH[i] * CONV_OUT_CH[i] * ((core.depthwise)?1:CONV_IN_CH[i]);
			int bias_size = 4*CONV_OUT_CH[i];
			int shift_size = 4*CONV_OUT_CH[i];
			int multiplier_size = 4*CONV_OUT_CH[i];
			core.conv_output_multiplier_offset = wt_size+bias_size;
			core.conv_output_shift_offset = wt_size+bias_size+multiplier_size;
			
			AhbTFLiteConvolutionSetMemSelector(&core, (uint8_t)mem_selector);
			AhbTFLiteConvolutionSetWtBiasMemOffsets(&core, wt_mem_offset, bias_mem_offset);
			AhbTFLiteConvolutionProcess(&core);

			if (i == 27)
			{
				#ifdef USE_PSRAM
				AhbTFLiteConvolutionUnloadImagePixel(&core, (uint16_t)0);
				for(int k = 1; k <= conv_result_size; k++)
				{
					image[k-1] = ((char)AhbTFLiteConvolutionUnloadImagePixel(&core, (uint16_t)k));
				}
      	  	  	#else
				for(int k = 0; k < conv_result_size; k++)
				{
					image[k] = ((char)AhbTFLiteConvolutionUnloadImagePixel(&core, (uint16_t)k));
				}
      	  	    #endif
			}
      
			wt_bias_mem_offset = wt_bias_mem_offset + wt_size + bias_size + shift_size + multiplier_size;
			wt_mem_offset += wt_size;
			bias_mem_offset += bias_size;

			if(!core.pool_en)
			{	
				mem_selector = !mem_selector;
			}
		}
		
		/* ---------------------------------------- Reshape --------------------------------------*/
		//TODO : 
		//Or not to do.
		
		/* ---------------------------------------- Softmax --------------------------------------*/
		//TODO : 
		//Or not to do.

		/* ---------------------------------------- Result --------------------------------------*/
		//image[0] : no person
		//image[1] : person
		//HDMI : person or empty
		//LEDx : as system indicator and inference indicator
		command_responder(image, infer_num);  
	}
}

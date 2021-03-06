/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      bring_up.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-25 09:00:00
 * @brief     clock_detection flow.
 ******************************************************************************************
 */

/* Includes ---------------------------------------------------------- */
#include <stdbool.h>
#include "GOWIN_M1.h"
#include "bring_up.h"
#include "helper.h"
#include "ahb_convolution.h"
#include "command_responder.h"
#include "tflite_clock_detection_parameters.h"

/* Macros ---------------------------------------------------------- */
#define IMG_SIZE 					(96)
#define SCORE_THRESHOLD 			(100)

#define NUMBER_OF_STRING			(10)
#define MAX_STRING_SIZE 			(12)

#define TXT_OFFSET					0x00C00000

/* Functions ---------------------------------------------------------- */
//Initialization
void setup(void)
{
    SystemInit();	//Initialize system clock
    UartInit();		//Initialize UART0
}

//Convolution loop flow
void loop(void)
{
	AhbTFLiteConvolution_t core;
	
	uint32_t* im_buf = (uint32_t *) AHB2PERIPH_BASE;
	uint32_t* infer_num = (uint32_t *) (AHB2PERIPH_BASE + TXT_OFFSET);
	int8_t im_pix;//an image pixel
	int8_t image[60];//result
	
	AhbTFLiteConvolutionInit(&core, 0x80800000);//Initialize convolution

	while(1)
	{
		int j=0;
		
		AhbTFLiteConvolutionSetMemSelector(&core, 0);
		
		/* ---------------------------------------- Images Provider --------------------------------------*/
		for (int i=0; i< IMG_SIZE*IMG_SIZE; i++)
		{
			im_pix = (int8_t)((*(im_buf+i)) - 128);//offset -128 for int8 input
			AhbTFLiteConvolutionLoadImagePixel(&core, im_pix, j++);
		}
		
		j=0;
		
		/* ---------------------------------------- Convolution --------------------------------------*/
		uint32_t wt_bias_mem_offset = 0;//0;
		bool mem_selector = false;
		
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
			
			AhbTFLiteConvolutionReadWtBiasFromFlash(&core, wt_bias_mem_offset, wt_size + bias_size + shift_size + multiplier_size);
			AhbTFLiteConvolutionSetMemSelector(&core, (uint8_t)mem_selector);
			AhbTFLiteConvolutionSetWtBiasMemOffsets(&core, 0, wt_size);
			AhbTFLiteConvolutionProcess(&core);

			for(int k = 0; k < conv_result_size; k++)
			{
				
				if(i==27)
				{
					image[k] = ((char)AhbTFLiteConvolutionUnloadImagePixel(&core, (uint16_t)k));
				}
			}
			
			wt_bias_mem_offset = wt_bias_mem_offset + wt_size + bias_size + shift_size + multiplier_size;

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
		//image[0]  : 00
		//image[1]  : 01
		//...
		//image[59] : 59
		//HDMI
		//UART0
		command_responder(image, infer_num);
	}
}

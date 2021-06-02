/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      bring_up.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-12-14 09:00:00
 * @brief     digit_detection flow.
 ******************************************************************************************
 */

/* Includes ---------------------------------------------------------- */
#include <stdbool.h>
#include "bring_up.h"
#include "helper.h"
#include "ahb_convolution.h"
#include "command_responder.h"
#include "tflite_digit_detection_parameters.h"

/* Macros ---------------------------------------------------------- */
#define IMG_SIZE 						(96)
#define TXT_OFFSET						0x00C00000

/* Definitions ---------------------------------------------------------- */
#define CMD_STOP						0x01
#define CMD_XY_UPDATE					0x09
#define CMD_BEGIN						0x00
#define CMD_XY_UPDATE1					0x01

uint8_t digit_num[5]={0};				//digit in instrument board
int32_t xs[5]={202,277,352,427,502};
int32_t xe[5]={298,373,448,523,598};
int32_t ys[5]={252,252,252,252,252};
int32_t ye[5]={348,348,348,348,348};

/* Variable ---------------------------------------------------------- */
static char* int2str(int num,char*str,int radix);
char buff[20];

/* Functions ---------------------------------------------------------- */
//Initialization
void setup(void)
{
    SystemInit();			//Initialize system clock
    UartInit();				//Initialize UART0
    GPIOInit();				//Initialize GPIO
    I2CInit();				//Initialize I2C
}

//Convolution loop flow
void loop(void)
{
	int digit_slice = 0;					//which digit image slice in 5-digits
	
	AhbTFLiteConvolution_t core;
	
	uint32_t* im_buf = (uint32_t *) AHB2PERIPH_BASE;
	uint32_t* infer_num = (uint32_t *) (AHB2PERIPH_BASE + TXT_OFFSET);
	int8_t im_pix;
	int8_t image[10];
	
	AhbTFLiteConvolutionInit(&core, 0x80800000);//Initialize convolution

	while(1)
	{
		int j = 0;
		uint8_t data = 0;
		
		//The first digit image, wait whole image is ready.
		//Stop whole image update from camera.
		if(0==digit_slice)
		{
			while(!AhbPhotoReady1(&core));
			AhbPhotoController(&core,CMD_STOP);
		}
		
		//Update digit location
		AhbPhotoController(&core,CMD_XY_UPDATE1);
		AhbPhotoWriteXY(&core,xs[digit_slice],xe[digit_slice],ys[digit_slice],ye[digit_slice]);
		AhbPhotoController(&core,CMD_XY_UPDATE);
		
		//Wait each digit image slice is ready. 
		while(!AhbPhotoReady(&core));
		
		//delay some ms, wait digit image is stable.
		delay_ms(200);

		AhbTFLiteConvolutionSetMemSelector(&core, 0);
		
		/* ---------------------------------------- Images Provider --------------------------------------*/
		for (int i=0; i< IMG_SIZE*IMG_SIZE; i++)
		{
			im_pix = (int8_t)((*(im_buf+i))-128);
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
		//image[0] : Zero
		//image[1] : One
		//image[2] : Two
		//image[3] : Three
		//image[4] : Four
		//image[5] : Five
		//image[6] : Six
		//image[7] : Seven
		//image[8] : Eight
		//image[9] : Nine
		//HDMI
		//LED
		command_responder(image, infer_num,&data);
		
		//Display whole digit
		digit_num[digit_slice] = data;
		
	  	if(digit_slice==4)
		{
			digit_slice=0;
			
			UART_SendString(UART0, "Current Digit Meter = ");
			UART_SendString(UART0, int2str(digit_num[0],buff,10));
			UART_SendString(UART0, int2str(digit_num[1],buff,10));
			UART_SendString(UART0, int2str(digit_num[2],buff,10));
			UART_SendString(UART0, int2str(digit_num[3],buff,10));
			UART_SendString(UART0, int2str(digit_num[4],buff,10));
			UART_SendString(UART0, "\r\n");
			
			AhbPhotoController(&core,CMD_BEGIN);
		}
		else
		{
			digit_slice++;
		}
		
		delay_ms(300);
	}
}

static char* int2str(int num,char*str,int radix)
{
	char index[]="0123456789ABCDEF";
	unsigned unum;
	int i=0,j,k;
	char temp;

	if(radix==10&&num<0)
	{
		unum=(unsigned)-num;
		str[i++]='-';
	}
	else
	{
		unum=(unsigned)num;
	}

	do
	{
		str[i++]=index[unum%(unsigned)radix];
		unum/=radix;
	}while(unum);
	str[i]='\0';

	if(str[0]=='-')
	{
		k=1;
	}
	else
	{
		k=0;
	}

	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}

	return str;
}

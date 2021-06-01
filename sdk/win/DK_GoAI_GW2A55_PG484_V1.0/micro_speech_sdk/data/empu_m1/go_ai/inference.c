/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      inference.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-11-16 09:00:00
 * @brief     inference flow.
 ******************************************************************************************
 */

/* Include ---------------------------------------------------------- */
#include <stdbool.h>
#include "inference.h"
#include "audio_provider.h"
#include "feature_provider.h"
#include "ahb_convolution.h"
#include "fully_connected.h"
#include "command_responder.h"
#include "recognize_commands.h"
#include "tflite_micro_speech_parameters.h"


/* Macro ---------------------------------------------------------- */
#define FEATURE_DATA_SIZE		DEF_CONV_IN_DIM_H * DEF_CONV_IN_DIM_W
#define CONV_OUTPUT_SIZE		DEF_CONV_OUT_CH * DEF_CONV_OUT_DIM_H * DEF_CONV_OUT_DIM_W

/* Declaractions ---------------------------------------------------------- */
static void convolution_params_init(AhbTFLiteConvolution_t* core);
static void fullyconnected_params_init(fully_connected_t* core);


/* Function ---------------------------------------------------------- */
//micro_speech loop flow
void loop(void)
{
	AhbTFLiteConvolution_t conv_core;							//Convolution core
	fully_connected_t fc_core;									//FullyConnected core
	
	int8_t feature_data[FEATURE_DATA_SIZE] = {0};				//Audio feature data
	int8_t conv_output_data[CONV_OUTPUT_SIZE] = {0};			//DepthwiseConv2D's output data, FullyConnected's input data
	int8_t fully_connected_output_data[DEF_OUTPUT_DEPTH] = {0};		//FullyConnected's output data
	
	int how_many_new_slices = 0;								//Audio spectrogram slices
	int32_t previous_time = 0;									//audio capture start time
	
	AhbTFLiteConvolutionInit(&conv_core, 0x80800000);			//Initialize convolution
	convolution_params_init(&conv_core);						//Initialize convolution parameters
	fullyconnected_params_init(&fc_core);						//Initialize fully_connected parameters

	while(1)
	{
		//************************* Front-end *****************************************//
		//-------------------------Audio Capture----------------------------------//
		//Audio capture in GoAI_55C board.
		audio_capture();
		
		//************************** Back-end *****************************************//
		//--------------------------------Audio Feature Provider-------------------------------//
		const int32_t current_time = LatestAudioTimestamp();
		feature_provider(previous_time, current_time, &how_many_new_slices, FEATURE_DATA_SIZE, feature_data);
		previous_time = current_time;
		 
		if(how_many_new_slices == 0)
		{
			return;
		}

		//-------------------------DepthwiseConv2D Layer-----------------------------//
		int j=0;
		AhbTFLiteConvolutionSetMemSelector(&conv_core, 0);
		
		//read audio input data to depthwise_conv2d
		for (int i=0; i< FEATURE_DATA_SIZE; i++)
		{
			AhbTFLiteConvolutionLoadImagePixel(&conv_core, feature_data[i], j++);
		}
		
		j=0;
		
		int wt_bias_mem_offset = 0;
		bool mem_selector = false;

		int wt_size = 1 * CONV_KER_DIM_H * CONV_KER_DIM_W * CONV_KER_CH;
		int bias_size = 4 * CONV_KER_CH;
		
		//read weight and bias
		//convolution
		AhbTFLiteConvolutionReadWtBiasFromFlash(&conv_core, wt_bias_mem_offset, wt_size + bias_size);
		AhbTFLiteConvolutionSetMemSelector(&conv_core, (uint8_t)mem_selector);
		AhbTFLiteConvolutionSetWtBiasMemOffsets(&conv_core, 0, wt_size);
		AhbTFLiteConvolutionProcess(&conv_core);

		//read depthwise_conv2d convolution result
		for(int k = 0; k < CONV_OUTPUT_SIZE; k++)
		{
			conv_output_data[k] = AhbTFLiteConvolutionUnloadImagePixel(&conv_core, (uint16_t)k);
		}
		
		//--------------------------------------FullyConnected Layer-----------------------------------------------//
		fully_connected_int8(&fc_core, FILTER_VAL, BIAS_DATA, conv_output_data, fully_connected_output_data);
		
		//--------------------------------------SoftMax Layer-----------------------------------------------//
		//TODO:
		//Not necessory.
		//Or not do.
		
		//--------------------------------------Recognize Commands-----------------------------------------------//
		const char* found_command;
		uint8_t score = 0;
		bool is_new_command = false;
		recognize_commands(fully_connected_output_data, current_time, &found_command, &score, &is_new_command);
		
		//--------------------------------------Result-----------------------------------------------//
		//Display LED 1-4.
		/*
		 * LED1 : Silence.
		 * LED2 : Unknown.
		 * LED3 : Yes.
		 * LED4 : No.
		 */
		command_responder(found_command, is_new_command);
	}
}

//initialize depthwise_conv2d/conv2d/average_pool2d parameters.
static void convolution_params_init(AhbTFLiteConvolution_t* core)
{
	core->depthwise = DEPTHWISE;
	core->conv_dim_im_in_x = CONV_IN_DIM_W;
	core->conv_dim_im_in_y = CONV_IN_DIM_H;
	core->conv_ch_im_in = CONV_IN_CH;
	core->conv_dim_kernel_x = CONV_KER_DIM_W;
	core->conv_dim_kernel_y = CONV_KER_DIM_H;
	core->conv_ch_im_kernel = CONV_KER_CH;
	core->conv_padding_x = CONV_PADDING_W;
	core->conv_padding_y = CONV_PADDING_H;
	core->conv_stride_x = CONV_STRIDE_W;
	core->conv_stride_y = CONV_STRIDE_H;
	core->conv_dilation_x = DILATION_FACTOR_W;
	core->conv_dilation_y = DILATION_FACTOR_H;
	core->conv_dim_im_out_x = CONV_OUT_DIM_W;
	core->conv_dim_im_out_y = CONV_OUT_DIM_H;
	core->conv_ch_im_out = CONV_OUT_CH;
	core->conv_batch = BATCH;
	core->conv_input_offset = IN_OFFSET;
	core->conv_filter_offset = WT_OFFSET[0];
	core->conv_output_offset = OUT_OFFSET;
	core->conv_output_shift1 = OUT_SHIFT[0];
	core->conv_output_shift2 = OUT_SHIFT[1];
	core->conv_output_shift3 = OUT_SHIFT[2];
	core->conv_output_shift4 = OUT_SHIFT[3];
	core->conv_output_shift5 = OUT_SHIFT[4];
	core->conv_output_shift6 = OUT_SHIFT[5];
	core->conv_output_shift7 = OUT_SHIFT[6];
	core->conv_output_shift8 = OUT_SHIFT[7];
	core->conv_output_multiplier1= OUT_MULTIPLIER[0];
	core->conv_output_multiplier2= OUT_MULTIPLIER[1];
	core->conv_output_multiplier3= OUT_MULTIPLIER[2];
	core->conv_output_multiplier4= OUT_MULTIPLIER[3];
	core->conv_output_multiplier5= OUT_MULTIPLIER[4];
	core->conv_output_multiplier6= OUT_MULTIPLIER[5];
	core->conv_output_multiplier7= OUT_MULTIPLIER[6];
	core->conv_output_multiplier8= OUT_MULTIPLIER[7];
	core->conv_activation_max = OUT_ACTIVATION_MAX;
	core->conv_activation_min = OUT_ACTIVATION_MIN;
	core->conv_depth_multiplier = DEPTH_MULTIPLIER;
		
	core->pool_ch_im_in = POOL_IN_CH;
	core->pool_dim_im_in_x = POOL_IN_DIM_W;
	core->pool_dim_im_in_y = POOL_IN_DIM_H;
	core->pool_ch_im_out = POOL_OUT_CH;
	core->pool_dim_im_out_x = POOL_OUT_DIM_W;
	core->pool_dim_im_out_y = POOL_OUT_DIM_H;
	core->pool_ch_im_kernel = POOL_KER_CH;
	core->pool_dim_kernel_x =  POOL_KER_DIM_W;
	core->pool_dim_kernel_y = POOL_KER_DIM_H;
	core->pool_padding_x = POOL_PADDING_W;
	core->pool_padding_y = POOL_PADDING_H;
	core->pool_stride_x = POOL_STRIDE_W;
	core->pool_stride_y = POOL_STRIDE_H;
	core->pool_en = POOL_EN;
	core->pool_mode = POOL_MODE;
}

//initialize fully_connected parameters.
static void fullyconnected_params_init(fully_connected_t* core)
{
	core->input_offset = INPUT_OFFSET;
	core->filter_offset = FILTER_OFFSET;
	core->output_offset = OUTPUT_OFFSET;
	core->output_multiplier = OUTPUT_MULTIPLIER;
	core->output_shift = OUTPUT_SHIFT;
	core->output_activation_min = OUTPUT_ACTIVATION_MIN;
	core->output_activation_max = OUTPUT_ACTIVATION_MAX;
	core->filter_dim_count = FILTER_DIM_COUNT;
	core->batches = BATCHES;
	core->output_depth = OUTPUT_DEPTH;
	core->accum_depth = ACCUM_DEPTH;
}

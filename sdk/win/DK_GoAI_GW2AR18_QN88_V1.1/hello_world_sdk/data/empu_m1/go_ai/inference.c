/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      inference.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-10 09:00:00
 * @brief     hello_world inference.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "inference.h"
#include "fully_connected.h"
#include "tflite_hello_world_parameters.h"

/* Functions ------------------------------------------------------------------*/
void inference(int8_t* input_val, int8_t* output_data)
{
	//--------------------------LAYER 1------------------------------//
	FullyConnected(INPUT_OFFSET1, FILTER_OFFSET1, OUTPUT_OFFSET1, OUTPUT_MULTIPLIER1, OUTPUT_SHIFT1, 
						OUTPUT_ACTIVATION_MIN1, OUTPUT_ACTIVATION_MAX1, FILTER_DIM_COUNT1, BATCHES1, 
						OUTPUT_DEPTH1, ACCUM_DEPTH1, input_val, FILTER_VAL1, BIAS_DATA1, output_data);
		
	for(int i=0; i<OUTPUT_DEPTH1; i++)
	{
		input_val[i] = output_data[i];
	}
		
	//--------------------------LAYER 2-------------------------------//
	FullyConnected(INPUT_OFFSET2, FILTER_OFFSET2, OUTPUT_OFFSET2, OUTPUT_MULTIPLIER2, OUTPUT_SHIFT2, 
						OUTPUT_ACTIVATION_MIN2, OUTPUT_ACTIVATION_MAX2, FILTER_DIM_COUNT2, BATCHES2, 
						OUTPUT_DEPTH2, ACCUM_DEPTH2, input_val, FILTER_VAL2, BIAS_DATA2, output_data);

	for(int i=0; i<OUTPUT_DEPTH2; i++)
	{
		input_val[i] = output_data[i];
	}
		
	//--------------------------LAYER 3-------------------------------//
	FullyConnected(INPUT_OFFSET3, FILTER_OFFSET3, OUTPUT_OFFSET3, OUTPUT_MULTIPLIER3, OUTPUT_SHIFT3, 
					OUTPUT_ACTIVATION_MIN3, OUTPUT_ACTIVATION_MAX3, FILTER_DIM_COUNT3, BATCHES3, 
					OUTPUT_DEPTH3, ACCUM_DEPTH3, input_val, FILTER_VAL3, BIAS_DATA3, output_data);
}

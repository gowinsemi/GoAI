/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			bring_up.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-18 09:00:00
 * @brief			inference.
 ******************************************************************************************
 */
 
/* Includes ------------------------------------------------------------------------ */
#include "bring_up.h"
#include "helper.h"
#include "conv.h"
#include "pooling.h"
#include "fully_connected.h"
#include "soft_max.h"
#include "accelerometer_handler.h"
#include "gesture_predictor.h"
#include "output_handler.h"
#include "tflite_magic_wand_parameters.h"
#include "gw1ns4c.h"

/* Macro ------------------------------------------------------------------------ */
#define INPUT_LENGTH						DEF_L1_CONV_INPUT_HEIGHT*DEF_L1_CONV_INPUT_WIDTH								//model's input data length
#define L1_CONV_OUTPUT_LENGTH				DEF_L1_CONV_OUTPUT_HEIGHT*DEF_L1_CONV_OUTPUT_WIDTH*DEF_L1_CONV_OUTPUT_DEPTH		//layer-1 conv2d's output data length
#define L2_MAXPOOL_OUTPUT_LENGTH			DEF_L2_MAXPOOL_OUTPUT_HEIGHT*DEF_L2_MAXPOOL_OUTPUT_WIDTH*DEF_L2_MAXPOOL_DEPTH	//layer-2 max_pool's output data length
#define L3_CONV_OUTPUT_LENGTH				DEF_L3_CONV_OUTPUT_HEIGHT*DEF_L3_CONV_OUTPUT_WIDTH*DEF_L3_CONV_OUTPUT_DEPTH		//layer-3 conv2d's output data length
#define L4_MAXPOOL_OUTPUT_LENGTH			DEF_L4_MAXPOOL_OUTPUT_HEIGHT*DEF_L4_MAXPOOL_OUTPUT_WIDTH*DEF_L4_MAXPOOL_DEPTH	//layer-4 max_pool's output data length
#define L6_FULLYCONNECTED_OUTPUT_LENGTH		DEF_L6_FULLYCONNECTED_OUTPUT_DEPTH												//layer-6 fully_connected's output data length
#define L7_FULLYCONNECTED_OUTPUT_LENGTH		DEF_L7_FULLYCONNECTED_OUTPUT_DEPTH												//layer-7 fully_connected's output data length
#define OUTPUT_LENGTH						DEF_L8_SOFTMAX_DEPTH

/* Declarations ------------------------------------------------------------------------ */
static void inference(float* input_data, float* output_data);

/* Functions ------------------------------------------------------------------------ */
//Initializes
void setup(void)
{
	SystemInit();			//Initializes System
	GPIOInit();				//Initializes GPIO
	I2C_Init(I2C,100);		//Initializes I2C
	setup_accelerometer();	//Initializes Accelerometer
}

//Inference
void loop(void)
{
	float input_data[INPUT_LENGTH] = {0.0};		//input accelerometer data
	float output_data[OUTPUT_LENGTH] = {0.0};	//output score data

	/* ----------------------------- Front-End Sample ---------------------------------*/
	//read accelerometer
	if(read_accelerometer(input_data, INPUT_LENGTH) == 0)
	{
		return;
	}
	
	/* ----------------------------- Back-End Inference ------------------------------ */
	//inference
	inference(input_data, output_data);
	
	/* ----------------------------- Gesture Predictor ------------------------------ */
	//gesture predictor
	int kind = predict_gesture(output_data);
	
	/* ----------------------------- Output Handler ------------------------------ */
	//0 : Wing
	//1 : Ring
	//2 : Slope
	//3 : Unknown
	output_handler(kind);
}

//Inference
static void inference(float* input_data, float* output_data)
{
  //////Variable Definition/////////
  conv_t conv_core;													//conv2d
  max_pool_t max_pool_core;											//max_pool
  fully_connected_t fully_connected_core;							//fully_connected
  soft_max_t soft_max_core;											//soft_max
	
  float temp_data[L1_CONV_OUTPUT_LENGTH] = {0.0};					//temp data
																	//max output length
  ////////////Layer 1//////////
  //Conv2D
  //setup parameters
  conv_core.batches = L1_CONV_BATCHES;
  conv_core.stride_width = L1_CONV_STRIDE_WIDTH;
  conv_core.stride_height = L1_CONV_STRIDE_HEIGHT;
  conv_core.dilation_width_factor = L1_CONV_DILATION_WIDTH_FACTOR;
  conv_core.dilation_height_factor = L1_CONV_DILATION_HEIGHT_FACTOR;
  conv_core.pad_width = L1_CONV_PAD_WIDTH;
  conv_core.pad_height = L1_CONV_PAD_HEIGHT;
  conv_core.input_width = L1_CONV_INPUT_WIDTH;
  conv_core.input_height = L1_CONV_INPUT_HEIGHT;
  conv_core.input_depth = L1_CONV_INPUT_DEPTH;
  conv_core.filter_width = L1_CONV_FILTER_WIDTH;
  conv_core.filter_height = L1_CONV_FILTER_HEIGHT;
  conv_core.filter_out_depth = L1_CONV_FILTER_OUT_DEPTH;
  conv_core.filter_in_depth = L1_CONV_FILTER_IN_DEPTH;
  conv_core.output_width = L1_CONV_OUTPUT_WIDTH;
  conv_core.output_height = L1_CONV_OUTPUT_HEIGHT;
  conv_core.output_depth = L1_CONV_OUTPUT_DEPTH;
  conv_core.output_activation_max = L1_CONV_OUTPUT_ACTIVATION_MAX;
  conv_core.output_activation_min = L1_CONV_OUTPUT_ACTIVATION_MIN;
	
  //Conv2D inference
  conv(&conv_core, input_data, L1_CONV_WT_DATA, L1_CONV_BIAS_DATA, temp_data);
	
  ////////////Layer 2////////////
  //MaxPool
  //setup parameters
  max_pool_core.batches = L2_MAXPOOL_BATCHES;
  max_pool_core.depth = L2_MAXPOOL_DEPTH;
  max_pool_core.filter_height = L2_MAXPOOL_FILTER_HEIGHT;
  max_pool_core.filter_width = L2_MAXPOOL_FILTER_WIDTH;
  max_pool_core.float_activation_max = L2_MAXPOOL_FLOAT_ACTIVATION_MAX;
  max_pool_core.float_activation_min = L2_MAXPOOL_FLOAT_ACTIVATION_MIN;
  max_pool_core.input_height = L2_MAXPOOL_INPUT_HEIGHT;
  max_pool_core.input_width = L2_MAXPOOL_INPUT_WIDTH;
  max_pool_core.output_height = L2_MAXPOOL_OUTPUT_HEIGHT;
  max_pool_core.output_width = L2_MAXPOOL_OUTPUT_WIDTH;
  max_pool_core.pad_height = L2_MAXPOOL_PAD_HEIGHT;
  max_pool_core.pad_width = L2_MAXPOOL_PAD_WIDTH;
  max_pool_core.stride_height = L2_MAXPOOL_STRIDE_HEIGHT;
  max_pool_core.stride_width = L2_MAXPOOL_STRIDE_WIDTH;

  //MaxPool inference
  max_pool(&max_pool_core, temp_data, input_data);
	
  ////////////Layer 3////////////
  //Conv2D
  //setup parameters
  conv_core.batches = L3_CONV_BATCHES;
  conv_core.stride_width = L3_CONV_STRIDE_WIDTH;
  conv_core.stride_height = L3_CONV_STRIDE_HEIGHT;
  conv_core.dilation_width_factor = L3_CONV_DILATION_WIDTH_FACTOR;
  conv_core.dilation_height_factor = L3_CONV_DILATION_HEIGHT_FACTOR;
  conv_core.pad_width = L3_CONV_PAD_WIDTH;
  conv_core.pad_height = L3_CONV_PAD_HEIGHT;
  conv_core.input_width = L3_CONV_INPUT_WIDTH;
  conv_core.input_height = L3_CONV_INPUT_HEIGHT;
  conv_core.input_depth = L3_CONV_INPUT_DEPTH;
  conv_core.filter_width = L3_CONV_FILTER_WIDTH;
  conv_core.filter_height = L3_CONV_FILTER_HEIGHT;
  conv_core.filter_out_depth = L3_CONV_FILTER_OUT_DEPTH;
  conv_core.filter_in_depth = L3_CONV_FILTER_IN_DEPTH;
  conv_core.output_width = L3_CONV_OUTPUT_WIDTH;
  conv_core.output_height = L3_CONV_OUTPUT_HEIGHT;
  conv_core.output_depth = L3_CONV_OUTPUT_DEPTH;
  conv_core.output_activation_max = L3_CONV_OUTPUT_ACTIVATION_MAX;
  conv_core.output_activation_min = L3_CONV_OUTPUT_ACTIVATION_MIN;
	
  //Conv2D inference
  conv(&conv_core, input_data, L3_CONV_WT_DATA, L3_CONV_BIAS_DATA, temp_data);
	
  ////////////Layer 4////////////
  //MaxPool
  //setup parameters
  max_pool_core.batches = L4_MAXPOOL_BATCHES;
  max_pool_core.depth = L4_MAXPOOL_DEPTH;
  max_pool_core.filter_height = L4_MAXPOOL_FILTER_HEIGHT;
  max_pool_core.filter_width = L4_MAXPOOL_FILTER_WIDTH;
  max_pool_core.float_activation_max = L4_MAXPOOL_FLOAT_ACTIVATION_MAX;
  max_pool_core.float_activation_min = L4_MAXPOOL_FLOAT_ACTIVATION_MIN;
  max_pool_core.input_height = L4_MAXPOOL_INPUT_HEIGHT;
  max_pool_core.input_width = L4_MAXPOOL_INPUT_WIDTH;
  max_pool_core.output_height = L4_MAXPOOL_OUTPUT_HEIGHT;
  max_pool_core.output_width = L4_MAXPOOL_OUTPUT_WIDTH;
  max_pool_core.pad_height = L4_MAXPOOL_PAD_HEIGHT;
  max_pool_core.pad_width = L4_MAXPOOL_PAD_WIDTH;
  max_pool_core.stride_height = L4_MAXPOOL_STRIDE_HEIGHT;
  max_pool_core.stride_width = L4_MAXPOOL_STRIDE_WIDTH;
	
  //MaxPool inference
  max_pool(&max_pool_core, temp_data, input_data);
	
  ////////////Layer 5//////////////////
  //Reshape
  //TBD
	
  /////////////Layer 6//////////////////
  //FullyConnected
  //setup parameters
  fully_connected_core.batches = L6_FULLYCONNECTED_BATCHES;
  fully_connected_core.output_depth = L6_FULLYCONNECTED_OUTPUT_DEPTH;
  fully_connected_core.accum_depth = L6_FULLYCONNECTED_ACCUM_DEPTH;
  fully_connected_core.output_activation_min = L6_FULLYCONNECTED_OUTPUT_ACTIVATION_MIN;
  fully_connected_core.output_activation_max = L6_FULLYCONNECTED_OUTPUT_ACTIVATION_MAX;
	
  //FullyConnected inference
  fully_connected(&fully_connected_core, input_data, L6_FULLYCONNECTED_WT_DATA, L6_FULLYCONNECTED_BIAS_DATA, temp_data);

  /////////////Layer 7//////////////////
  //FullyConnected
  //setup parameters
  fully_connected_core.batches = L7_FULLYCONNECTED_BATCHES;
  fully_connected_core.output_depth = L7_FULLYCONNECTED_OUTPUT_DEPTH;
  fully_connected_core.accum_depth = L7_FULLYCONNECTED_ACCUM_DEPTH;
  fully_connected_core.output_activation_min = L7_FULLYCONNECTED_OUTPUT_ACTIVATION_MIN;
  fully_connected_core.output_activation_max = L7_FULLYCONNECTED_OUTPUT_ACTIVATION_MAX;
	
  //FullyConnected inference
  fully_connected(&fully_connected_core, temp_data, L7_FULLYCONNECTED_WT_DATA, L7_FULLYCONNECTED_BIAS_DATA, input_data);
	
  ////////////Layer 8/////////////////
  //SoftMax
  //setup parameters
  soft_max_core.outer_size = L8_SOFTMAX_OUTER_SIZE;
  soft_max_core.depth = L8_SOFTMAX_DEPTH;
  soft_max_core.beta = L8_SOFTMAX_BETA;
	
  //SoftMax inference
  soft_max(&soft_max_core, input_data, output_data);
}

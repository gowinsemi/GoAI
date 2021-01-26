/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			fully_connected.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-15 09:00:00
 * @brief			fully connected.
 ******************************************************************************************
 */
 
#ifndef GOAI_FULLY_CONNECTED_H_
#define GOAI_FULLY_CONNECTED_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>

/* Definitions ------------------------------------------------------------------------ */
typedef struct
{
	float output_activation_min;
	float output_activation_max;
	uint8_t batches;
	uint8_t output_depth;
	uint8_t accum_depth;
}fully_connected_t;

/* Declarations ------------------------------------------------------------------------ */
void fully_connected(const fully_connected_t* core, const float* input_data, const float* weights_data, const float* bias_data, float* output_data);

#endif

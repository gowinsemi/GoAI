/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      fully_connected.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-28 09:00:00
 * @brief     fully connected.
 ******************************************************************************************
 */

#ifndef FULLY_CONNECTED_H_
#define FULLY_CONNECTED_H_

/* Includes ------------------------------------------------------------------ */
#include <stdint.h>

/* Definitions --------------------------------------------------------------- */
typedef struct
{
	int32_t input_offset;
	int32_t filter_offset;
	int32_t output_offset;
	int32_t output_multiplier;
	int output_shift;
	int32_t output_activation_min;
	int32_t output_activation_max;
	int filter_dim_count;
	int batches;
	int output_depth;
	int accum_depth;
}fully_connected_t;

/* Declarations --------------------------------------------------------------- */
//int8_t model
void fully_connected_int8(fully_connected_t* fc,const int8_t* filter_data, const int32_t* bias_data,const int8_t* input_data,  int8_t* output_data);

#endif

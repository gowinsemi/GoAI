/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      fully_connected.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-10 09:00:00
 * @brief     fully connected.
 ******************************************************************************************
 */

#ifndef FULLY_CONNECTED_H_
#define FULLY_CONNECTED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Declarations ------------------------------------------------------------------*/
void FullyConnected	(const int32_t input_offset, const int32_t filter_offset, const int32_t output_offset, const int32_t output_multiplier, 
						const int output_shift, const int32_t output_activation_min, const int32_t output_activation_max, const int filter_dim_count, 
						const int batches, const int output_depth, const int accum_depth, const int8_t* input_data, 
						const int8_t* filter_data, const int32_t* bias_data, int8_t* output_data );

#endif

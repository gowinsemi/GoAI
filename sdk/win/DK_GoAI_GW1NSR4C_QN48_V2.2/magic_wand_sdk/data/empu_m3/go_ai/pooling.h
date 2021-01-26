/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			pooling.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-14 09:00:00
 * @brief			max pooling.
 ******************************************************************************************
 */
 
#ifndef GOAI_POOLING_H_
#define GOAI_POOLING_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>

/* Definitions ------------------------------------------------------------------------ */
typedef struct
{
  uint8_t batches;
	uint8_t depth;//input/output depth
	uint8_t input_height;
	uint8_t input_width;
	uint8_t output_height;
	uint8_t output_width;
	uint8_t stride_height;
	uint8_t stride_width;
	uint8_t filter_height;
	uint8_t filter_width;
	uint8_t pad_height;
	uint8_t pad_width;
	float float_activation_min;
	float float_activation_max;
}max_pool_t;

/* Declarations ------------------------------------------------------------------------ */
void max_pool(const max_pool_t* core, const float* input_data, float* output_data);

#endif

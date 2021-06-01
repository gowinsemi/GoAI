/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			conv.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-12 09:00:00
 * @brief			convolution.
 ******************************************************************************************
 */
 
#ifndef GOAI_CONV_H_
#define GOAI_CONV_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>

/* Definitions ------------------------------------------------------------------------ */
typedef struct
{
  uint8_t batches;
  uint8_t stride_width;
  uint8_t stride_height;
  uint8_t dilation_width_factor;
  uint8_t dilation_height_factor;
  uint8_t pad_width;
  uint8_t pad_height;
  
  uint8_t input_width;
  uint8_t input_height;
  uint8_t input_depth;
  uint8_t filter_width;
  uint8_t filter_height;
  uint8_t filter_out_depth;
  uint8_t filter_in_depth;
  uint8_t output_width;
  uint8_t output_height;
  uint8_t output_depth;
  
  float output_activation_max;
  float output_activation_min;
}conv_t;

/* Declarations ------------------------------------------------------------------------ */
void conv(const conv_t* core, const float* input_data, const float* filter_data, const float* bias_data, float* output_data);

#endif

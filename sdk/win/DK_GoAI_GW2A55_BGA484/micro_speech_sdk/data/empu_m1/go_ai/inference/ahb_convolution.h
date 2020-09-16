/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      ahb_convolution.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-06 09:00:00
 * @brief     AHB convolution interface.
 ******************************************************************************************
 */

#ifndef AHB_CONVOLUTION_H
#define AHB_CONVOLUTION_H

/* Include ------------------------------------------------------ */
#include <stdint.h>

/* Definition ------------------------------------------------------ */
typedef struct{
    uint32_t base_addr;
	
		uint8_t depthwise;
	  uint16_t conv_dim_im_in_x;
	  uint16_t conv_dim_im_in_y;
	  uint16_t conv_dim_im_out_x;
	  uint16_t conv_dim_im_out_y;
		uint16_t conv_dim_kernel_x;
	  uint16_t conv_dim_kernel_y;
	  uint16_t conv_ch_im_in;
	  uint16_t conv_ch_im_out;
	  uint16_t conv_ch_im_kernel;
	  uint16_t conv_stride_x;
	  uint16_t conv_stride_y;
	  uint16_t conv_padding_x;
	  uint16_t conv_padding_y;
	  uint16_t conv_dilation_x;
	  uint16_t conv_dilation_y;
    uint16_t conv_depth_multiplier;
	  uint16_t conv_batch;
    int32_t conv_input_offset;
    int32_t conv_filter_offset;
    int32_t conv_output_offset;
    int32_t conv_output_multiplier1;
		int32_t conv_output_multiplier2;
		int32_t conv_output_multiplier3;
		int32_t conv_output_multiplier4;
		int32_t conv_output_multiplier5;
		int32_t conv_output_multiplier6;
		int32_t conv_output_multiplier7;
		int32_t conv_output_multiplier8;
    int32_t conv_output_shift1;
		int32_t conv_output_shift2;
		int32_t conv_output_shift3;
		int32_t conv_output_shift4;
		int32_t conv_output_shift5;
		int32_t conv_output_shift6;
		int32_t conv_output_shift7;
		int32_t conv_output_shift8;
    int32_t conv_activation_max;
    int32_t conv_activation_min;
    uint8_t pool_en;
	  uint8_t pool_mode;
	  uint16_t pool_dim_im_in_x;
	  uint16_t pool_dim_im_in_y;
	  uint16_t pool_dim_im_out_x;
	  uint16_t pool_dim_im_out_y;
	  uint16_t pool_dim_kernel_x;
		uint16_t pool_dim_kernel_y;
	  uint16_t pool_ch_im_in;
		uint16_t pool_ch_im_out;
    uint16_t pool_ch_im_kernel;
	  uint16_t pool_stride_x;
		uint16_t pool_stride_y;
	  uint16_t pool_padding_x;
		uint16_t pool_padding_y;
}AhbTFLiteConvolution_t;

/* Declarations ------------------------------------------------------ */
void AhbTFLiteConvolutionInit(AhbTFLiteConvolution_t* core, uint32_t baseaddr);
void AhbTFLiteConvolutionLoadWtMem(AhbTFLiteConvolution_t* core, int8_t* data, uint32_t size, uint32_t offset);
void AhbTFLiteConvolutionLoadBiasMem(AhbTFLiteConvolution_t* core, int32_t* data, uint32_t size, uint32_t offset);
void AhbTFLiteConvolutionSetWtBiasMemOffsets(AhbTFLiteConvolution_t* core, uint32_t wt_offset, uint32_t bias_offset);
void AhbTFLiteConvolutionSetMemSelector(AhbTFLiteConvolution_t* core, uint8_t selector);
void AhbTFLiteConvolutionLoadImage(AhbTFLiteConvolution_t* core, int8_t* image, uint16_t size);
void AhbTFLiteConvolutionLoadImagePixel(AhbTFLiteConvolution_t* core, int8_t pixel, uint16_t address);
int8_t AhbTFLiteConvolutionUnloadImagePixel(AhbTFLiteConvolution_t* core, uint16_t address);
void AhbTFLiteConvolutionProcess(AhbTFLiteConvolution_t* core);
void AhbTFLiteConvolutionUnloadImage(AhbTFLiteConvolution_t* core, int8_t* image, uint16_t size);
void AhbTFLiteConvolutionReadWtBiasFromFlash(AhbTFLiteConvolution_t* core, uint32_t addr, uint32_t size);

#endif

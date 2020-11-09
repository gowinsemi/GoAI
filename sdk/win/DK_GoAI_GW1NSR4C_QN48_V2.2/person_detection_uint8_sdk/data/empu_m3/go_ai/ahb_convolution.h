/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			ahb_convolution.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-09-28 09:00:00
 * @brief			AHB convolution.
 ******************************************************************************************
 */

#ifndef AHB_CONVOLUTION_H
#define AHB_CONVOLUTION_H

/* Includes ------------------------------------------------------------------ */
#include <stdint.h>

/* Variables ------------------------------------------------------------------ */
typedef struct{
    uint32_t base_addr;
	  uint16_t conv_dim_im_in_x;
	  uint16_t conv_dim_im_in_y;
	  uint16_t conv_dim_im_out_x;
	  uint16_t conv_dim_im_out_y;
	  uint16_t conv_ch_im_in;
	  uint16_t conv_ch_im_out;
	  uint16_t conv_dim_kernel;
	  uint16_t conv_stride;
	  uint16_t conv_padding;
	  uint16_t conv_dilation;
    uint16_t conv_depth_multiplier;
	  uint16_t conv_batch;
      
    int32_t conv_input_offset;
    int32_t conv_filter_offset;
    int32_t conv_output_offset;
    int32_t conv_output_multiplier;
    int32_t conv_output_shift;
    int32_t conv_activation_max;
    int32_t conv_activation_min;
      
	  uint16_t pool_dim_im_in_x;
	  uint16_t pool_dim_im_in_y;
	  uint16_t pool_dim_im_out_x;
	  uint16_t pool_dim_im_out_y;
	  uint16_t pool_ch_im_in;
	  uint16_t pool_dim_kernel;
	  uint16_t pool_stride;
	  uint16_t pool_padding;
	  uint8_t depthwise;
	  uint8_t pool_en;
	  uint8_t pool_mode;
}AhbTFLiteConvolution_t;

/* Declarations ------------------------------------------------------------------ */
void AhbTFLiteConvolutionInit(AhbTFLiteConvolution_t* core, uint32_t baseaddr);
void AhbTFLiteConvolutionLoadWtMem(AhbTFLiteConvolution_t* core, int8_t* data, uint32_t size, uint32_t offset);
void AhbTFLiteConvolutionLoadBiasMem(AhbTFLiteConvolution_t* core, int32_t* data, uint32_t size, uint32_t offset);
void AhbTFLiteConvolutionSetWtBiasMemOffsets(AhbTFLiteConvolution_t* core, uint32_t wt_offset, uint32_t bias_offset);
void AhbTFLiteConvolutionSetMemSelector(AhbTFLiteConvolution_t* core, uint8_t selector);
void AhbTFLiteConvolutionSetCamSelector(AhbTFLiteConvolution_t* core, uint8_t selector);
void AhbTFLiteConvolutionLoadImage(AhbTFLiteConvolution_t* core, int8_t* image, uint16_t size);
void AhbTFLiteConvolutionLoadImagePixel(AhbTFLiteConvolution_t* core, uint8_t pixel, uint16_t address);
uint8_t AhbTFLiteConvolutionUnloadImagePixel(AhbTFLiteConvolution_t* core, uint16_t address);
void AhbTFLiteConvolutionProcess(AhbTFLiteConvolution_t* core);
void AhbTFLiteConvolutionUnloadImage(AhbTFLiteConvolution_t* core, int8_t* image, uint16_t size);
void AhbTFLiteConvolutionReadWtBiasFromFlash(AhbTFLiteConvolution_t* core, uint32_t addr, uint32_t size);

#endif

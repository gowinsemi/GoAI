
//GowinSemiconductor Technology Co.,Ltd GoAI2.0:Gender Detection!
//Auto Generate Tflite Model Gender Detection Parameters Header File!

#ifndef TFLITE_GENDER_DETECTION_PARAMETERS_H_
#define TFLITE_GENDER_DETECTION_PARAMETERS_H_

/* Includes ------------------------------------------------*/
#include <stdint.h>

/* Parameters ------------------------------------------------*/
//DepthwiseConv2D/Conv2D/AreragePool2D Layers
#define STAGES 28

const uint8_t DEPTHWISE [STAGES] = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0};
const uint16_t DILATION_FACTOR_HEIGHT [STAGES] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const uint16_t DILATION_FACTOR_WIDTH [STAGES] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const uint16_t DEPTH_MULTIPLIER [STAGES] = {8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const int32_t OUT_ACTIVATION_MIN [STAGES] = {-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128};
const int32_t OUT_ACTIVATION_MAX [STAGES] = {127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127};
const int32_t IN_OFFSET [STAGES] = {1,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};
const int32_t WT_OFFSET [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const int32_t OUT_OFFSET [STAGES] = {-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,15};
const int32_t OUT_MULTIPLIER_OFFSET [STAGES] = {32,32,64,64,128,128,128,128,256,256,256,256,512,512,512,512,512,512,512,512,512,512,512,512,1024,1024,1024,12};
const int32_t OUT_SHIFT_OFFSET [STAGES] = {32,32,64,64,128,128,128,128,256,256,256,256,512,512,512,512,512,512,512,512,512,512,512,512,1024,1024,1024,12};
const uint16_t BATCH [STAGES] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const uint16_t CONV_PADDING_HEIGHT [STAGES] = {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0};
const uint16_t CONV_PADDING_WIDTH [STAGES] = {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0};
const uint16_t CONV_STRIDE_HEIGHT [STAGES] = {2,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1};
const uint16_t CONV_STRIDE_WIDTH [STAGES] = {2,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1};
const uint16_t CONV_IN_CH [STAGES] = {1,8,8,16,16,32,32,32,32,64,64,64,64,128,128,128,128,128,128,128,128,128,128,128,128,256,256,256};
const uint16_t CONV_IN_DIM_HEIGHT [STAGES] = {96,48,48,48,24,24,24,24,12,12,12,12,6,6,6,6,6,6,6,6,6,6,6,6,3,3,3,1};
const uint16_t CONV_IN_DIM_WIDTH [STAGES] = {96,48,48,48,24,24,24,24,12,12,12,12,6,6,6,6,6,6,6,6,6,6,6,6,3,3,3,1};
const uint16_t CONV_OUT_CH [STAGES] = {8,8,16,16,32,32,32,32,64,64,64,64,128,128,128,128,128,128,128,128,128,128,128,128,256,256,256,3};
const uint16_t CONV_OUT_DIM_HEIGHT [STAGES] = {48,48,48,24,24,24,24,12,12,12,12,6,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,1};
const uint16_t CONV_OUT_DIM_WIDTH [STAGES] = {48,48,48,24,24,24,24,12,12,12,12,6,6,6,6,6,6,6,6,6,6,6,6,3,3,3,3,1};
const uint16_t CONV_KER_CH [STAGES] = {8,8,16,16,32,32,32,32,64,64,64,64,128,128,128,128,128,128,128,128,128,128,128,128,256,256,256,3};
const uint16_t CONV_KER_DIM_HEIGHT [STAGES] = {3,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,1};
const uint16_t CONV_KER_DIM_WIDTH [STAGES] = {3,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,1};
const uint8_t POOL_EN [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
const uint8_t POOL_MODE [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
const uint16_t POOL_IN_CH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,256,0};
const uint16_t POOL_IN_DIM_HEIGHT [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0};
const uint16_t POOL_IN_DIM_WIDTH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0};
const uint16_t POOL_OUT_CH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,256,0};
const uint16_t POOL_OUT_DIM_HEIGHT [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
const uint16_t POOL_OUT_DIM_WIDTH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
const uint16_t POOL_KER_DIM_HEIGHT [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0};
const uint16_t POOL_KER_DIM_WIDTH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0};
const uint16_t POOL_PADDING_HEIGHT [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t POOL_PADDING_WIDTH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t POOL_STRIDE_HEIGHT [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0};
const uint16_t POOL_STRIDE_WIDTH [STAGES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0};

#endif        /* TFLITE_GENDER_DETECTION_PARAMETERS_H_ */

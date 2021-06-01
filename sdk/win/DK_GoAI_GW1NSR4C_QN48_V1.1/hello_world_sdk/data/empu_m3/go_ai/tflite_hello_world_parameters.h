
//GowinSemiconductor Technology Co.,Ltd GoAI2.0:Hello World!
//Auto Generate Tflite Model Hello World Parameters Header File!

#ifndef TFLITE_HELLO_WORLD_PARAMETERS_H_
#define TFLITE_HELLO_WORLD_PARAMETERS_H_

/* Includes ------------------------------------------------*/
#include <stdint.h>

/* Macros ------------------------------------------------*/
#define DEF_OUTPUT_DEPTH1 16
#define DEF_ACCUM_DEPTH1 1
#define DEF_OUTPUT_DEPTH2 16
#define DEF_ACCUM_DEPTH2 16
#define DEF_OUTPUT_DEPTH3 1
#define DEF_ACCUM_DEPTH3 16

/* Parameters ------------------------------------------------*/
//layer 1
const int32_t INPUT_OFFSET1 = 128;
const int32_t FILTER_OFFSET1 = 0;
const int32_t OUTPUT_OFFSET1 = -128;
const int32_t OUTPUT_MULTIPLIER1 = 1195127966;
const int OUTPUT_SHIFT1 = -6;
const int32_t OUTPUT_ACTIVATION_MIN1 = -128;
const int32_t OUTPUT_ACTIVATION_MAX1 = 127;
const int FILTER_DIM_COUNT1 = 2;
const int BATCHES1 = 1;
const int OUTPUT_DEPTH1 = 16;
const int ACCUM_DEPTH1 = 1;
const int8_t FILTER_VAL1[DEF_OUTPUT_DEPTH1*DEF_ACCUM_DEPTH1] = {115,28,17,-31,12,-127,-91,67,-2,-43,-43,-78,96,119,25,-33};
const int32_t BIAS_DATA1[DEF_OUTPUT_DEPTH1] = {1,2897,-2489,0,3100,0,0,1435,0,0,8423,0,1938,-2828,-4011,0};

//layer 2
const int32_t INPUT_OFFSET2 = 128;
const int32_t FILTER_OFFSET2 = 0;
const int32_t OUTPUT_OFFSET2 = -128;
const int32_t OUTPUT_MULTIPLIER2 = 1804161650;
const int OUTPUT_SHIFT2 = -5;
const int32_t OUTPUT_ACTIVATION_MIN2 = -128;
const int32_t OUTPUT_ACTIVATION_MAX2 = 127;
const int FILTER_DIM_COUNT2 = 2;
const int BATCHES2 = 1;
const int OUTPUT_DEPTH2 = 16;
const int ACCUM_DEPTH2 = 16;
const int8_t FILTER_VAL2[DEF_OUTPUT_DEPTH2*DEF_ACCUM_DEPTH2] = {-18,-4,0,-20,5,22,-17,-20,-26,-8,3,1,0,-6,-8,-11,-38,-21,39,20,-17,-34,-30,-38,-16,-33,50,6,1,-26,-18,-7,0,22,7,-32,-2,-1,-23,5,-25,-17,-127,27,24,-22,-54,1,15,0,-37,-9,14,-20,18,30,4,19,-78,-25,-3,6,-69,-32,12,-20,-16,-33,-21,-9,5,38,25,-28,112,26,-22,30,52,-33,25,-13,-15,25,14,3,27,-31,-34,19,-10,25,-1,-10,26,23,-15,28,-37,26,26,32,-26,25,-11,-1,-105,11,0,0,-50,-33,13,-9,21,-28,-19,-4,13,-23,-5,-20,92,-4,29,2,88,-29,-32,-12,21,-20,-7,0,19,5,-20,12,28,20,12,-23,10,-12,24,0,-41,5,39,2,21,-22,-22,2,-101,0,12,-6,-23,-22,-2,1,20,-3,11,2,-16,-17,6,-18,1,13,6,-25,-9,17,-11,10,-7,-15,35,-1,13,-14,-20,17,38,29,-14,-22,40,24,-32,-5,-13,-12,5,28,29,-5,-3,30,-4,17,-24,6,9,3,18,-14,53,-5,-35,27,-7,-17,-13,-25,111,12,29,0,67,-3,13,-15,10,25,26,-6,-32,24,30,19,55,28,18,-20,58,12,-74,-53,-26,19,-9,-21,-15,5,27,-6,25,-27,-20,-49,12,-12};
const int32_t BIAS_DATA2[DEF_OUTPUT_DEPTH2] = {0,1276,2719,1637,-1987,0,2795,-2001,1256,2593,-442,1224,0,-2141,-1752,1434};

//layer 3
const int32_t INPUT_OFFSET3 = 128;
const int32_t FILTER_OFFSET3 = 0;
const int32_t OUTPUT_OFFSET3 = 2;
const int32_t OUTPUT_MULTIPLIER3 = 1601824118;
const int OUTPUT_SHIFT3 = -7;
const int32_t OUTPUT_ACTIVATION_MIN3 = -128;
const int32_t OUTPUT_ACTIVATION_MAX3 = 127;
const int FILTER_DIM_COUNT3 = 2;
const int BATCHES3 = 1;
const int OUTPUT_DEPTH3 = 1;
const int ACCUM_DEPTH3 = 16;
const int8_t FILTER_VAL3[DEF_OUTPUT_DEPTH3*DEF_ACCUM_DEPTH3] = {33,-94,-116,-55,95,29,-50,65,-97,-51,32,-79,-33,83,47,-127};
const int32_t BIAS_DATA3[DEF_OUTPUT_DEPTH3] = {-4382};

#endif        /* TFLITE_HELLO_WORLD_PARAMETERS_H_ */

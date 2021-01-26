/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			common.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-12 09:00:00
 * @brief			public.
 ******************************************************************************************
 */

#ifndef GOAI_COMMON_H_
#define GOAI_COMMON_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>

/* Declarations ------------------------------------------------------------------------ */
int Offset(const int h, const int w, const int d, int i0, int i1, int i2, int i3);
float ActivationFunctionWithMinMax(float x, float output_activation_min, float output_activation_max);
float float_max(float a, float b);
float float_min(float a, float b);
int int_max(int a, int b);
int int_min(int a, int b);

#endif

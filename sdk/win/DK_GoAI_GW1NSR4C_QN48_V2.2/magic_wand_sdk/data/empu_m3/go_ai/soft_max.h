/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			soft_max.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-14 09:00:00
 * @brief			soft max.
 ******************************************************************************************
 */
 
#ifndef GOAI_SOFT_MAX_H_
#define GOAI_SOFT_MAX_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>

/* Definitions ------------------------------------------------------------------------ */
typedef struct
{
	uint8_t outer_size;
	uint8_t depth;
	float beta;
}soft_max_t;

/* Declarations ------------------------------------------------------------------------ */
void soft_max(const soft_max_t* core, const float* input_data, float* output_data);

#endif

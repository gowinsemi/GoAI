/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			accelerometer_handler.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-12 09:00:00
 * @brief			accelerometer handler.
 ******************************************************************************************
 */

#ifndef GOAI_ACCELEROMETER_HANDLER_H_
#define GOAI_ACCELEROMETER_HANDLER_H_

/* Includes ------------------------------------------------------------------------ */
#include <stdint.h>
#include <stdbool.h>

/* Declarations ------------------------------------------------------------------------ */
void setup_accelerometer(void);
bool read_accelerometer(float* input, int length);

#endif

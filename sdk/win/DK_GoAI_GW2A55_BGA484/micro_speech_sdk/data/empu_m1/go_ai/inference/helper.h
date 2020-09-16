/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-06 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

#ifndef HELPER_H_
#define HELPER_H_

/* Includes --------------------------------------------------------------- */
#include <stdint.h>

/* Definitions --------------------------------------------------------------- */

#define SYSTEM_CLOCK (48000000)		//system clock
#define MICRO_STATUS 4						//micro_speech result

/* Declarations --------------------------------------------------------------- */
void setup(void);									//Initialization
void delay_ms(uint32_t delay_ms);	//Delay ms

extern const char* micro_speech_lable[MICRO_STATUS];	//standard score

#endif

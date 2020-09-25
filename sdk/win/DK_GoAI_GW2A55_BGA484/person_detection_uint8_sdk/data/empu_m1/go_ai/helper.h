/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-20 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

#ifndef HELPER_H_
#define HELPER_H_

/* Macros ----------------------------------------------------------- */
#define SYSTEM_CLOCK (48000000)	//Define new system clock

/* Declarations ----------------------------------------------------------- */
void SystemClockInit(void);		//Initialize system clock
void UartInit(void);			//Initialize UART0
void GPIOInit(void);			//Initialize GPIO

#endif

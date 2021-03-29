/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-25 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

#ifndef HELPER_H_
#define HELPER_H_

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"

/* Declarations -------------------------------------------------------- */
void SystemClockInit(void);							//Initialize system clock
void UartInit(void);										//Initialize UART0
void GPIOInit(void);										//Initialize GPIO
void I2CInit(void);											//Initialized I2C
void delay_ms(__IO uint32_t delay_ms);	//Delay ms

#endif

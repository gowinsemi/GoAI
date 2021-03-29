/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-11-26 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

#ifndef HELPER_H_
#define HELPER_H_

/* Declarations -------------------------------------------------------- */
void SystemClockInit(void);		//Initialize system clock
void UartInit(void);					//Initialize UART0
void GPIOInit(void);					//Initialize GPIO

#endif

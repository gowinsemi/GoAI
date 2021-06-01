/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-16 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "helper.h"
#include "GOWIN_M1.h"

/* Functions ------------------------------------------------------------------*/
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitType;
	
	GPIO_InitType.GPIO_Pin = GPIO_Pin_0 |
	                         GPIO_Pin_1 |
	                         GPIO_Pin_2 |
	                         GPIO_Pin_3 |
	                         GPIO_Pin_4 |
	                         GPIO_Pin_5;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0,&GPIO_InitType);

	GPIO_WriteBits(GPIO0,0x3F);//light : low level
}

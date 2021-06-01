/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			helper.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-12-01 09:00:00
 * @brief			initialization.
 ******************************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "helper.h"
#include "GOWIN_M1.h"

/* Declarations ------------------------------------------------------------------*/
static void delay_ms(__IO uint32_t delay_ms);

/* Functions ------------------------------------------------------------------*/
//Initializes GPIO
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

	GPIO_SetBit(GPIO0, GPIO_Pin_0);	//initializes LEDx off
	GPIO_SetBit(GPIO0, GPIO_Pin_1);
	GPIO_SetBit(GPIO0, GPIO_Pin_2);
	GPIO_SetBit(GPIO0, GPIO_Pin_3);
	GPIO_SetBit(GPIO0, GPIO_Pin_4);
	GPIO_SetBit(GPIO0, GPIO_Pin_5);
	
	delay_ms(100);					//delay 100ms until system is stable
}

//delay ms
static void delay_ms(__IO uint32_t delay_ms)
{
  for(delay_ms=delay_ms*8500; delay_ms != 0; delay_ms--);
}

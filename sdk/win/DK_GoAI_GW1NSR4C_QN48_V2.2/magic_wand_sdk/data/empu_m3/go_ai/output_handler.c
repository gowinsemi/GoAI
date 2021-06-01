/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			output_handler.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-15 09:00:00
 * @brief			output handler.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------------ */
#include "output_handler.h"
#include "gw1ns4c.h"

/* Macros ------------------------------------------------------------------------ */
#define BLINK_DLY 100

/* Declarations ------------------------------------------------------------------------ */
static void Delay_ms(__IO uint32_t delay_ms);

/* Functions ------------------------------------------------------------------------ */
//0 : Wing
//1 : Ring
//2 : Slope
//3 : Unknown
void output_handler(int kind)
{
	if(kind == 0)
	{
		//Wing
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
	}
	else if(kind == 1)
	{
		//Ring
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
	}
	else if(kind == 2)
	{
		//Slope
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		Delay_ms(BLINK_DLY);
	}
	else if(kind == 3)
	{
		//Unknown
	}
	
	GPIO_ResetBit(GPIO0, GPIO_Pin_0);
}

//delay ms
static void Delay_ms(__IO uint32_t delay_ms)
{
	for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}

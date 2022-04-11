/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-12-01 09:00:00
 * @brief			command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include "command_responder.h"

/* Macros ------------------------------------------------------------------------ */
#define BLINK_DLY 100

/* Declarations ---------------------------------------------------------- */
static uint8_t max(int8_t* image, int8_t length);
static void delay_ms(__IO uint32_t delay_ms);

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image)
{
	//LED2 : GoAI running indicator

	//image[0] : 0
	//...
	//image[59] : 59
	uint8_t digit = max(image, 60);

	//LED2 : GoAI running indicator
	for(uint8_t i = 0;i < (digit+1);i++)
	{
		GPIO_SetBit(GPIO0, GPIO_Pin_0);		//on
		delay_ms(BLINK_DLY);
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);	//off
		delay_ms(BLINK_DLY);
	}
}

//find out the maximum digit in image[length]
static uint8_t max(int8_t* image, int8_t length)
{
	int8_t max = image[0];
	uint8_t index = 0;
	
	for(uint8_t i = 1;i < length;i++)
	{
		if(max < image[i])
		{
			max = image[i];
			index = i;
		}
	}
	
	return index;
}

//delay ms
static void delay_ms(__IO uint32_t delay_ms)
{
	for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}

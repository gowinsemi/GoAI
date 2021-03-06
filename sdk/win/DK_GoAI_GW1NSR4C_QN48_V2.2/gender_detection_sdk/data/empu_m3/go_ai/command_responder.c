/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author			Embedded Development Team
 * @version			V1.0.0
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
static void Delay_ms(__IO uint32_t delay_ms);

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image)
{
	/*
	 * image[0] : unknown
	 * image[1] : female
	 * image[2] : male
	 */
	uint8_t res = max(image, 3);

	switch(res)
	{
		case 0:
			//unknown
			//LED2 off
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			break;
		case 1:
			//female
			//LED2 on 1 times
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			break;
		case 2:
			//male
			//LED2 on 2 times
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			Delay_ms(BLINK_DLY);
			break;
		default:
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			break;
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
static void Delay_ms(__IO uint32_t delay_ms)
{
	for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}

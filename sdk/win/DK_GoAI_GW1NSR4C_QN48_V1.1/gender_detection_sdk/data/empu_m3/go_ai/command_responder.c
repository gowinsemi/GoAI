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

/* Declarations ---------------------------------------------------------- */
static uint8_t max(int8_t* image, int8_t length);

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
			//LED2 and LED3 off
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			GPIO_SetBit(GPIO0, GPIO_Pin_1);
			break;
		case 1:
			//female
			//LED2 on
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			GPIO_SetBit(GPIO0, GPIO_Pin_1);
			break;
		case 2:
			//male
			//LED3 on
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			GPIO_ResetBit(GPIO0, GPIO_Pin_1);
			break;
		default:
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			GPIO_ResetBit(GPIO0, GPIO_Pin_1);
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

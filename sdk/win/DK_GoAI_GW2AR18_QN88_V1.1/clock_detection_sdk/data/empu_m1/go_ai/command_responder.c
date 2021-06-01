/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2021-03-25 09:00:00
 * @brief			command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"
#include "command_responder.h"
#include <stdbool.h>

/* Declarations ---------------------------------------------------------- */
uint8_t max(int8_t* image, int8_t length);

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image, uint32_t* infer_num)
{
	//GoAI indicator
	//image[0] : 00
	//...
	//image[59] : 59
	uint8_t digit = max(image, 60);

	//HDMI : '00' ~ '59'
	*infer_num = (uint32_t)(digit + 1);

	//LED1~6
	GPIO_WriteBits(GPIO0,(uint32_t)(~digit));

}

//find out the maximum digit in image[length]
uint8_t max(int8_t* image, int8_t length)
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

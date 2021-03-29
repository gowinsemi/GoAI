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

/* Variables ------------------------------------------------------------------*/
bool run_flag = true;

/* Declarations ---------------------------------------------------------- */
uint8_t max(int8_t* image, int8_t length);

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image, uint32_t* infer_num)
{
	//GoAI indicator
	//image[0] : Zero
	//image[1] : One
	//image[2] : Two
	//image[3] : Three
	//image[4] : Four
	//image[5] : Five
	//image[6] : Six
	//image[7] : Seven
	//image[8] : Eight
	//image[9] : Nine
	//HDMI
	uint8_t digit = max(image, 10);
	*infer_num = (uint32_t)(digit + 1);

	//System indicator
	//LED12 blinks each inference
	if(run_flag)
	{
		//LEDx on
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_4);
		GPIO_ResetBit(GPIO0, GPIO_Pin_5);
	}
	else
	{
		//LEDx off
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		GPIO_SetBit(GPIO0, GPIO_Pin_1);
		GPIO_SetBit(GPIO0, GPIO_Pin_2);
		GPIO_SetBit(GPIO0, GPIO_Pin_3);
		GPIO_SetBit(GPIO0, GPIO_Pin_4);
		GPIO_SetBit(GPIO0, GPIO_Pin_5);
	}
	run_flag = !run_flag;
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

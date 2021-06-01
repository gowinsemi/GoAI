/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author		 	Embedded Development Team
 * @version			V1.0.0
 * @date			2021-05-28 09:00:00
 * @brief			command responder.
 ******************************************************************************************
 */

/* Includes ---------------------------------------------------------- */
#include "GOWIN_M1.h"
#include "command_responder.h"
#include <stdbool.h>

/* Declarations ---------------------------------------------------------- */
static uint8_t max(int8_t* image, int8_t length);

/* Variables ---------------------------------------------------------- */
bool run_flag = false;

/* Functions ---------------------------------------------------------- */
void command_responder(int8_t* image, uint32_t* infer_num)
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
			//LED
			GPIO_ResetBit(GPIO0, GPIO_Pin_0);
			GPIO_SetBit(GPIO0, GPIO_Pin_1);
			GPIO_SetBit(GPIO0, GPIO_Pin_2);
			//HDMI
			*infer_num = 0x1;
			break;
		case 1:
			//female
			//LED
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			GPIO_ResetBit(GPIO0, GPIO_Pin_1);
			GPIO_SetBit(GPIO0, GPIO_Pin_2);
			//HDMI
			*infer_num = 0x2;
			break;
		case 2:
			//male
			//LED
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			GPIO_SetBit(GPIO0, GPIO_Pin_1);
			GPIO_ResetBit(GPIO0, GPIO_Pin_2);
			//HDMI
			*infer_num = 0x3;
			break;
		default:
			//LED
			GPIO_SetBit(GPIO0, GPIO_Pin_0);
			GPIO_SetBit(GPIO0, GPIO_Pin_1);
			GPIO_SetBit(GPIO0, GPIO_Pin_2);
			//HDMI
			*infer_num = 0x0;
			break;
	}

	//system running indicator
	if(run_flag)
	{
		GPIO_ResetBit(GPIO0, GPIO_Pin_5);
	}
	else
	{
		GPIO_SetBit(GPIO0, GPIO_Pin_5);
	}
	run_flag = !run_flag;
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

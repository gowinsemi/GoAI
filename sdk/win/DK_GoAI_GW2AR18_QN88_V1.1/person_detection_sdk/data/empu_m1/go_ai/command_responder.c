/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2021-03-24 09:00:00
 * @brief			command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"
#include "command_responder.h"
#include <stdbool.h>

/* Variables ------------------------------------------------------------------*/
bool run_flag = true;

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image, uint32_t* infer_num)
{
	//GoAI indicator
	//image[0] : no person
	//image[1] : person
	//LEDx on : person
	//LEDx off : no person
	//HDMI
	if (image[0]<image[1])
	{
		//person
		//LEDx on
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_4);
		
		//HDMI : person
		*infer_num = 0xC;
	}
	else
	{
		//no person
		//LEDx off
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		GPIO_SetBit(GPIO0, GPIO_Pin_1);
		GPIO_SetBit(GPIO0, GPIO_Pin_2);
		GPIO_SetBit(GPIO0, GPIO_Pin_3);
		GPIO_SetBit(GPIO0, GPIO_Pin_4);
		
		//HDMI : empty no person
		*infer_num = 0;
	}
	
	//System indicator
	//LED12 blinks each inference
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

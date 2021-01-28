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
#include "GOWIN_M1.h"
#include "command_responder.h"
#include <stdbool.h>

/* Variables ------------------------------------------------------------------*/
bool run_flag = true;

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image)
{
	//GoAI indicator
	//image[0] : no person
	//image[1] : person
	//LEDx on : person
	//LEDx off : no person
	if (image[0]<image[1])
	{
		//person
		//LEDx on
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_4);
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
	}
	
	//System indicator
	//LED12 blinks
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

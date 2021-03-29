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

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image, uint32_t* infer_num)
{
	//GoAI indicator
	//image[0] : no car
	//image[1] : car
	//LEDx on : car
	//LEDx off : no car
	//HDMI
	if (image[0]<image[1])
	{
		//car
		//LEDx on
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_4);
		
		//HDMI : car
		*infer_num = 0x2;
	}
  else
	{
		//no car
		//LEDx off
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
		GPIO_SetBit(GPIO0, GPIO_Pin_1);
		GPIO_SetBit(GPIO0, GPIO_Pin_2);
		GPIO_SetBit(GPIO0, GPIO_Pin_3);
		GPIO_SetBit(GPIO0, GPIO_Pin_4);
		
		//HDMI : empty no car
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

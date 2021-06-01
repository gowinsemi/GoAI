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
#include <stdbool.h>

/* Variables ------------------------------------------------------------------*/
bool run_flag = false;

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image)
{
	//GoAI running indicator
	//image[0] : no car
	//image[1] : car
	//led3 on : car
	//led3 off : no car
	if (image[0]<image[1])
	{
		//car
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);//led3 on
	}
	else
	{
		//no car
		GPIO_SetBit(GPIO0, GPIO_Pin_1);//led3 off
	}

	//system running indicator
	//led2
	if(run_flag)
	{
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
	}
	else
	{
		GPIO_SetBit(GPIO0, GPIO_Pin_0);
	}
	run_flag = !run_flag;
}

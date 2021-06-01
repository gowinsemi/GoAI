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

/* Functions ------------------------------------------------------------------*/
void command_responder(int8_t* image)
{
	//GoAI running indicator
	//image[0] : no person
	//image[1] : person

	//led2 on : person
	//led2 off : no person
	if (image[0]<image[1])
	{
		//person
		GPIO_SetBit(GPIO0, GPIO_Pin_0);//led2 on
	}
  else
	{
		//no person
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);//led2 off
	}
}

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			command_responder.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-09-28 09:00:00
 * @brief			command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include "command_responder.h"

/* Functions ------------------------------------------------------------------*/
void command_responder(uint8_t* image)
{
	//image[0] : unknown
	//image[1] : person
	//image[2] : no person
	//led2 on : person
	//led2 off : no person
	if (image[1]>image[2])
	{
		//person
		GPIO_WriteBits(GPIO0, 0x0);//led2 on
	}
  else
	{
		//no person
		GPIO_WriteBits(GPIO0, 0x1);//led2 off
	}
}

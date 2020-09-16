/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-15 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */

/* Include ---------------------------------------------------------- */
#include "command_responder.h"
#include "GOWIN_M1.h"

/* Function ---------------------------------------------------------- */
void command_responder(uint8_t* image, uint32_t* infer_num)
{
	if(image[1]>image[2])
	{
		//person
		GPIO_WriteBits(GPIO0,0x2A);//light : low level.
		*infer_num = 0xC;
	}
	else
	{
		//no person
		GPIO_WriteBits(GPIO0,0x0);//light : low level.
		*infer_num = 0;
	}
}

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-23 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */
 
/* Includes ---------------------------------------------------------- */
#include "GOWIN_M1.h"
#include "command_responder.h"
#include <stdio.h>

/* Functions ---------------------------------------------------------- */
void command_responder(int8_t* image, uint32_t* infer_num)
{
	/*
	 * image[0] : no person
	 * image[1] : person
	 */
	if (image[0]<image[1])
	{
		//person
		GPIO_WriteBits(GPIO0,0x3D);	//LED4 : person
		*infer_num = 0xC;						//HDMI : person
		//printf("person score : %d\r\n",image[1]);
	}
	else
	{
		//no person
		GPIO_WriteBits(GPIO0,0x3E);	//LED2 : no person
		*infer_num = 0;							//HDMI :
		//printf("no person score : %d\r\n",image[0]);
	}
	
}

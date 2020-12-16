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
		//LED4 : person
		GPIO_SetBit(GPIO0,GPIO_Pin_0);//LED2 off
		GPIO_ResetBit(GPIO0,GPIO_Pin_1);//LED4 on
		*infer_num = 0xC;				//HDMI : person
		printf("person score : %d\r\n",image[1]);
	}
	else
	{
		//no person
		//LED2 : no prson
		GPIO_ResetBit(GPIO0,GPIO_Pin_0);//LED2 on
		GPIO_SetBit(GPIO0,GPIO_Pin_1);//LED4 off
		*infer_num = 0;					//HDMI :
		printf("no person score : %d\r\n",image[0]);
	}
	
}

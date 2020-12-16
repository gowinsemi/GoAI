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
	 * image[0] : no car
	 * image[1] : car
	 */
	if (image[0]<image[1])
	{
		//car
		//LED4 : car
		GPIO_SetBit(GPIO0,GPIO_Pin_0);//LED2 off
		GPIO_ResetBit(GPIO0,GPIO_Pin_1);//LED4 on
		*infer_num = 0x2;						//HDMI : car
		printf("car score : %d\r\n",image[1]);
	}
	else
	{
		//no car
		//LED2 : no car
		GPIO_ResetBit(GPIO0,GPIO_Pin_0);//LED2 on
		GPIO_SetBit(GPIO0,GPIO_Pin_1);//LED4 off
		*infer_num = 0;							//HDMI :
		printf("no car score : %d\r\n",image[0]);
	}
}

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
		GPIO_WriteBits(GPIO0,0x3D);	//LED4 : car
		*infer_num = 0x2;						//HDMI : car
		printf("car score : %d\r\n",image[1]);
	}
	else
	{
		//no car
		GPIO_WriteBits(GPIO0,0x3E);	//LED2 : no car
		*infer_num = 0;							//HDMI :
		printf("no car score : %d\r\n",image[0]);
	}
	
}

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
		//LED
		GPIO_WriteBits(GPIO0,0x3D);				//LED4 : person
		//HDMI
		*infer_num = 0xC;						//HDMI : person
		//UART
		UART_SendString(UART0, "There is a person!\r\n");
	}
	else
	{
		//no person
		//LED
		GPIO_WriteBits(GPIO0,0x3E);				//LED2 : no person
		//HDMI
		*infer_num = 0;							//HDMI :
		//UART
		UART_SendString(UART0, "There is no person!\r\n");
	}
	
}

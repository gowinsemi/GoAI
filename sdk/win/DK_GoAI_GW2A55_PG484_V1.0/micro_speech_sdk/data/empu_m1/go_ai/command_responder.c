/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-11-16 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "command_responder.h"
#include "GOWIN_M1.h"
#include "helper.h"
#include <string.h>

/* Functions ------------------------------------------------------------------*/
void command_responder(const char* found_command, bool is_new_command)
{
	/*
	 * [0] - silence
     * [1] - unknown
     * [2] - yes
     * [3] - no
	 */
	if(is_new_command)
	{
		if(strcmp(found_command,micro_speech_lable[0])==0)
		{
			//silence
			UART_SendString(UART0, "MICRO_SPEECH : SILENCE.\r\n");
			GPIO_WriteBits(GPIO0,0x3E);
		}
		else if(strcmp(found_command,micro_speech_lable[1])==0)
		{
			//unknown
			UART_SendString(UART0, "MICRO_SPEECH : UNKNOWN.\r\n");
			GPIO_WriteBits(GPIO0,0x3D);
		}
		else if(strcmp(found_command,micro_speech_lable[2])==0)
		{
			//yes
			UART_SendString(UART0, "MICRO_SPEECH : YES.\r\n");
			GPIO_WriteBits(GPIO0,0x3B);
		}
		else if(strcmp(found_command,micro_speech_lable[3])==0)
		{
			//no
			UART_SendString(UART0, "MICRO_SPEECH : NO.\r\n");
			GPIO_WriteBits(GPIO0,0x37);
		}
	}
}

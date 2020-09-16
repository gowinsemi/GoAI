/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-12 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "command_responder.h"
#include "GOWIN_M1.h"
#include "helper.h"
#include <stdio.h>
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
			printf("MICRO_SPEECH : SILENCE.\r\n");
			GPIO_WriteBits(GPIO0,0xE);
		}
		else if(strcmp(found_command,micro_speech_lable[1])==0)
		{
			//unknown
			printf("MICRO_SPEECH : UNKNOWN.\r\n");
			GPIO_WriteBits(GPIO0,0xD);
		}
		else if(strcmp(found_command,micro_speech_lable[2])==0)
		{
			//yes
			printf("MICRO_SPEECH : YES.\r\n");
			GPIO_WriteBits(GPIO0,0xB);
		}
		else if(strcmp(found_command,micro_speech_lable[3])==0)
		{
			//no
			printf("MICRO_SPEECH : NO.\r\n");
			GPIO_WriteBits(GPIO0,0x7);
		}
  }
}

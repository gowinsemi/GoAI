/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-27 09:00:00
 * @brief     Main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "inference.h"
#include "helper.h"

/* Functions ------------------------------------------------------------------*/
int main(void)
{
	/*
	 * Initialization.
	 */
	setup();
	
	/*
	 * Micro Speech : 
	 * audio_provider
	 * feature_provider
	 * inference
	 * command_responder
	 */
	loop();
}

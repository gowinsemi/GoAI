/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-25 09:00:00
 * @brief     person_detection main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "bring_up.h"

/* Functions ------------------------------------------------------------------ */
int main(void)
{
	//initialization.
	setup();
	
	//person_detection loop flow.
	loop();
}

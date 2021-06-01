/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-25 09:00:00
 * @brief     gender_detection main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "bring_up.h"

/* Functions ------------------------------------------------------------------ */
int main(void)
{
	//initialization.
	setup();
	
	//gender_detection loop flow.
	loop();
}

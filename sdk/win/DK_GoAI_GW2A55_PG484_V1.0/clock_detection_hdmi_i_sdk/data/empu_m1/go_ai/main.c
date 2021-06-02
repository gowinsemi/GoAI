/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2021-03-27 09:00:00
 * @brief     clock_detection main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "bring_up.h"

/* Functions ------------------------------------------------------------------ */
int main(void)
{
	//initialization.
	setup();
	
	//clock_detection loop flow.
	loop();
}

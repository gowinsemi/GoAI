/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-20 09:00:00
 * @brief     Main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "bring_up.h"

/* Functions ------------------------------------------------------------------*/
int main(void)
{
	setup();		//Initialization
	loop();			//Convolution loop flow
}

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file        main.c
 * @author      Embedded Development Team
 * @version     V1.0.0
 * @date        2020-9-16 09:00:00
 * @brief       Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "helloworld.h"

int main(void)
{
	setup();	//Initialization
	
	while(1)
	{
		loop();	//Inference hello_world
	}
}

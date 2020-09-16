/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      main.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-15 09:00:00
 * @brief     Main body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "helloworld.h"

int main(void)
{
	setup();//Initialization
	
	while(1)
	{
		loop();//loop fully_connected flow
	}
}

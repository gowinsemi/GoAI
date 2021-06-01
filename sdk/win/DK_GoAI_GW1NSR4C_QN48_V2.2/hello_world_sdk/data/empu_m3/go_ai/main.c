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

/** @addtogroup GW1NS4C_StdPeriph_Template
  * @{
  */

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	setup();	//Initialization
	
	while(1)
	{
		loop();	//Inference hello_world
	}
}

/**
  * @}
  */
/*************************GowinSemiconductor*****END OF FILE*********************/

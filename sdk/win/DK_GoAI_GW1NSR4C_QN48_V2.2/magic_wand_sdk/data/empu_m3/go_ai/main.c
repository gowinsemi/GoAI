/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file        main.c
 * @author      Embedded Development Team
 * @version     V1.0.0
 * @date        2020-10-12 09:00:00
 * @brief       Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "bring_up.h"

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
		loop();	//Inference magic_wand
	}
}

/**
  * @}
  */
/*************************GowinSemiconductor*****END OF FILE*********************/

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helloworld.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-16 09:00:00
 * @brief     hello_world main flow.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include "helper.h"
#include "inference.h"
#include "helloworld.h"

/* Functions ------------------------------------------------------------------*/
//Initialization
void setup(void)
{
	SystemInit();	//Initializes system
	GPIOInit();		//Initializes GPIO
}

//Loop fully_connected flow
void loop(void)
{
	for(int i=-128; i<128; i++) 
	{
		int8_t input_val[16] = {i};		//Input
		int8_t output_data[16];			//Output
		
		//-------------------------AI INFERENCE------------------------------//
		inference(input_val, output_data);
		
		//--------------------------RESULTS-------------------------------//
		//TODO :
		//user customized.
		GPIO_WriteBits(GPIO0,~(1<<(output_data[0] + 128) / 25));//light : low level
	}
}

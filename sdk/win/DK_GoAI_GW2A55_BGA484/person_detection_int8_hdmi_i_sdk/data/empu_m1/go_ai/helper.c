/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-11-26 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "helper.h"
#include "GOWIN_M1.h"

/* Definitions ------------------------------------------------------------------*/
#define SYSTEM_CLOCK (48000000)			//Define new system clock

/* Functions ------------------------------------------------------------------*/
//Initialize system clock
void SystemClockInit(void)
{
	SystemCoreClock = SYSTEM_CLOCK;
}

//Initialize UART0
void UartInit(void)
{
	UART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = 115200;//Baud Rate
	
	UART_Init(UART0,&UART_InitStruct);
}

//Initialize GPIO
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitType;
	
	GPIO_InitType.GPIO_Pin = GPIO_Pin_0 |
	                         GPIO_Pin_1 |
	                         GPIO_Pin_2 |
	                         GPIO_Pin_3 |
	                         GPIO_Pin_4 |
	                         GPIO_Pin_5;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0,&GPIO_InitType);

	GPIO_ResetBit(GPIO0,GPIO_Pin_0);//LED2
	GPIO_ResetBit(GPIO0,GPIO_Pin_1);//LED4
}

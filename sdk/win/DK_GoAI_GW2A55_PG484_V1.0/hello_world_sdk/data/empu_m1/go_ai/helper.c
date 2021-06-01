/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      helper.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-15 09:00:00
 * @brief     initialized peripherals.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "helper.h"
#include "GOWIN_M1.h"

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
	UART_InitStruct.UART_BaudRate = 115200;	//Baud Rate

	UART_Init(UART0,&UART_InitStruct);
}

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

	GPIO_WriteBits(GPIO0,0x0);	//light : low level
}

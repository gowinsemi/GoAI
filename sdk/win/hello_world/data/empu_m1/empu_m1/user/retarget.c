/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file        retarget.c
 * @author      Embedded Development Team
 * @version     V1.3.0
 * @date        2019-10-1 09:00:00
 * @brief       UART printf and scanf retarget function.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"
#include <stdio.h>

int fputc(int ch, FILE *f)
{
	UART_SendChar(UART0, (uint8_t) ch);
	while(UART0->STATE & UART_STATE_TXBF);//UART0
	
	return (ch);
}

int fgetc(FILE *f)
{
	while(!(UART0->STATE & UART_STATE_RXBF));//UART0
	
	return (int)UART_ReceiveChar(UART0);
}

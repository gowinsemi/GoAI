/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file        retarget.c
 * @author      Embedded Development Team
 * @version     V1.6.1
 * @date        2021-01-01 09:00:00
 * @brief       UART printf and scanf retarget function.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"
#include <stdio.h>
#include <sys/stat.h>

__attribute__ ((used))  int _write (int fd, char *ptr, int len)
{
  size_t i;

  for (i=0; i<len; i++)
  {
    UART_SendChar(UART0,ptr[i]); // call character output function
  }

  return len;
}

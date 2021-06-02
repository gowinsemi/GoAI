/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2021-02-23 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */
 
/* Includes ---------------------------------------------------------- */
#include "GOWIN_M1.h"
#include "command_responder.h"

/* Declarations ---------------------------------------------------------- */
static uint8_t max(int8_t* image, int8_t length);
static char* int2str(int num,char*str,int radix);
char buff[20];

/* Functions ---------------------------------------------------------- */
void command_responder(int8_t* image, uint32_t* infer_num)
{
	/*
	 * image[0] : 0
	 * ...
	 * image[59] : 59
	 */
	uint8_t digit = max(image, 60);
	
	//HDMI
	*infer_num = (uint32_t)(digit+1);
	
	//UART
	UART_SendString(UART0, "Current Clock Digit : ");
	UART_SendString(UART0, int2str(digit, buff, 10));
	UART_SendString(UART0, "\r\n");
}

//find out the maximum digit in image[length]
static uint8_t max(int8_t* image, int8_t length)
{
	int8_t max = image[0];
	uint8_t index = 0;
	
	for(uint8_t i = 1;i < length;i++)
	{
		if(max < image[i])
		{
			max = image[i];
			index = i;
		}
	}
	
	return index;
}

static char* int2str(int num,char*str,int radix)
{
	char index[]="0123456789ABCDEF";
	unsigned unum;
	int i=0,j,k;
	char temp;

	if(radix==10&&num<0)
	{
		unum=(unsigned)-num;
		str[i++]='-';
	}
	else
	{
		unum=(unsigned)num;
	}

	do
	{
		str[i++]=index[unum%(unsigned)radix];
		unum/=radix;
	}while(unum);
	str[i]='\0';

	if(str[0]=='-')
	{
		k=1;
	}
	else
	{
		k=0;
	}

	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}

	return str;
}

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-12-14 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */
 
/* Includes ---------------------------------------------------------- */
#include "GOWIN_M1.h"
#include "command_responder.h"

/* Declarations ---------------------------------------------------------- */
static uint8_t max(int8_t* image, int8_t length);

/* Functions ---------------------------------------------------------- */
void command_responder(int8_t* image, uint32_t* infer_num, uint8_t* data)
{
	/*
	 * image[0] : Zero
	 * image[1] : One
	 * image[2] : Two
	 * image[3] : Three
	 * image[4] : Four
	 * image[5] : Five
	 * image[6] : Six
	 * image[7] : Seven
	 * image[8] : Eight
	 * image[9] : Nine
	 */
	switch(max(image, 10))
	{
		case 0:
			//Zero
			GPIO_WriteBits(GPIO0,0x3E);
			*infer_num = 0x1;
			*data = 0;
			UART_SendString(UART0, "Digit : Zero.\r\n");
			break;
		case 1:
			//One
			GPIO_WriteBits(GPIO0,0x3D);
			*infer_num = 0x2;
		  	*data = 1;
		  	UART_SendString(UART0, "Digit : One.\r\n");
			break;
		case 2:
			//Two
			GPIO_WriteBits(GPIO0,0x3B);
			*infer_num = 0x3;
			*data = 2;
			UART_SendString(UART0, "Digit : Two.\r\n");
			break;
		case 3:
			//Three
			GPIO_WriteBits(GPIO0,0x37);
			*infer_num = 0x4;
			*data = 3;
			UART_SendString(UART0, "Digit : Three.\r\n");
			break;
		case 4:
			//Four
			GPIO_WriteBits(GPIO0,0x2F);
			*infer_num = 0x5;
			*data = 4;
			UART_SendString(UART0, "Digit : Four.\r\n");
			break;
		case 5:
			//Five
			GPIO_WriteBits(GPIO0,0x1F);
			*infer_num = 0x6;
			*data = 5;
			UART_SendString(UART0, "Digit : Five.\r\n");
			break;
		case 6:
			//Six
			GPIO_WriteBits(GPIO0,0x3C);
			*infer_num = 0x7;
			*data = 6;
			UART_SendString(UART0, "Digit : Six.\r\n");
			break;
		case 7:
			//Seven
			GPIO_WriteBits(GPIO0,0x33);
			*infer_num = 0x8;
			*data = 7;
			UART_SendString(UART0, "Digit : Seven.\r\n");
			break;
		case 8:
			//Eight
			GPIO_WriteBits(GPIO0,0x0F);
			*infer_num = 0x09;
			*data = 8;
			UART_SendString(UART0, "Digit : Eight.\r\n");
			break;
		case 9:
			//Nine
			GPIO_WriteBits(GPIO0,0x38);
			*infer_num = 0xA;
			*data = 9;
			UART_SendString(UART0, "Digit : Nine.\r\n");
			break;
		default:
			GPIO_WriteBits(GPIO0,0x00);
			*infer_num = 0x0;
			*data = 0;
			UART_SendString(UART0, "Unknown Digit.\r\n");
			break;
	}
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

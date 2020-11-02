/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			helper.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-09-28 09:00:00
 * @brief			initialization.
 ******************************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "helper.h"
#include "gw1ns4c.h"

/* Functions ------------------------------------------------------------------*/
//Initializes GPIO
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitType;
	
	GPIO_InitType.GPIO_Pin = GPIO_Pin_0 |
	                         GPIO_Pin_1 |
	                         GPIO_Pin_2 |
	                         GPIO_Pin_3 |
	                         GPIO_Pin_4 |
	                         GPIO_Pin_5 |
	                         GPIO_Pin_6 |
	                         GPIO_Pin_7 |
	                         GPIO_Pin_8 |
	                         GPIO_Pin_9 |
	                         GPIO_Pin_10 |
	                         GPIO_Pin_11 |
	                         GPIO_Pin_12 |
	                         GPIO_Pin_13 |
	                         GPIO_Pin_14 |
	                         GPIO_Pin_15;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0,&GPIO_InitType);

	GPIO_WriteBits(GPIO0,0x1);//light : low level
}

//Initializes I2C
void I2CInit(void)
{
	static const	unsigned char i2c_data[462] = 
	{
		0xFF, 0x01, 
    0x12, 0x80,
    0xFF, 0x00,
    0x2c, 0xff,
    0x2e, 0xdf,
    0xFF, 0x01,
    0x3c, 0x32,
    0x11, 0x80,
    0x09, 0x02,
    0x04, 0x28,
    0x13, 0xE5,
    0x14, 0x48,
    0x15, 0x00,
    0x2c, 0x0c,
    0x33, 0x78,
    0x3a, 0x33,
    0x3b, 0xfb,
    0x3e, 0x00,
    0x43, 0x11,
    0x16, 0x10,
    0x39, 0x02,
    0x35, 0x88,
    0x22, 0x0a,
    0x37, 0x40,
    0x23, 0x00,
    0x34, 0xa0,
    0x06, 0x02,
    0x06, 0x88,
    0x07, 0xc0,
    0x0d, 0xb7,
    0x0e, 0x01,
    0x4c, 0x00,
    0x4a, 0x81,
    0x21, 0x99,
    0x24, 0x40,
    0x25, 0x38,
    0x26, 0x82,
    0x48, 0x00,
    0x49, 0x00,
    0x5c, 0x00,
    0x63, 0x00,
    0x46, 0x00,
    0x47, 0x00,
    0x0C, 0x3A,
    0x5D, 0x55,
    0x5E, 0x7d,
    0x5F, 0x7d,
    0x60, 0x55,
    0x61, 0x70,
    0x62, 0x80,
    0x7c, 0x05,
    0x20, 0x80,
    0x28, 0x30,
    0x6c, 0x00,
    0x6d, 0x80,
    0x6e, 0x00,
    0x70, 0x02,
    0x71, 0x94,
    0x73, 0xc1,
    0x3d, 0x34,
    0x5a, 0x57,
    0x4F, 0xbb,
    0x50, 0x9c,
    0xFF, 0x00,
    0xe5, 0x7f,
    0xF9, 0xC0,
    0x41, 0x24,
    0xE0, 0x14,
    0x76, 0xff,
    0x33, 0xa0,
    0x42, 0x20,
    0x43, 0x18,
    0x4c, 0x00,
    0x87, 0xD0,
    0x88, 0x3f,
    0xd7, 0x03,
    0xd9, 0x10,
    0xD3, 0x82,
    0xc8, 0x08,
    0xc9, 0x80,
    0x7C, 0x00,
    0x7D, 0x00,
    0x7C, 0x03,
    0x7D, 0x48,
    0x7D, 0x48,
    0x7C, 0x08,
    0x7D, 0x20,
    0x7D, 0x10,
    0x7D, 0x0e,
    0x90, 0x00,
    0x91, 0x0e,
    0x91, 0x1a,
    0x91, 0x31,
    0x91, 0x5a,
    0x91, 0x69,
    0x91, 0x75,
    0x91, 0x7e,
    0x91, 0x88,
    0x91, 0x8f,
    0x91, 0x96,
    0x91, 0xa3,
    0x91, 0xaf,
    0x91, 0xc4,
    0x91, 0xd7,
    0x91, 0xe8,
    0x91, 0x20,
    0x92, 0x00,
    0x93, 0x06,
    0x93, 0xe3,
    0x93, 0x03,
    0x93, 0x03,
    0x93, 0x00,
    0x93, 0x02,
    0x93, 0x00,
    0x93, 0x00,
    0x93, 0x00,
    0x93, 0x00,
    0x93, 0x00,
    0x93, 0x00,
    0x93, 0x00,
    0x96, 0x00,
    0x97, 0x08,
    0x97, 0x19,
    0x97, 0x02,
    0x97, 0x0c,
    0x97, 0x24,
    0x97, 0x30,
    0x97, 0x28,
    0x97, 0x26,
    0x97, 0x02,
    0x97, 0x98,
    0x97, 0x80,
    0x97, 0x00,
    0x97, 0x00,
    0xa4, 0x00,
    0xa8, 0x00,
    0xc5, 0x11,
    0xc6, 0x51,
    0xbf, 0x80,
    0xc7, 0x10,
    0xb6, 0x66,
    0xb8, 0xA5,
    0xb7, 0x64,
    0xb9, 0x7C,
    0xb3, 0xaf,
    0xb4, 0x97,
    0xb5, 0xFF,
    0xb0, 0xC5,
    0xb1, 0x94,
    0xb2, 0x0f,
    0xc4, 0x5c,
    0xa6, 0x00,
    0xa7, 0x20,
    0xa7, 0xd8,
    0xa7, 0x1b,
    0xa7, 0x31,
    0xa7, 0x00,
    0xa7, 0x18,
    0xa7, 0x20,
    0xa7, 0xd8,
    0xa7, 0x19,
    0xa7, 0x31,
    0xa7, 0x00,
    0xa7, 0x18,
    0xa7, 0x20,
    0xa7, 0xd8,
    0xa7, 0x19,
    0xa7, 0x31,
    0xa7, 0x00,
    0xa7, 0x18,
    0x7f, 0x00,
    0xe5, 0x1f,
    0xe1, 0x77,
    0xdd, 0x7f,
    0xC2, 0x0E,
    0xFF, 0x01,
    0xFF, 0x00,
    0xE0, 0x04,
    0xDA, 0x08,
    0xD7, 0x03,
    0xE1, 0x77,
    0xE0, 0x00,
    0xFF, 0x00,
    0x05, 0x01,
    0x5A, 0x28,
    0x5B, 0x1E,
    0x5C, 0x00,
    0xFF, 0x01,
    0x11, 0x83,
    0xFF, 0x01,
    0x12, 0x40,
    0x03, 0x0F,
    0x32, 0x09,
    0x17, 0x11,
    0x18, 0x43,
    0x19, 0x00,
    0x1A, 0x4b,
    0x3d, 0x38,
    0x35, 0xda,
    0x22, 0x1a,
    0x37, 0xc3,
    0x34, 0xc0,
    0x06, 0x88,
    0x0d, 0x87,
    0x0e, 0x41,
    0x42, 0x03,
    0xFF, 0x00,
    0x05, 0x01,
    0xE0, 0x04,
    0xC0, 0x64,
    0xC1, 0x4B,
    0x8C, 0x00,
    0x53, 0x00,
    0x54, 0x00,
    0x51, 0xC8,
    0x52, 0x96,
    0x55, 0x00,
    0x57, 0x00,
    0x86, 0x3D,
    0x50, 0x80,
    0xD3, 0x80,
    0x05, 0x00,
    0xE0, 0x00,
    0xFF, 0x00,
    0x05, 0x00,
    0xFF, 0x00,
    0xE0, 0x04,
    0xDA, 0x08,
    0xD7, 0x03,
    0xE1, 0x77,
		0xE0, 0x00
	};
			 
	I2C_Init(I2C,100);	//Initializes I2C
	
	for(int i=0;i<462;i=i+2)
	{
		I2C_SendByte(I2C,0x30,i2c_data[i],i2c_data[i+1]);
	}	
}

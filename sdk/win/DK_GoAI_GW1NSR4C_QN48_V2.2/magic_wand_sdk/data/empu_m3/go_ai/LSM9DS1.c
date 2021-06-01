/*
  This file is part of the Arduino_LSM9DS1 library.
  Copyright (c) 2019 Arduino SA. All rights reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "gw1ns4c_i2c.h"
#include "LSM9DS1.h"

#define LSM9DS1_ADDRESS            0x6b

#define LSM9DS1_WHO_AM_I           0x0f
#define LSM9DS1_CTRL_REG1_G        0x10
#define LSM9DS1_STATUS_REG         0x17
#define LSM9DS1_OUT_X_G            0x18
#define LSM9DS1_CTRL_REG6_XL       0x20
#define LSM9DS1_CTRL_REG8          0x22
#define LSM9DS1_OUT_X_XL           0x28

// magnetometer
#define LSM9DS1_ADDRESS_M          0x1e

#define LSM9DS1_CTRL_REG1_M        0x20
#define LSM9DS1_CTRL_REG2_M        0x21
#define LSM9DS1_CTRL_REG3_M        0x22
#define LSM9DS1_STATUS_REG_M       0x27
#define LSM9DS1_OUT_X_L_M          0x28
int LSM9DS1_continuousMode;
		
int LSM9DS1_begin(void)
{
  // reset
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG8, 0x05);
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG2_M, 0x0c);

  if(LSM9DS1_readRegister(LSM9DS1_ADDRESS, LSM9DS1_WHO_AM_I) != 0x68)
  {
    LSM9DS1_end();

    return 0;
  }

  if(LSM9DS1_readRegister(LSM9DS1_ADDRESS_M, LSM9DS1_WHO_AM_I) != 0x3d)
  {
    LSM9DS1_end();

    return 0;
  }

  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG1_G, 0x78); // 119 Hz, 2000 dps, 16 Hz BW
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG6_XL, 0x70); // 119 Hz, 4G
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG5_XL, 0xB8); // Decimation-update fifo every four samples, enable X, Y, Z

  LSM9DS1_writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG1_M, 0xb4); // Temperature compensation enable, medium performance, 20 Hz
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG2_M, 0x00); // 4 Gauss
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG3_M, 0x00); // Continuous conversion mode

  return 1;
}

void LSM9DS1_setContinuousMode(void)
{
  // Enable FIFO (see docs https://www.st.com/resource/en/datasheet/DM00103319.pdf)
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, 0x23, 0x02);
	
  uint8_t fifo;
  fifo = I2C_ReceiveByte(I2C,LSM9DS1_ADDRESS,0x23);
	
  // Set continuous mode
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, 0x2E, 0xC0);
	
  uint8_t cont;
  cont = I2C_ReceiveByte(I2C,LSM9DS1_ADDRESS,0x2E);
	
  LSM9DS1_continuousMode = 1;
}

void LSM9DS1_end(void)
{
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS_M, LSM9DS1_CTRL_REG3_M, 0x03);
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG1_G, 0x00);
  LSM9DS1_writeRegister(LSM9DS1_ADDRESS, LSM9DS1_CTRL_REG6_XL, 0x00);
}

int LSM9DS1_readAcceleration(int16_t *x, int16_t *y, int16_t *z)//Update-KV-Changed data type to have space for `save_data` in `accelerometer_handler.c`
{
  int16_t data[3];
	
  I2C_ReadBytes(I2C, LSM9DS1_ADDRESS, LSM9DS1_OUT_X_XL, (uint8_t*)data, sizeof(data));
  *x = data[0];// * 4.0 / 32768.0;
  *y = data[1];// * 4.0 / 32768.0;
  *z = data[2];// * 4.0 / 32768.0;
	
  return 1;
}

int LSM9DS1_accelerationAvailable(void)
{
  if(LSM9DS1_continuousMode)
  {
    // Read FIFO_SRC. If any of the rightmost 8 bits have a value, there is data.
    if(LSM9DS1_readRegister(LSM9DS1_ADDRESS, 0x2F) & 63)
	{
      return 1;
    }
  }
  else
  {
    if(LSM9DS1_readRegister(LSM9DS1_ADDRESS, LSM9DS1_STATUS_REG) & 0x01)
	{
      return 1;
    }
  }

  return 0;
}

float LSM9DS1_accelerationSampleRate(void)
{
  return 119.0F;
}

int LSM9DS1_readRegister(uint8_t slaveAddress, uint8_t address)
{
	return I2C_ReceiveByte(I2C,slaveAddress,address);
}

void LSM9DS1_readRegisters(uint8_t slaveAddress, uint8_t address, uint8_t* data, size_t length)
{
	I2C_ReadBytes(I2C, slaveAddress, address, data, length);
}

void LSM9DS1_writeRegister(uint8_t slaveAddress, uint8_t address, uint8_t value)
{
	//i2c send bytes
	I2C_SendByte(I2C ,slaveAddress,address, value);
}

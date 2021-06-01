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

#include <stdint.h>
#include <stdio.h>

#define LSM9DS1_ADDRESS            0x6b

#define LSM9DS1_WHO_AM_I           0x0f
#define LSM9DS1_CTRL_REG1_G        0x10
#define LSM9DS1_STATUS_REG         0x17
#define LSM9DS1_OUT_X_G            0x18
#define LSM9DS1_CTRL_REG5_XL       0x1F
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

int LSM9DS1_begin(void);
void LSM9DS1_end(void);

// Controls whether a FIFO is continuously filled, or a single reading is stored.
// Defaults to one-shot.
void LSM9DS1_setContinuousMode(void);

// Accelerometer
int LSM9DS1_readAcceleration(int16_t *x, int16_t *y, int16_t *z);//Update-KV-Changed data type to have space for `save_data` in `accelerometer_handler.c`
int LSM9DS1_accelerationAvailable(void); // Number of samples in the FIFO.
float LSM9DS1_accelerationSampleRate(void); // Sampling rate of the sensor.

int LSM9DS1_readRegister(uint8_t slaveAddress, uint8_t address);
void LSM9DS1_readRegisters(uint8_t slaveAddress, uint8_t address, uint8_t* data, size_t length);
void LSM9DS1_writeRegister(uint8_t slaveAddress, uint8_t address, uint8_t value);

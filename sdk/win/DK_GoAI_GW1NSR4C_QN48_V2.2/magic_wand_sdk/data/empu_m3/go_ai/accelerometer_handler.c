/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			accelerometer_handler.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-12 09:00:00
 * @brief			accelerometer handler.
 ******************************************************************************************
 */
 
/* Includes ------------------------------------------------------------------------ */
#include "accelerometer_handler.h"
#include "LSM9DS1.h"

// Most recent position in the save_data buffer
int begin_index = 0;
// True if there is not yet enough data to run inference
uint8_t pending_initial_data = 1;
// How often we should save a measurement during downsampling
int sample_every_n;
// The number of measurements since we last saved one
int sample_skip_counter = 1;


/* Functions ------------------------------------------------------------------------ */
void setup_accelerometer(void)
{
  // Switch on the IMU
  if(!LSM9DS1_begin())
	{
	  //error
		while(1);
  }

  // Make sure we are pulling measurements into a FIFO.
  // If you see an error on this line, make sure you have at least v1.1.0 of the
  // Arduino_LSM9DS1 library installed.
  LSM9DS1_setContinuousMode();

  // Determine how many measurements to keep in order to
  // meet kTargetHz
  float sample_rate = LSM9DS1_accelerationSampleRate();
  sample_every_n = 1;//KV-Update-When using decimation in LSM9DS1
}

uint8_t read_accelerometer(float* input, int length)
{
  // A buffer holding the last 200 sets of 3-channel values
  int16_t save_data[600] = {0.0};

  // Keep track of whether we stored any new data
  uint8_t new_data = 0;
	
  // Loop through new samples and add to buffer
  while(LSM9DS1_accelerationAvailable())
  {
    int16_t x, y, z;
		
    // Read each sample, removing it from the device's FIFO buffer
    if(!LSM9DS1_readAcceleration(&x, &y, &z))
	{
      break;
    }
    // Throw away this sample unless it's the nth
    if(sample_skip_counter != sample_every_n)
	{
      sample_skip_counter += 1;
      continue;
    }
    // Write samples to our buffer, converting to milli-Gs and rotating the axis
    // order for compatibility with model (sensor orientation is different on
    // Arduino Nano BLE Sense compared with SparkFun Edge).
    // The expected orientation of the Arduino on the wand is with the USB port
    // facing down the shaft towards the user's hand, with the reset button
    // pointing at the user's face:
    //
    //                  ____
    //                 |    |<- Arduino board
    //                 |    |
    //                 | () |  <- Reset button
    //                 |    |
    //                  -TT-   <- USB port
    //                   ||
    //                   ||<- Wand
    //                  ....
    //                   ||
    //                   ||
    //                   ()
    //  
    save_data[begin_index++] = -z;//norm_x * 1000;
    save_data[begin_index++] = y;//norm_y * 1000;
    save_data[begin_index++] = x;//norm_z * 1000;
    // Since we took a sample, reset the skip counter
    sample_skip_counter = 1;
    // If we reached the end of the circle buffer, reset
    if(begin_index >= 600)
	{
      begin_index = 0;
    }
		
    new_data = 1;
  }

  // Skip this round if data is not ready yet
  if(!new_data)
  {
    return 0;
  }

  // Check if we are ready for prediction or still pending more initial data
  if(pending_initial_data && begin_index >= 200)
  {
    pending_initial_data = 0;
  }

  // Return if we don't have enough data
  if(pending_initial_data)
  {
    return 0;
  }

  // Copy the requested number of bytes to the provided input tensor
  for(int i = 0; i < length; ++i)
  {
    int ring_array_index = begin_index + i - length;
		
    if (ring_array_index < 0)
	{
      ring_array_index += 600;
    }

    input[i] = save_data[ring_array_index] * 4000.0 / 32768.0;
  }

  return 1;
}

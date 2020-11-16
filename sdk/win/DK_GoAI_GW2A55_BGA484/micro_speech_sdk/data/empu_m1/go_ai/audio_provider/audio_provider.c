/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      audio_provider.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-11-16 09:00:00
 * @brief     Audio provider.
 ******************************************************************************************
 */

/* Includes ---------------------------------------------------------- */
#include "GOWIN_M1.h"
#include "audio_provider.h"
#include "micro_model_settings.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Variables ---------------------------------------------------------- */
int16_t recording_buffer[kMaxAudioSampleSize] = {0};		//audio capture data
volatile uint32_t recording_length = kMaxAudioSampleSize;	//audio capture data number
int16_t g_dummy_audio_data[kMaxAudioSampleSize] = {0};		//audio spectrogram
volatile uint32_t audio_timestamp_ms = 0;					//time stamp

/* Functions ---------------------------------------------------------- */
//capture raw audio data.
void audio_capture(void)
{
	//Audio capture in GoAI_55C board.
	//Microphone is adafruit board.
	uint32_t* vi_buf = (uint32_t *) AHB2PERIPH_BASE;
	uint32_t* vi_en = (uint32_t *) (AHB2PERIPH_BASE + 0x400000);
	*vi_en = 0x01;
	
	while(!(0x2&(*vi_en)));
	
	for(uint32_t i=0;i<recording_length;i++)
	{
		*(recording_buffer+i) = *(vi_buf);
	}
}

//get audio samples.
void GetAudioSamples(int start_ms, int duration_ms, int* audio_samples_size, int16_t** audio_samples)
{
  const int start_sample = start_ms * (kAudioSampleFrequency / 1000);
  uint32_t curr_audio_start_sample = audio_timestamp_ms * (kAudioSampleFrequency / 1000);
  uint32_t curr_audio_end_sample = curr_audio_start_sample+recording_length;
 
  for (int i = 0; i < kMaxAudioSampleSize; ++i)
  {
    const int32_t sample_index = start_sample + i;
    int16_t sample;

    if((sample_index < 0) || (sample_index < curr_audio_start_sample)) 
    {
      sample = 0;
    }
    else if(sample_index >= curr_audio_end_sample)
    {
      sample = 0;
    }
    else
    {
      sample = recording_buffer[sample_index-curr_audio_start_sample];
    }
    
    g_dummy_audio_data[i] = sample;
  }
  
  *audio_samples_size = kMaxAudioSampleSize;
  *audio_samples = g_dummy_audio_data;
}

int32_t LatestAudioTimestamp(void) 
{
  audio_timestamp_ms += 30;
  return audio_timestamp_ms;
}

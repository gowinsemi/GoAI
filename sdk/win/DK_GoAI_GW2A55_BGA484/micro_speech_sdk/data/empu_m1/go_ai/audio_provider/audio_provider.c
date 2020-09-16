/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      audio_provider.c
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-01 09:00:00
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

/* Declarations ---------------------------------------------------------- */
int16_t g_audio_capture_buffer[kAudioSampleFrequency] = {0};	//audio capture
int16_t g_audio_output_buffer[kMaxAudioSampleSize] = {0};			//audio samples

volatile int32_t g_latest_audio_timestamp = 0;								//audio timestamp

/* Functions ---------------------------------------------------------- */
//capture audio.
void audio_capture(void)
{
	//Audio capture in GoAI_55C board.
	//Microphone is adafruit board.
	uint32_t* vi_buf = (uint32_t *) AHB2PERIPH_BASE;
	uint32_t* vi_en = (uint32_t *) (AHB2PERIPH_BASE + 0x400000);

	while(!(0x2&(*vi_en)));
	
	for(uint32_t i=0;i<16000;i++)
	{
		*(g_audio_capture_buffer+i) = *(vi_buf);
	}
	
	*vi_en = 0x0;
}

//get audio samples.
void GetAudioSamples(int start_ms, int duration_ms, int* audio_samples_size, int16_t** audio_samples)
{
	//Audio capture in GoAI_55C board.
	// This next part should only be called when the main thread notices that the
  // latest audio sample data timestamp has changed, so that there's new data
  // in the capture ring buffer. The ring buffer will eventually wrap around and
  // overwrite the data, but the assumption is that the main thread is checking
  // often enough and the buffer is large enough that this call will be made
  // before that happens.

  // Determine the index, in the history of all samples, of the first
  // sample we want
  const int start_offset = start_ms * (kAudioSampleFrequency / 1000);
	
  // Determine how many samples we want in total
  const int duration_sample_count = duration_ms * (kAudioSampleFrequency / 1000);
	
  for(int i = 0; i < duration_sample_count; ++i)
	{
    // For each sample, transform its index in the history of all samples into
    // its index in g_audio_capture_buffer
    const int capture_index = (start_offset + i) % kAudioSampleFrequency;
		
    // Write the sample to the output buffer
    g_audio_output_buffer[i] = g_audio_capture_buffer[capture_index];
  }

  // Set pointers to provide access to the audio
  *audio_samples_size = kMaxAudioSampleSize;
  *audio_samples = g_audio_output_buffer;
}

int32_t LatestAudioTimestamp(void) 
{
  g_latest_audio_timestamp += 100;//100ms is a slice.
  return g_latest_audio_timestamp;
}

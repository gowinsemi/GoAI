/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      audio_provider.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-01 09:00:00
 * @brief     Audio provider.
 ******************************************************************************************
 */

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_MICRO_SPEECH_AUDIO_PROVIDER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_MICRO_SPEECH_AUDIO_PROVIDER_H_

/* Includes ---------------------------------------------------------- */
#include <stdint.h>

/* Declarations ---------------------------------------------------------- */
void audio_capture(void);
void GetAudioSamples(int start_ms, int duration_ms, int* audio_samples_size, int16_t** audio_samples);
int32_t LatestAudioTimestamp(void);

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_MICRO_SPEECH_AUDIO_PROVIDER_H_

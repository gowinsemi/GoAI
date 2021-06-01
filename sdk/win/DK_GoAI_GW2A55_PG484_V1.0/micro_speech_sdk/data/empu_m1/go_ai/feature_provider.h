/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      feature_provider.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-07-28 09:00:00
 * @brief     feature_provider.
 ******************************************************************************************
 */

#ifndef FEATURE_PROVIDER_H_
#define FEATURE_PROVIDER_H_

/* Includes ------------------------------------------------------------------ */
#include <stdint.h>

/* Declarations ------------------------------------------------------------------*/
void feature_provider(int32_t last_time_in_ms, int32_t time_in_ms, int* how_many_new_slices, int feature_size, int8_t* feature_data);

#endif  //FEATURE_PROVIDER_H_

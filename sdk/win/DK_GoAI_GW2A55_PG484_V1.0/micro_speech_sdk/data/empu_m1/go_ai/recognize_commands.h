/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      recognize_commands.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-08-19 09:00:00
 * @brief     recognize_commands.
 ******************************************************************************************
 */

#ifndef RECOGNIZE_COMMANDS_H_
#define RECOGNIZE_COMMANDS_H_

/* Includes ---------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* Declarations ---------------------------------------------------------- */
void recognize_commands(const int8_t* latest_results, const int32_t current_time_ms, const char** found_command, uint8_t* score, bool* is_new_command);

#endif

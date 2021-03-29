/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      command_responder.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2020-09-23 09:00:00
 * @brief     command responder.
 ******************************************************************************************
 */

#ifndef COMMAND_RESPONDER_H_
#define COMMAND_RESPONDER_H_

/* Includes ---------------------------------------------------------- */
#include <stdint.h>

/* Declarations ---------------------------------------------------------- */
void command_responder(int8_t* image, uint32_t* infer_num, uint8_t *data);

#endif

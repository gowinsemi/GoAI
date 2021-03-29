/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      GOWIN_M1_it.h
 * @author    Embedded Development Team
 * @version   V1.3.0
 * @date      2019-10-1 09:00:00
 * @brief     This file contains the headers of the interrupt handlers.
 ******************************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GOWIN_M1_IT_H
#define GOWIN_M1_IT_H

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

/* Core Exceptions Handler */
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* StdPeriph Interrupts Handler */
void UART0_Handler(void);
void UART1_Handler(void);
void TIMER0_Handler(void);
void TIMER1_Handler(void);
void GPIO0_Handler(void);
void RTC_Handler(void);
void I2C_Handler(void);
void CAN_Handler(void);
void ENT_Handler(void);
void DTimer_Handler(void);
void TRNG_Handler(void);

void GPIO0_0_Handler(void);
void GPIO0_1_Handler(void);
void GPIO0_2_Handler(void);
void GPIO0_3_Handler(void);
void GPIO0_4_Handler(void);
void GPIO0_5_Handler(void);
void GPIO0_6_Handler(void);
void GPIO0_7_Handler(void);
void GPIO0_8_Handler(void);
void GPIO0_9_Handler(void);
void GPIO0_10_Handler(void);
void GPIO0_11_Handler(void);
void GPIO0_12_Handler(void);
void GPIO0_13_Handler(void);
void GPIO0_14_Handler(void);
void GPIO0_15_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* GOWIN_M1_IT_H */

/*************************GowinSemiconductor*****END OF FILE*********************/

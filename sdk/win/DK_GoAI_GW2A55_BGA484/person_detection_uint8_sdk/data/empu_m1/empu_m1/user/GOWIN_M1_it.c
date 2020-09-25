/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      GOWIN_M1_it.c
 * @author    Embedded Development Team
 * @version   V1.3.0
 * @date      2019-10-1 09:00:00
 * @brief     Main Interrupt Service Routines.
 *            This file provides template for all exceptions handler and
 *            peripherals interrupt service routine.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "GOWIN_M1_it.h"

/** @addtogroup GOWIN_M1_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M1 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  none
  * @retval none
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  none
  * @retval none
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  none
  * @retval none
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 GOWIN_M1 Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (XXX), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_GOWIN_M1.s).                                                 */
/******************************************************************************/

/**
  * @brief  This function handles UART0 interrupt request.
  * @param  none
  * @retval none
  */
void UART0_Handler(void)
{
}

/**
  * @brief  This function handles UART1 interrupt request.
  * @param  none
  * @retval none
  */
void UART1_Handler(void)
{
}

/**
  * @brief  This function handles TIMER0 interrupt request.
  * @param  none
  * @retval none
  */
void TIMER0_Handler(void)
{
}

/**
  * @brief  This function handles TIMER1 interrupt request.
  * @param  none
  * @retval none
  */
void TIMER1_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_0~15 combine interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_Handler(void)
{
}

/**
  * @brief  This function handles RTC interrupt request.
  * @param  none
  * @retval none
  */
void RTC_Handler(void)
{	
}

/**
  * @brief  This function handles I2C interrupt request.
  * @param  none
  * @retval none
  */
void I2C_Handler(void)
{
}

/**
  * @brief  This function handles CAN interrupt request.
  * @param  none
  * @retval none
  */
void CAN_Handler(void)
{
}

/**
  * @brief  This function handles Ethernet interrupt request.
  * @param  none
  * @retval none
  */
void ENT_Handler(void)
{
}

/**
  * @brief  This function handles DualTimer interrupt request.
  * @param  none
  * @retval none
  */
void DTimer_Handler(void)
{
}

/**
  * @brief  This function handles TRNG interrupt request.
  * @param  none
  * @retval none
  */
void TRNG_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_0 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_0_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_1 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_1_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_2 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_2_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_3 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_3_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_4 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_4_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_5 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_5_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_6 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_6_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_7 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_7_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_8 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_8_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_9 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_9_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_10 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_10_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_11 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_11_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_12 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_12_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_13 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_13_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_14 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_14_Handler(void)
{
}

/**
  * @brief  This function handles GPIO0_15 interrupt request.
  * @param  none
  * @retval none
  */
void GPIO0_15_Handler(void)
{
}

/**
  * @}
  */ 

/*************************GowinSemiconductor*****END OF FILE*********************/

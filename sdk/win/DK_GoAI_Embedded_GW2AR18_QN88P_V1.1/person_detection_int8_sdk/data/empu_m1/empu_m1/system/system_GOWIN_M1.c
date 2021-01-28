/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      system_GOWIN_M1.c
 * @author    Embedded Development Team
 * @version   V1.6.1
 * @date      2021-01-01 09:00:00
 * @brief     CMSIS Cortex-M1 Device Peripheral Access Layer System Source File.
 *              This file contains the system clock configuration for Cortex-M1 device.
 *
 *              This file provides two functions and one global variable to be called from
 *              user application:
 *                - SystemInit(): Setups the system clock.
 *                                 This function is called at startup just after reset and
 *                                 before branch to main program. This call is mad inside
 *                                 the "startup_GOWIN_M1.s" file.
 *                - SystemCoreClock variable: Contains the core clock, it can be used
 *                                 by the user application to setup the SysTick 
 *                                 timer or configure other parameters.
 *                - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
 *                                 be called whenever the core clock is changed
 *                                 during program execution.
 ******************************************************************************************
 */

#include "GOWIN_M1.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  XTAL            (100000000UL)     /* Oscillator frequency */

#define  SYSTEM_CLOCK    (XTAL / 2U)       /* 50MHz                */


/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency */


/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 * @brief  Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
/**
 * @param  none
 * @return none
 * @brief  Setup the Cortex-M1 system.
 *         Initialize the System.
 */
void SystemInit (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

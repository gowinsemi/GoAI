/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      GOWIN_M1_conf.h
 * @author    Embedded Development Team
 * @version   V1.4.0
 * @date      2020-1-1 09:00:00
 * @brief     Library configuration file.
 ******************************************************************************************
 */

/* Define to prevent recursive inclusion--------------------------------------*/
#ifndef GOWIN_M1_CONF_H
#define GOWIN_M1_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "GOWIN_M1_uart.h"			  //UART
//#include "GOWIN_M1_wdog.h"			  //WatchDog
//#include "GOWIN_M1_timer.h"			  //Timer
//#include "GOWIN_M1_dualtimer.h"		//DualTimer
//#include "GOWIN_M1_rtc.h"			    //RTC
//#include "GOWIN_M1_trng.h"			  //TRNG
#include "GOWIN_M1_i2c.h"			    //I2C
//#include "GOWIN_M1_spi.h"			    //SPI
//#include "GOWIN_M1_sdcard.h"		  //SD-Card
//#include "GOWIN_M1_can.h"			    //CAN
//#include "GOWIN_M1_ethernet.h"		//Ethernet
#include "GOWIN_M1_gpio.h"			  //GPIO
//#include "GOWIN_M1_ddr3.h"			  //DDR3
//#include "GOWIN_M1_psram.h"       //PSRAM
//#include "GOWIN_M1_spi_flash.h"		//SPI-Flash
//#include "GOWIN_M1_misc.h"			  //NVIC

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/

//#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __GOWIN_M1_CONF_H */

/*************************GowinSemiconductor*****END OF FILE*********************/

/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file      GOWIN_M1.h
 * @author    Embedded Development Team
 * @version   V1.6.0
 * @date      2020-06-30 09:00:00
 * @brief     CMSIS Cortex-M1 Core Peripheral Access Layer Header File for Device Cortex-M1.
 *				    This file contains all the peripheral register's definitions, bits 
 *				    definitions and memory mapping for Cortex-M1 Connectivity line, 
 *				    High density, High density value line, Medium density, 
 *				    Medium density Value line, Low density, Low density Value line 
 *				    and XL-density devices.
 *
 *				    The file is the unique include file that the application programmer
 *				    is using in the C source code, usually in main.c. This file contains:
 *					   - Configuration section that allows to select:
 *						  - The device used in the target application
 *						  - To use or not the peripheral drivers in application code(i.e. 
 *						    code will be based on direct access to peripheral registers 
 *						    rather than drivers API), this option is controlled by 
 *						    "#define USE_STDPERIPH_DRIVER"
 *						  - To change few application-specific parameters such as 
 *						    crystal frequency
 *						  - Data structures and the address mapping for all peripherals
 *						  - Peripheral's registers declarations and bits definition
 *						  - Macros to access peripheral registers hardware
 *
 ******************************************************************************************
 */

#ifndef GOWIN_M1_H
#define GOWIN_M1_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /* -14 Non Maskable Interrupt   */
  HardFault_IRQn                = -13,     /* -13 HardFault Interrupt      */
  SVCall_IRQn                   =  -5,     /* -5 SV Call Interrupt         */
  PendSV_IRQn                   =  -2,     /* -2 Pend SV Interrupt         */
  SysTick_IRQn                  =  -1,     /* -1 System Tick Interrupt     */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  UART0_IRQn                    =   0,     /* 0 UART0 Interrupt            */
  UART1_IRQn                    =   1,     /* 1 UART1 Interrupt            */
  TIMER0_IRQn                   =   2,     /* 2 TIMER0 Interrupt           */
  TIMER1_IRQn                   =   3,     /* 3 TIMER1 Interrupt           */
  GPIO0_IRQn                    =   4,     /* 4 GPIO0 Interrupt            */
  UARTOVF_IRQn                  =   5,     /* 5 UART0,1 Overflow Interrupt */
  RTC_IRQn                      =   6,     /* 6 RTC Interrupt              */
  I2C_IRQn                      =   7,     /* 7 I2C Interrupt              */
  CAN_IRQn                      =   8,     /* 8 CAN Interrupt              */
  ENT_IRQn                      =   9,     /* 9 Ethernet Interrupt         */
  Interrupt10_IRQn              =   10,    /* 10 Reserved                  */
  DTimer_IRQn                   =   11,    /* 11 DualTimer Interrupt       */
  TRNG_IRQn                     =   12,    /* 12 TRNG Interrupt            */
  Interrupt13_IRQn              =   13,    /* 13 Reserved                  */
  Interrupt14_IRQn              =   14,    /* 14 Reserved                  */
  Interrupt15_IRQn              =   15,    /* 15 Reserved                  */
  GPIO0_0_IRQn                  =   16,    /* 16 GPIO0_0 Interrupt         */
  GPIO0_1_IRQn                  =   17,    /* 17 GPIO0_1 Interrupt         */
  GPIO0_2_IRQn                  =   18,    /* 18 GPIO0_2 Interrupt         */
  GPIO0_3_IRQn                  =   19,    /* 19 GPIO0_3 Interrupt         */
  GPIO0_4_IRQn                  =   20,    /* 20 GPIO0_4 Interrupt         */
  GPIO0_5_IRQn                  =   21,    /* 21 GPIO0_5 Interrupt         */
  GPIO0_6_IRQn                  =   22,    /* 22 GPIO0_6 Interrupt         */
  GPIO0_7_IRQn                  =   23,    /* 23 GPIO0_7 Interrupt         */
  GPIO0_8_IRQn                  =   24,    /* 24 GPIO0_8 Interrupt         */
  GPIO0_9_IRQn                  =   25,    /* 25 GPIO0_9 Interrupt         */
  GPIO0_10_IRQn                 =   26,    /* 26 GPIO0_10 Interrupt        */
  GPIO0_11_IRQn                 =   27,    /* 27 GPIO0_11 Interrupt        */
  GPIO0_12_IRQn                 =   28,    /* 28 GPIO0_12 Interrupt        */
  GPIO0_13_IRQn                 =   29,    /* 29 GPIO0_13 Interrupt        */
  GPIO0_14_IRQn                 =   30,    /* 30 GPIO0_14 Interrupt        */
  GPIO0_15_IRQn                 =   31     /* 31 GPIO0_15 Interrupt        */
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* ----------------------------- Enumeration Definition ----------------------------------- */
typedef enum
{
  RESET = 0,
  SET = !RESET
}FlagStatus,ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
}FunctionalState;

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
}ErrorStatus;

/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM1_REV                 0x0100U   /* Core revision r1p0                           */
#define __MPU_PRESENT             0U        /* no MPU present                               */
#define __VTOR_PRESENT            0U        /* no VTOR present                              */
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels      */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

/* --------------------  Including header file  ----------------------------------- */
#include "core_cm1.h"                       /* Processor and core peripherals               */
#include "system_GOWIN_M1.h"                /* System Header                                */


/* ================================================================================ */
/* ================     Peripheral Register Definition Section     ================ */
/* ================================================================================ */

/*--------- Universal Asynchronous Receiver Transmitter (UART) --------*/
typedef struct
{
  __IO   uint32_t  DATA;          /*!< Offset: 0x000 Data Register    (R/W)          */
  __IO   uint32_t  STATE;         /*!< Offset: 0x004 Status Register  (R/W)          */
  __IO   uint32_t  CTRL;          /*!< Offset: 0x008 Control Register (R/W)          */
  union
  {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W)  */
  };
  __IO   uint32_t  BAUDDIV;       /*!< Offset: 0x010 Baudrate Divider Register (R/W) */
}UART_TypeDef;

/*------------------------ Timer (TIMER) ------------------------*/
typedef struct
{
  __IO   uint32_t  CTRL;          /*!< Offset: 0x000 Control Register (R/W)          */
  __IO   uint32_t  VALUE;         /*!< Offset: 0x004 Current Value Register (R/W)    */
  __IO   uint32_t  RELOAD;        /*!< Offset: 0x008 Reload Value Register  (R/W)    */
  union
  {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W)  */
  };
}TIMER_TypeDef;

/*--------------------- General Purpose Input Output (GPIO) ----------*/
typedef struct
{
  __IO   uint32_t  DATA;          /* Offset: 0x000 (R/W) DATA Register                     */
  __IO   uint32_t  DATAOUT;       /* Offset: 0x004 (R/W) Data Output Latch Register        */
         uint32_t  RESERVED0[2];  /* Offset: 0x010-0x004                                   */
  __IO   uint32_t  OUTENSET;      /* Offset: 0x010 (R/W) Output Enable Set Register        */
  __IO   uint32_t  OUTENCLR;      /* Offset: 0x014 (R/W) Output Enable Clear Register      */
  __IO   uint32_t  ALTFUNCSET;    /* Offset: 0x018 (R/W) Alternate Function Set Register   */
  __IO   uint32_t  ALTFUNCCLR;    /* Offset: 0x01C (R/W) Alternate Function Clear Register */
  __IO   uint32_t  INTENSET;      /* Offset: 0x020 (R/W) Interrupt Enable Set Register     */
  __IO   uint32_t  INTENCLR;      /* Offset: 0x024 (R/W) Interrupt Enable Clear Register   */
  __IO   uint32_t  INTTYPESET;    /* Offset: 0x028 (R/W) Interrupt Type Set Register       */
  __IO   uint32_t  INTTYPECLR;    /* Offset: 0x02C (R/W) Interrupt Type Clear Register     */
  __IO   uint32_t  INTPOLSET;     /* Offset: 0x030 (R/W) Interrupt Polarity Set Register   */
  __IO   uint32_t  INTPOLCLR;     /* Offset: 0x034 (R/W) Interrupt Polarity Clear Register */
  union
  {
    __I    uint32_t  INTSTATUS;      /* Offset: 0x038 (R/ ) Interrupt Status Register                 */
    __O    uint32_t  INTCLEAR;       /* Offset: 0x038 ( /W) Interrupt Clear Register                  */
  };
         uint32_t RESERVED1[241];    /* Offset : 0x400-0x0038                                         */
  __IO   uint32_t MASKLOWBYTE[256];  /* Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) */
  __IO   uint32_t MASKHIGHBYTE[256]; /* Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) */
}GPIO_TypeDef;

/*----------------------------- WatchDog ------------------------*/
typedef struct
{
  __IO    uint32_t  LOAD;           /* Offset: 0x000 (R/W) Watchdog Load Register                         */
  __I     uint32_t  VALUE;          /* Offset: 0x004 (R/ ) Watchdog Value Register                        */
  __IO    uint32_t  CTRL;           /* Offset: 0x008 (R/W) Watchdog Control Register                      */
  __O     uint32_t  INTCLR;         /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register              */
  __I     uint32_t  RIS;            /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register         */
  __I     uint32_t  MIS;            /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register             */
          uint32_t  RESERVED0[762]; /* Offset: 0xC00-0x014                                                */
  __IO    uint32_t  LOCK;           /* Offset: 0xC00 (R/W) Watchdog Lock Register                         */
          uint32_t  RESERVED1[191]; /* Offset: 0xF00-0xC00                                                */
  __IO    uint32_t  ITCR;           /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register     */
  __O     uint32_t  ITOP;           /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register  */
}WDOG_TypeDef;

/*----------------------------- I2C --------------------------*/
typedef struct {
	__IO uint32_t PRER;          /* Offset: 0x00 (R/W) I2C Prescale Register                              */
	__IO uint32_t CTR;           /* Offset: 0x04 (R/W) I2C Control Register                               */
	union
	{
		__I uint32_t RXR;          /* Offset: 0x0C (R/ ) I2C Data Receive Register                          */
		__O uint32_t TXR;          /* Offset: 0x08 ( /W) I2C Data Transmit Register                         */
	};
	union
	{
		__I uint32_t SR;           /* Offset: 0x14 (R/ ) I2C Status Register                                */
		__O uint32_t CR;           /* Offset: 0x10 ( /W) I2C Command Register                               */
	};
}I2C_TypeDef;

/*----------------------------- CAN --------------------------*/
typedef struct {
	__IO uint32_t SRST;       /* 0x0000 software reset register                             */
	__IO uint32_t CMD;        /* 0x0004 command register                                    */
	__IO uint32_t BRP;        /* 0x0008 baud rate prescalar register                        */
	__IO uint32_t BTN;        /* 0x000C bit timing (nominal) register                       */
	__IO uint32_t BTD;        /* 0x0010 bit timing (data)register                           */
	__I  uint32_t RSVD0[3];   /* 0x001C reserved                                            */
	__I  uint32_t IS;         /* 0x0020 interrupt status register                           */
	__IO uint32_t IE;         /* 0x0024 interrupt enable register                           */
	__O  uint32_t IC;         /* 0x0028 interrupt clear register                            */
	__I  uint32_t RSVD1;      /* 0x002C reserved                                            */
	__IO uint32_t CFG;        /* 0x0030 configuration register                              */
	__I  uint32_t RSVD2[3];   /* 0x0034~0x003c reserved                                     */
	__IO uint32_t RXBCFG;     /* 0x0040 rx buffer/fifo configuration register               */
	__IO uint32_t TXBCFG;     /* 0x0044 tx buffer/fifo configuration register               */
	__IO uint32_t TXHBCFG;    /* 0x0048 tx high-priority/fifo configuration register        */
	__I  uint32_t RSVD3;	    /* 0x004C reserved                                            */
	__IO uint32_t TXBRETRY;   /* 0x0050 tx buffer retry count                               */
	__IO uint32_t TXHBRETRY;  /* 0x0054 tx high-priority buffer retry count                 */
	__I  uint32_t TXMSGSTS;   /* 0x0058 transmit message status register                    */
	__I  uint32_t TXHMSGSTS;  /* 0x005C transmit high-priority message status register      */
	__IO uint32_t ERRSTS;     /* 0x0060 error status register                               */
	__I  uint32_t ERRCNTR;    /* 0x0064 error counter register                              */
	__I  uint32_t RSVD4[38];  /* 0x0068~0x00fc reserved                                     */
	__IO uint32_t AF[16];     /* 0x0100 receive acceptance filter register                  */
	__IO uint32_t AFM[16];    /* 0x0140 receive acceptance filter mask register             */
	__I  uint32_t RSVD5[32];  /* 0x0180~0x01fc reserved                                     */
	__I  uint32_t RXB;        /* 0x0200 receive buffer/fifo window register                 */
	__O  uint32_t TXB;        /* 0x0204 transmit buffer/fifo window register                */
	__O  uint32_t TXHB;       /* 0x0208 transmit high-priority buffer/fifo window register  */
	__I  uint32_t TXBSTS;     /* 0x020C transmit buffer/fifo status                         */
	__I  uint32_t TXHBSTS;    /* 0x0210 transmit high-priority byffer/fifo status           */
	__I  uint32_t RXBSTS;     /* 0x0214 receive buffer/fifo status                          */
}CAN_RegDef;

/*----------------------------- Ethernet Mac--------------------------*/
typedef struct {
	union
	{
		__O  uint32_t ETH_TX_DATA[384];       /* 0x000~0x5ff transmit data registers          */
		__I  uint32_t ETH_RX_DATA[384];       /* 0x000~0x5ff receive data registers           */
	};
	__IO uint32_t ETH_TX_LENGTH;            /* 0x600 transmit data length, bit[10:0]        */
	__IO uint32_t ETH_TX_EN;                /* 0x604 transmit enable, bit[0]                */
	__IO uint32_t ETH_TX_FAIL;              /* 0x608 transmit fail, bit[2,1,0]              */
	__I  uint32_t ETH_TX_IS;                /* 0x60c transmit interrupt status, bit[0]      */
	__O  uint32_t ETH_TX_IC;                /* 0x610 transmit interrupt clear, bit[0]       */
	__IO uint32_t ETH_TX_IE;                /* 0x614 transmit interrupt enable, bit[0]      */
	     uint32_t RESERVED_1[26];           /* 0x618~0x67f reserved                         */
	__I  uint32_t ETH_RX_LENGTH;            /* 0x680 receive data length                    */
	__I  uint32_t ETH_RX_IS;                /* 0x684 receive interrupt status, bit[0]       */
	__IO uint32_t ETH_RX_IE;                /* 0x688 receive interrupt enable, bit[0]       */
	__O  uint32_t ETH_RX_IC;                /* 0x68c receive interrupt clear, bit[0]        */
	     uint32_t RESERVED_2[28];           /* 0x690~0x6ff reserved                         */
	__IO uint32_t MIIM_OP_MODE;             /* 0x700 miim operation mode, bit[0]            */
	__IO uint32_t MIIM_PHY_ADDR;            /* 0x704 miim phy address, bit[4:0]             */
	__IO uint32_t MIIM_REG_ADDR;            /* 0x708 miim reg address, bit[4:0]             */
	__IO uint32_t MIIM_WR_DATA;             /* 0x70c miim write data, bit[15:0]             */
	__I  uint32_t MIIM_RD_DATA;             /* 0x710 miim read data, bit[15:0]              */
	__I  uint32_t MIIM_IS;                  /* 0x714 miim interrupt status, bit[1,0]        */
	__IO uint32_t MIIM_IE;                  /* 0x718 miim interrupt enable, bit[1,0]        */
	__O  uint32_t MIIM_IC;                  /* 0x71c miim interrupt clear, bit[1,0]         */
	__IO uint32_t MIIM_OP_EN;               /* 0x720 miim operation enable, bit[0]          */
	__IO uint32_t ETH_MODE;                 /* 0x724 ethernet operation mode, bit[2,1,0]    */
}ETH_RegDef;

/*----------------Serial Peripheral Interface (SPI)-----------------*/
typedef struct
{
  __I     uint32_t RDATA;        /* Offset: 0x00 (R/ ) Data Read Register          */
  __O     uint32_t WDATA;        /* Offset: 0x04 (/W ) Data Write Register         */
  __IO    uint32_t STATUS;       /* Offset: 0x08 (R/W) Status Register             */
  __IO    uint32_t SSMASK;       /* Offset: 0x0C (R/W) Unused Select slave address */
  __IO    uint32_t CTRL;         /* Offset: 0x10 (R/W) Control Register            */
}SPI_TypeDef;

/*--------------------------------DUALTIMER-----------------------------*/
typedef struct 
{
	__IO uint32_t TIMER1LOAD;         /* Offset: 0x00 (R/W) Load Register                   */
	__I  uint32_t TIMER1VALUE ;       /* Offset: 0x04 (R/ ) Current Value Register          */
	__IO uint32_t TIMER1CONTROL;      /* Offset: 0x08 (R/W) Timer Control Register          */
	__O  uint32_t TIMER1INTCLR ;      /* Offset: 0x0C ( /W) Interrupt Clear Register        */
	__I  uint32_t TIMER1RIS    ;      /* Offset: 0x10 (R/ ) Raw Interrupt Status Register   */
	__I  uint32_t TIMER1MIS    ;      /* Offset: 0x14 (R/ ) Interrupt Status Register       */
	__IO uint32_t TIMER1BGLOAD ;      /* Offset: 0x18 (R/W) Background Load Register        */

	__IO uint32_t RESERVE1;           /* Reserved                                           */
	
	__IO uint32_t TIMER2LOAD;         /* Offset: 0x20 (R/W) Load Register                   */
	__I  uint32_t TIMER2VALUE ;       /* Offset: 0x24 (R/ ) Current Value Register          */
	__IO uint32_t TIMER2CONTROL;      /* Offset: 0x28 (R/W) Timer Control Register          */
	__O  uint32_t TIMER2INTCLR ;      /* Offset: 0x2C ( /W) Interrupt Clear Register        */
	__I  uint32_t TIMER2RIS    ;      /* Offset: 0x30 (R/ ) Raw Interrupt Status Register   */
	__I  uint32_t TIMER2MIS    ;      /* Offset: 0x34 (R/ ) Interrupt Status Register       */
	__IO uint32_t TIMER2BGLOAD ;	    /* Offset: 0x38 (R/W) Background Load Register        */
}DUALTIMER_RegDef;

/*--------------------------RTC----------------------------*/
typedef struct
{
	__I  uint32_t RTC_CURRENT_DATA;       /* Offset: 0x000 (R/ ) Data Register                          */
	__IO uint32_t RTC_MATCH_VALUE;        /* Offset: 0x004 (R/W) Match Register                         */
	__IO uint32_t RTC_LOAD_VALUE;         /* Offset: 0x008 (R/W) Load Register                          */
	__IO uint32_t RTC_CTROLLER_REG;       /* Offset: 0x00C (R/W) Control Register                       */
	__IO uint32_t RTC_IMSC;               /* Offset: 0x010 (R/W) Interrupt Mask Set and Clear Register  */
	__I  uint32_t RTC_RIS;                /* Offset: 0x014 (R/ ) Raw Interrupt Status Register          */
	__I  uint32_t RTC_MIS;                /* Offset: 0x018 (R/ ) Masked Interrupt Status Register       */
	__O  uint32_t RTC_INTR_CLEAR;         /* Offset: 0x01C ( /W) Interrupt Clear Register               */
}RTC_RegDef;

/*---------------------------TRNG------------------------------*/
typedef struct
{
	__I  uint8_t  RESEVE1[0x100];         /* Offset: 0x000-0x0FC Reserved                                        */
	__IO uint32_t RNG_IMR;                /* Offset: 0x100 (R/W) Interrupt Mask Register                         */
	__I  uint32_t RNG_ISR;                /* Offset: 0x104 (R/ ) Interrupt Status Register                       */
	__O  uint32_t RNG_ICR;                /* Offset: 0x108 ( /W) Interrupt Clear Register                        */
	__IO uint32_t TRNG_CONFIG;            /* Offset: 0x10C (R/W) Configuration Register                          */
	__I  uint32_t TRNG_VALID;             /* Offset: 0x110 (R/ ) Valid Register                                  */
	__I  uint32_t EHR_DATA0;              /* Offset: 0x114-0x128 (R/ ) Entropy Holding Register Data Registers   */
	__I  uint32_t EHR_DATA1;
	__I  uint32_t EHR_DATA2;
	__I  uint32_t EHR_DATA3;
	__I  uint32_t EHR_DATA4;
	__I  uint32_t EHR_DATA5;
	__IO uint32_t RND_SOURCE_ENABLE;      /* Offset: 0x12C (R/W) Random Source Enable Register                   */
	__IO uint32_t SAMPLE_CNT1;            /* Offset: 0x130 (R/W) Sample Count Register                           */
	__IO uint32_t AUTOCORR_STATISTIC;     /* Offset: 0x134 (R/W) Autocorrelation Register                        */
	__I  uint32_t TRNG_DEBUG_CONTROL;     /* Offset: 0x138 (R/ ) Debug Control Register                          */
	__I  uint32_t RESEVE2;                /* Offset: 0x13C Reserved                                              */
	__O  uint32_t TRNG_SW_RESET;          /* Offset: 0x140 ( /W) Reset Register                                  */
	__I  uint8_t  RESEVE3[0x74];          /* Offset: 0x144-0x1B4 Reserved                                        */
	__I  uint32_t TRNG_BUSY;              /* Offset: 0x1B8 (R/ ) Busy Register                                   */
	__O  uint32_t RST_BIT_COUNT;          /* Offset: 0x1BC ( /W) Reset Bits Counter Register                     */
	__I  uint8_t  RESEVE4[0x20];          /* Offset: 0x1C0-0x1DC Reserved                                        */
	__I  uint32_t RNG_BIST_CNTR0;         /* Offset: 0x1E0-0x1E8 BIST Counter Registers                          */
	__I  uint32_t RNG_BIST_CNTR1;
	__I  uint32_t RNG_BIST_CNTR2;
}TRNG_RegDef;

/*--------------------------SD-Card-----------------------------*/
typedef struct {
	__IO uint32_t  SPI_MASTER_VERSION;				/* Offset: 0x000 (R/W) SPI Master Version Register                   */
	__O  uint32_t  SPI_MASTER_CONTROL;				/* Offset: 0x001 ( /W) SPI Master Control Register                   */
	__IO uint32_t  TRANS_TYPE;								/* Offset: 0x002 (R/W) Transaction Type Register                     */
	__O  uint32_t  TRANS_CTRL;								/* Offset: 0x003 ( /W) Transaction Control Register                  */
	__I  uint32_t  TRANS_STS;									/* Offset: 0x004 (R/ ) Transaction Status Register                   */
	__I  uint32_t  TRANS_ERROR;				  			/* Offset: 0x005 (R/ ) Transaction Error Register                    */
	__IO uint32_t  DIRECT_ACCESS_DATA;				/* Offset: 0x006 (R/W) Data Direct Access Register                   */
	__IO uint32_t  SD_ADDR_7_0;								/* Offset: 0x007 (R/W) SD Address[7:0] Register                      */
	__IO uint32_t  SD_ADDR_15_8;							/* Offset: 0x008 (R/W) SD Address[15:8] Register                     */
	__IO uint32_t  SD_ADDR_23_16;							/* Offset: 0x009 (R/W) SD Address[23:16] Register                    */
	__IO uint32_t  SD_ADDR_31_24;							/* Offset: 0x00A (R/W) SD Address[31:24] Register                    */
	__IO uint32_t  SPI_CLK_DEL;								/* Offset: 0x00B (R/W) SPI Clock Control Register                    */
		   uint32_t  RESERVED0[4];							/* Offset: 0x00C-0x00F Reserved 																		 */
	__IO uint32_t  RX_FIFO_DATA;							/* Offset: 0x010 (R/W) SD Block Read Data Register                   */
		   uint32_t  RESERVED1;									/* Offset: 0x011 (R/W) Reserved                         						 */
	__I  uint32_t  RX_FIFO_DATA_COUNT_MSB;		/* Offset: 0x012 (R/ ) MSByte of Read Data Count Register            */
	__I  uint32_t  RX_FIFO_DATA_COUNT_LSB;		/* Offset: 0x013 (R/ ) LSByte of Read Data Count Register            */
	__O  uint32_t  RX_FIFO_CONTROL;						/* Offset: 0x014 ( /W) SD Block Read Data Control Register           */
		   uint32_t  RESERVED2[11]; 						/* Offset: 0x015-0x019 Reserved																			 */
	__O  uint32_t  TX_FIFO_DATA;							/* Offset: 0x020 ( /W) SD Block Write Data Register                  */
		   uint32_t  RESERVED3[3]; 							/* Offset: 0x021-0x023 Reserved																			 */
	__O  uint32_t  TX_FIFO_CONTROL;						/* Offset: 0x024 ( /W) SD Block Write Data Control Register	         */ 
}SDCard_TypeDef;

/*--------------------------DDR3 Memory-----------------------------*/
typedef struct {
	__IO unsigned int RESERVED;    /* Offset: 0x0000 (R/W) Reserved                               */
	__IO unsigned int WR_ADDR;     /* Offset: 0x0004 (R/W) Write Address Register                 */
	__O  unsigned int WR_DATA[4];  /* Offset: 0x0008~0x0014 ( /W) Write Data Register             */
	__IO unsigned int RD_ADDR;     /* Offset: 0x0018 (R/W) Read Address Register                  */
	__IO unsigned int RD_EN;       /* Offset: 0x001c (R/W) Read Enable Register                   */
	__I  unsigned int RD_DATA[4];  /* Offset: 0x0020~0x002c (R/ ) Read Data Register              */
	__IO unsigned int INIT;        /* Offset: 0x0030 (R/W) Init Done Flag Register                */
	__IO unsigned int WR_EN;       /* Offset: 0x0034 (R/W) Write Enable and End flag Register     */
}DDR3_RegDef;

/*--------------------------SPI-Flash Memory-----------------------------*/
typedef struct 
{
	__I  unsigned int IDREV;                /* Offset: 0x00 (R/ ) ID and revision Register           */
	     unsigned int RESERVED0[3];         /* Offset: 0x04~0x0c Reserved                            */
	__IO unsigned int TRANSFMT;             /* Offset: 0x10 (R/W) SPI transfer format Register       */
	__IO unsigned int DIRECTIO;             /* Offset: 0x14 (R/W) SPI direct IO control Register     */
	     unsigned int RESERVED1[2];         /* Offset: 0x18~0x1c Reserved                            */
	__IO unsigned int TRANSCTRL;            /* Offset: 0x20 (R/W) SPI transfer control Register      */
	__IO unsigned int CMD;                  /* Offset: 0x24 (R/W) SPI command Register               */
	__IO unsigned int ADDR;                 /* Offset: 0x28 (R/W) SPI address Register               */
	__IO unsigned int DATA;                 /* Offset: 0x2c (R/W) SPI data Register                  */
	__IO unsigned int CTRL;                 /* Offset: 0x30 (R/W) SPI control Register               */
	__I  unsigned int STATUS;               /* Offset: 0x34 (R/ ) SPI status Register                */
	__IO unsigned int INTREN;               /* Offset: 0x38 (R/W) SPI interrupt enable Register      */
	__O  unsigned int INTRST;               /* Offset: 0x3c ( /W)SPI interrupt status Register       */
	__IO unsigned int TIMING;               /* Offset: 0x40 (R/W) SPI interface timing Register      */
	     unsigned int RESERVED2[3];         /* Offset: 0x44~0x4c Reserved                            */
	__IO unsigned int MEMCTRL;              /* Offset: 0x50 (R/W) SPI memory access control Register */
	     unsigned int RESERVED3[3];         /* Offset: 0x54~0x5c Reserved                            */
	__IO unsigned int SLVST;                /* Offset: 0x60 (R/W) SPI slave status Register          */
	__I  unsigned int SLVDATACNT;           /* Offset: 0x64 (R/ ) SPI slave data count Register      */
	     unsigned int RESERVED4[5];         /* Offset: 0x68~0x78 Reserved                            */
	__I  unsigned int CONFIG;               /* Offset: 0x7c (R/ ) Configuration Register             */
}SPI_FLASH_RegDef;

/*--------------------------------------PSRAM--------------------------------------*/
typedef struct
{
	__IO unsigned int CMD;                  /* Offset: 0x00 (R/W) PSRAM command register                */
	__IO unsigned int ADDRESS;              /* Offset: 0x04 (R/W) PSRAM address register                */
	__IO unsigned int WR_DATA0;             /* Offset: 0x08 (R/W) PSRAM write data register 0           */
	__IO unsigned int WR_DATA1;             /* Offset: 0x0C (R/W) PSRAM write data register 1           */
	__IO unsigned int WR_DATA2;             /* Offset: 0x10 (R/W) PSRAM write data register 2           */
	__IO unsigned int WR_DATA3;             /* Offset: 0x14 (R/W) PSRAM write data register 3           */
	__O  unsigned int CMD_EN;               /* Offset: 0x18 ( /W) PSRAM command enable register         */
	__IO unsigned int READ_DONE;            /* Offset: 0x1C (R/W) PSRAM read status register            */
	__I  unsigned int RD_DATA0;             /* Offset: 0x20 (R/ ) PSRAM read data register 0            */
	__I  unsigned int RD_DATA1;             /* Offset: 0x24 (R/ ) PSRAM read data register 1            */
	__I  unsigned int RD_DATA2;             /* Offset: 0x28 (R/ ) PSRAM read data register 2            */
	__I  unsigned int RD_DATA3;             /* Offset: 0x2C (R/ ) PSRAM read data register 3            */
	__I  unsigned int INIT_DONE;            /* Offset: 0x30 (R/ ) PSRAM initialization status register  */
}PSRAM_TypeDef;


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* ================================================================================ */
/* ================         Peripheral Address Map Section         ================ */
/* ================================================================================ */

/* Memory and Peripheral base Address */
/* Instruction and Data Memory */
#define ITCM_BASE         ((uint32_t)0x00000000)   /*!< (ITCM      ) Base Address                            */
#define DTCM_BASE         ((uint32_t)0x20000000)   /*!< (DTCM      ) Base Address                            */
#define EXT_INS_MEM_BASE  ((uint32_t)0x00000000)   /*!< (External Instruction Memory ) Base Address          */
#define EXT_DATA_MEM_BASE ((uint32_t)0x20100000)   /*!< (External Data Memory ) Base Address                 */

/* AHB and APB Peripheral base address */
#define AHB1PERIPH_BASE   ((uint32_t)0x40000000)   /*!< (AHB1 Peripheral) Base Address                       */
#define AHB2PERIPH_BASE   ((uint32_t)0x80000000)   /*!< (AHB2 Peripheral) Base Address                       */
#define APB1PERIPH_BASE   ((uint32_t)0x50000000)   /*!< (APB1 Peripheral) Base Address                       */
#define APB2PERIPH_BASE   ((uint32_t)0x60000000)   /*!< (APB2 Peripheral) Base Address                       */

/* APB1 Peripheral base address */
#define TIMER0_BASE       (APB1PERIPH_BASE + 0x0000)    /* !< TIMER0 Base Address     */
#define TIMER1_BASE       (APB1PERIPH_BASE + 0x1000)    /* !< TIMER1 Base Address     */
#define DUALTIMER_BASE    (APB1PERIPH_BASE + 0x2000)    /* !< DUAL timer Base Address */
#define SPI_FLASH_BASE    (APB1PERIPH_BASE + 0x3000)    /* !< SPI Flash Base Address> */
#define UART0_BASE        (APB1PERIPH_BASE + 0x4000)    /* !< UART0  Base Address     */
#define UART1_BASE        (APB1PERIPH_BASE + 0x5000)    /* !< UART1  Base Address     */
#define RTC_BASE          (APB1PERIPH_BASE + 0x6000)    /* !< RTC Base Address        */
#define WDOG_BASE         (APB1PERIPH_BASE + 0x8000)    /* !< WATCHDOG  Base Address  */
#define SDCARD_BASE       (APB1PERIPH_BASE + 0x9000)    /* !< SD-Card Base Address    */
#define I2C_BASE          (APB1PERIPH_BASE + 0xA000)    /* !< I2C Base Address        */
#define SPI_BASE          (APB1PERIPH_BASE + 0xB000)    /* !< SPI Base Address        */
#define TRNG_BASE         (APB1PERIPH_BASE + 0xF000)    /* !< TRNG Base Address       */

/* AHB1 Peripheral base address */
#define GPIO0_BASE        (AHB1PERIPH_BASE + 0x0000000)    /* !< GPIO0 Base Address     */
#define CAN_BASE          (AHB1PERIPH_BASE + 0x5000000)    /* !< CAN Base Address       */
#define ENT_BASE          (AHB1PERIPH_BASE + 0x6000000)    /* !< Ethernet Base Address  */
#define DDR3_BASE         (AHB2PERIPH_BASE + 0x8000000)    /* !< DDR3 Base Address      */
#define PSRAM_BASE        (AHB2PERIPH_BASE + 0x2000000)    /* !< PSRAM Base Address     */

/* AHB2 Peripheral base address */
/* AHB Master [1-6] base address */
#define AHB_M1            (AHB2PERIPH_BASE + 0x0000000)    /* !< AHB Master [1] Base Address   */
#define AHB_M2            (AHB2PERIPH_BASE + 0x1000000)    /* !< AHB Master [2] Base Address   */
#define AHB_M3            (AHB2PERIPH_BASE + 0x6000000)    /* !< AHB Master [3] Base Address   */
#define AHB_M4            (AHB2PERIPH_BASE + 0x9000000)    /* !< AHB Master [4] Base Address   */
#define AHB_M5            (AHB2PERIPH_BASE + 0xA000000)    /* !< AHB Master [5] Base Address   */
#define AHB_M6            (AHB2PERIPH_BASE + 0xB000000)    /* !< AHB Master [6] Base Address   */

/* APB2 Peripheral base address */
/* APB Master [1-16] base address */
#define APB_M1            (APB2PERIPH_BASE + 0x000000)     /* !< APB Master [1] Base Address   */
#define APB_M2            (APB2PERIPH_BASE + 0x100000)     /* !< APB Master [2] Base Address   */
#define APB_M3            (APB2PERIPH_BASE + 0x200000)     /* !< APB Master [3] Base Address   */
#define APB_M4            (APB2PERIPH_BASE + 0x300000)     /* !< APB Master [4] Base Address   */
#define APB_M5            (APB2PERIPH_BASE + 0x400000)     /* !< APB Master [5] Base Address   */
#define APB_M6            (APB2PERIPH_BASE + 0x500000)     /* !< APB Master [6] Base Address   */
#define APB_M7            (APB2PERIPH_BASE + 0x600000)     /* !< APB Master [7] Base Address   */
#define APB_M8            (APB2PERIPH_BASE + 0x700000)     /* !< APB Master [8] Base Address   */
#define APB_M9            (APB2PERIPH_BASE + 0x800000)     /* !< APB Master [9] Base Address   */
#define APB_M10           (APB2PERIPH_BASE + 0x900000)     /* !< APB Master [10] Base Address  */
#define APB_M11           (APB2PERIPH_BASE + 0xA00000)     /* !< APB Master [11] Base Address  */
#define APB_M12           (APB2PERIPH_BASE + 0xB00000)     /* !< APB Master [12] Base Address  */
#define APB_M13           (APB2PERIPH_BASE + 0xC00000)     /* !< APB Master [13] Base Address  */
#define APB_M14           (APB2PERIPH_BASE + 0xD00000)     /* !< APB Master [14] Base Address  */
#define APB_M15           (APB2PERIPH_BASE + 0xE00000)     /* !< APB Master [15] Base Address  */
#define APB_M16           (APB2PERIPH_BASE + 0xF00000)     /* !< APB Master [16] Base Address  */


#define UART0             ((UART_TypeDef      *) UART0_BASE)
#define UART1             ((UART_TypeDef      *) UART1_BASE)
#define TIMER0            ((TIMER_TypeDef     *) TIMER0_BASE)
#define TIMER1            ((TIMER_TypeDef     *) TIMER1_BASE)
#define WDOG              ((WDOG_TypeDef      *) WDOG_BASE)
#define I2C               ((I2C_TypeDef       *) I2C_BASE) 
#define GPIO0             ((GPIO_TypeDef      *) GPIO0_BASE)
#define CAN               ((CAN_RegDef        *) CAN_BASE)
#define Ethernet          ((ETH_RegDef        *) ENT_BASE)
#define DDR3              ((DDR3_RegDef       *) DDR3_BASE)
#define SPI               ((SPI_TypeDef       *) SPI_BASE)
#define DUALTIMER         ((DUALTIMER_RegDef  *) DUALTIMER_BASE)
#define RTC               ((RTC_RegDef        *) RTC_BASE)
#define TRNG              ((TRNG_RegDef       *) TRNG_BASE)
#define SDCARD            ((SDCard_TypeDef    *) SDCARD_BASE)
#define SPI_FLASH         ((SPI_FLASH_RegDef  *) SPI_FLASH_BASE)
#define PSRAM             ((PSRAM_TypeDef     *) PSRAM_BASE)

/* ================================================================================ */
/* ================  Peripheral Register Bit Definition Section    ================ */
/* ================================================================================ */

/******************************************************************************/
/*           Universal Asynchronous Receiver Transmitter (UART)               */
/******************************************************************************/
/* bit definitions for DATA register */
#define UART_DATA              ((uint32_t) 0x000000FF) /* UART DATA: Data value                         */

/* bit definitions for STATE register */
#define UART_STATE_TXBF        ((uint32_t) 0x00000001) /* UART STATE: Tx buffer full                    */
#define UART_STATE_RXBF        ((uint32_t) 0x00000002) /* UART STATE: Rx buffer full                    */
#define UART_STATE_TXOR        ((uint32_t) 0x00000004) /* UART STATE: Tx buffer overrun                 */
#define UART_STATE_RXOR        ((uint32_t) 0x00000008) /* UART STATE: Rx buffer overrun                 */

/* bit definitions for CTRL register */
#define UART_CTRL_TXEN         ((uint32_t) 0x00000001) /* UART CTRL: TX enable                           */
#define UART_CTRL_RXEN         ((uint32_t) 0x00000002) /* UART CTRL: RX enable           
            */
#define UART_CTRL_TXIRQEN      ((uint32_t) 0x00000004) /* UART CTRL: TX interrupt enable 
            */
#define UART_CTRL_RXIRQEN      ((uint32_t) 0x00000008) /* UART CTRL: RX interrupt enable 
            */
#define UART_CTRL_TXORIRQEN    ((uint32_t) 0x00000010) /* UART CTRL: TX overrun interrupt enable         */
#define UART_CTRL_RXORIRQEN    ((uint32_t) 0x00000020) /* UART CTRL: RX overrun interrupt enable         */
#define UART_CTRL_HSTM         ((uint32_t) 0x00000040) /* UART CTRL: High-speed test mode for TX enable  */

/* bit definitions for INTSTATUS register */
#define UART_INTSTATUS_TXIRQ    ((uint32_t) 0x00000001) /* UART INTCLEAR: Get TX interrupt status         */
#define UART_INTSTATUS_RXIRQ    ((uint32_t) 0x00000002) /* UART INTCLEAR: Get RX interrupt status         */
#define UART_INTSTATUS_TXORIRQ  ((uint32_t) 0x00000004) /* UART INTCLEAR: Get TX overrun interrupt status */
#define UART_INTSTATUS_RXORIRQ  ((uint32_t) 0x00000008) /* UART INTCLEAR: Get RX overrun interrupt status */

/* bit definitions for INTCLEAR register */
#define UART_INTCLEAR_TXIRQ    ((uint32_t) 0x00000001) /* UART INTCLEAR: Clear TX interrupt               */
#define UART_INTCLEAR_RXIRQ    ((uint32_t) 0x00000002) /* UART INTCLEAR: Clear RX interrupt               */
#define UART_INTCLEAR_TXORIRQ  ((uint32_t) 0x00000004) /* UART INTCLEAR: Clear TX overrun interrupt       */
#define UART_INTCLEAR_RXORIRQ  ((uint32_t) 0x00000008) /* UART INTCLEAR: Clear RX overrun interrupt       */

/* bit definitions for BAUDDIV register */
#define UART_BAUDDIV           ((uint32_t) 0x000FFFFF) /* UART BAUDDIV: Baud rate divider*/


/******************************************************************************/
/*                                Timer (TIMER)                               */
/******************************************************************************/
/* bit definitions for CTRL register */
#define TIMER_CTRL_EN          ((uint32_t) 0x00000001) /* TIMER CTRL: Enable                          */
#define TIMER_CTRL_SELEXTEN    ((uint32_t) 0x00000002) /* TIMER CTRL: Select external input as enable */
#define TIMER_CTRL_SELEXTCLK   ((uint32_t) 0x00000004) /* TIMER CTRL: Select external input as clock  */
#define TIMER_CTRL_IRQEN       ((uint32_t) 0x00000008) /* TIMER CTRL: Timer interrupt enable          */

/* bit definitions for VALUE register */
#define TIMER_VALUE            ((uint32_t) 0xFFFFFFFF) /* TIMER VALUE: Current value                  */

/* bit definitions for RELOAD register */
#define TIMER_RELOAD           ((uint32_t) 0xFFFFFFFF) /* TIMER RELOAD: Reload value                  */

/* bit definitions for INTSTATUS register */
#define TIMER_INTSTATUS        ((uint32_t) 0x00000001) /* TIMER INTSTATUS: Get Timer interrupt status */

/* bit definitions for INTCLEAR register */
#define TIMER_INTCLEAR         ((uint32_t) 0x00000001) /* TIMER INTCLEAR: Clear Timer interrupt       */

/******************************************************************************/
/*                   General Purpose Input Output (GPIO)                      */
/******************************************************************************/
/* bit definitions for  DATA register */
#define GPIO_DATA           ((uint32_t) 0x0000FFFF)  /* GPIO DATA: Data value                       */

/* bit definitions for DATAOUT register */
#define GPIO_DATAOUT        ((uint32_t) 0x0000FFFF)  /* GPIO DATAOUT: Data output value             */

/* bit definitions for OUTENSET register */
#define GPIO_OUTENSET       ((uint32_t) 0x0000FFFF)  /* GPIO OUTENSET: Output enable set            */

/* bit definitions for OUTENCLR register */
#define GPIO_OUTENCLR       ((uint32_t) 0x0000FFFF)  /* GPIO OUTENCLR: Output enable clear          */

/* bit definitions for ALTFUNCSET register */
#define GPIO_ALTFUNSET      ((uint32_t) 0x0000FFFF)  /* GPIO ALTFUNCSET: Alternative function set   */

/* bit definitions for ALTFUNCCLR register */
#define GPIO_ALTFUNCCLR     ((uint32_t) 0x0000FFFF)  /* GPIO ALTFUNCCLR: Alternative function clear */

/* bit definitions for INTENSET register */
#define GPIO_INTENSET       ((uint32_t) 0x0000FFFF)  /* GPIO INTENSET: Interrupt enable set         */

/* bit definitions for INTENCLR register */
#define GPIO_INTENCLR       ((uint32_t) 0x0000FFFF)  /* GPIO INTENCLR: Interrupt enable clear       */

/* bit definitions for INTTYPESET register */
#define GPIO_INTTYPESET     ((uint32_t) 0x0000FFFF)  /* GPIO INTTYPESET: Interrupt type set         */

/* bit definitions for INTTYPECLR register */
#define GPIO_INTTYPECLR     ((uint32_t) 0x0000FFFF)  /* GPIO INTTYPECLR: Interrupt type clear       */

/* bit definitions for INTPOLSET register */
#define GPIO_INTPOLSET      ((uint32_t) 0x0000FFFF)  /* GPIO INTPOLSET: Interrupt polarity set      */

/* bit definitions for INTPOLCLR register */
#define GPIO_INTPOLCLR      ((uint32_t) 0x0000FFFF)  /* GPIO INTPOLCLR: Interrupt polarity clear    */

/*  bit definitions for INTSTATUS register */
#define GPIO_INTSTATUS      ((uint32_t) 0x0000FFFF)  /* GPIO INTSTATUS: Get Interrupt status        */

/*  bit definitions for INTCLEAR register */
#define GPIO_INTCLEAR       ((uint32_t) 0x0000FFFF)  /* GPIO INTCLEAR: Interrupt request clear      */

/*  bit definitions for MASKLOWBYTE register */
#define GPIO_MASKLOWBYTE    ((uint32_t) 0x000000FF)  /* GPIO MASKLOWBYTE: Data for lower byte access */

/*  bit definitions for MASKHIGHBYTE register */
#define GPIO_MASKHIGHBYTE   ((uint32_t) 0x0000FF00)  /* GPIO MASKHIGHBYTE: Data for high byte access */

/******************************************************************************/
/*                             WatchDog (WDOG)                                */
/******************************************************************************/
/*  bit definitions for LOAD register */
#define WDOG_LOAD              ((uint32_t) 0xFFFFFFFF)  /* the value from which the counter is to decrement     */

/*  bit definitions for VALUE register */
#define WDOG_VALUE             ((uint32_t) 0xFFFFFFFF) /* the current value of the decrementing counter         */

/*  bit definitions for CTRL register */
#define WDOG_CTRL_INTEN        ((uint32_t) 0x00000001)  /* Enable the interrupt                                 */
#define WDOG_CTRL_RESEN        ((uint32_t) 0x00000002)  /* Enable watchdog reset output                         */

/*  bit definitions for INTCLR register */
#define WDOG_INTCLR            ((uint32_t) 0x00000001)  /* clear the watchdog interrupt and reloads the counter */

/*  bit definitions for RAWINTSTAT register */
#define WDOG_RAWINTSTAT        ((uint32_t) 0x00000001)  /* Raw interrupt status from the counter                */

/*  bit definitions for MASKINTSTAT register */
#define WDOG_MASKINTSTAT       ((uint32_t) 0x00000001)  /* Enable interrupt status from the counter             */

/*  bit definitions for LOCK register */
#define WDOG_LOCK_ENSTAT       ((uint32_t) 0x00000001)  /* Register write enable status                         */
#define WDOG_LOCK_EN           ((uint32_t) 0xFFFFFFFE)  /* Enable register writes                               */

/*  bit definitions for ITCR register */
#define WDOG_ITCR_INTEGTESTEN  ((uint32_t) 0x00000001)  /* Integration test mode enable                         */

/*  bit definitions for ITOP register */
#define WDOG_ITOP_WDOGRES      ((uint32_t) 0x00000001)  /* Integration test WDOGINT value                       */
#define WDOG_ITOP_WDOGINT      ((uint32_t) 0x00000002)  /* Integration test WDOGRES value                       */


/* ------------------------ Peripheral Includes -------------------------------------*/
#include "GOWIN_M1_conf.h"


#ifdef __cplusplus
}
#endif

#endif  /* GOWIN_M1_H */

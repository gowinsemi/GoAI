; **************************************************************************************
; *
; 		(C) COPYRIGHT 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
; *
; * File Name	:	startup_GOWIN_M1.s
; * Author		:	Embedded Development Team
; * Version		:	V1.3.0
; * Date		:	2019-10-1 09:00:00
; * Description	:	Cortex-M1 vector table for ARM toolchain
; *					This module performs:
; *					- Set the initial SP
; *					- Set the initial PC == Reset_Handler
; *					- Set the vector table entries with exceptions ISR address
; *					- Configure the system clock
; *					- Branches to __main in the C library(which eventually calls main())
; *					After Reset the Cortex-M1 processor is in Thread mode,
; *					priority is Privileged and the Stach is set to Main
; *
; * <<< Use Configuration Wizard in Context Menu >>>
; *
; ****************************************************************************************

;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Stack_Size      EQU      0x000001000

                AREA     STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE    Stack_Size
__initial_sp


;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Heap_Size       EQU      0x00001000

                IF       Heap_Size != 0                      ; Heap is provided
                AREA     HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE    Heap_Size
__heap_limit
                ENDIF


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA     RESET, DATA, READONLY
                EXPORT   __Vectors
                EXPORT   __Vectors_End
                EXPORT   __Vectors_Size

__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD      UART0_Handler                       ;   0 UART0 Interrupt handler
                DCD      UART1_Handler                       ;   1 UART1 Interrupt handler
                DCD      TIMER0_Handler                      ;   2 TIMER0 Interrupt handler
                DCD      TIMER1_Handler                      ;   3 TIMER1 Interrupt handler
                DCD      GPIO0_Handler                       ;   4 GPIO0 Interrupt handler
                DCD      UARTOVF_Handler                     ;   5 UART0,1 Overflow Interrupt handler
                DCD      RTC_Handler                         ;   6 RTC Interrupt handler
                DCD      I2C_Handler                         ;   7 I2C Interrupt handler
                DCD      CAN_Handler                         ;   8 CAN Interrupt handler
                DCD      ENT_Handler                         ;   9 Ethernet Interrupt handler
				DCD      Interrupt10_Handler                 ;   10 Interrupt 10
				DCD      DTimer_Handler                      ;   11 DualTimer Interrupt handler
				DCD      TRNG_Handler                        ;   12 TRNG Interrupt handler
				DCD      Interrupt13_Handler                 ;   13 Interrupt13 handler
				DCD      Interrupt14_Handler                 ;   14 Interrupt14 handler
				DCD      Interrupt15_Handler                 ;   15 Interrupt15 handler
				DCD      GPIO0_0_Handler                     ;   16 GPIO0_0 Interrupt handler
				DCD      GPIO0_1_Handler                     ;   17 GPIO0_1 Interrupt handler
				DCD      GPIO0_2_Handler                     ;   18 GPIO0_2 Interrupt handler
				DCD      GPIO0_3_Handler                     ;   19 GPIO0_3 Interrupt handler
				DCD      GPIO0_4_Handler                     ;   20 GPIO0_4 Interrupt handler
				DCD      GPIO0_5_Handler                     ;   21 GPIO0_5 Interrupt handler
				DCD      GPIO0_6_Handler                     ;   22 GPIO0_6 Interrupt handler
				DCD      GPIO0_7_Handler                     ;   23 GPIO0_7 Interrupt handler
				DCD      GPIO0_8_Handler                     ;   24 GPIO0_8 Interrupt handler
				DCD      GPIO0_9_Handler                     ;   25 GPIO0_9 Interrupt handler
				DCD      GPIO0_10_Handler                    ;   26 GPIO0_10 Interrupt handler
				DCD      GPIO0_11_Handler                    ;   27 GPIO0_11 Interrupt handler
				DCD      GPIO0_12_Handler                    ;   28 GPIO0_12 Interrupt handler
				DCD      GPIO0_13_Handler                    ;   29 GPIO0_13 Interrupt handler
				DCD      GPIO0_14_Handler                    ;   30 GPIO0_14 Interrupt handler
				DCD      GPIO0_15_Handler                    ;   31 GPIO0_15 Interrupt handler
__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors


                AREA     |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT   Reset_Handler             [WEAK]
                IMPORT   SystemInit
                IMPORT   __main

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX       R0
                ENDP


; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND


; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  UART0_Handler
                Set_Default_Handler  UART1_Handler
                Set_Default_Handler  TIMER0_Handler
                Set_Default_Handler  TIMER1_Handler
                Set_Default_Handler  GPIO0_Handler
                Set_Default_Handler  UARTOVF_Handler
                Set_Default_Handler  RTC_Handler
                Set_Default_Handler  I2C_Handler
                Set_Default_Handler  CAN_Handler
                Set_Default_Handler  ENT_Handler
				Set_Default_Handler  Interrupt10_Handler
				Set_Default_Handler  DTimer_Handler
				Set_Default_Handler  TRNG_Handler
				Set_Default_Handler  Interrupt13_Handler
				Set_Default_Handler  Interrupt14_Handler
				Set_Default_Handler  Interrupt15_Handler
				Set_Default_Handler  GPIO0_0_Handler
				Set_Default_Handler  GPIO0_1_Handler
				Set_Default_Handler  GPIO0_2_Handler
				Set_Default_Handler  GPIO0_3_Handler
				Set_Default_Handler  GPIO0_4_Handler
				Set_Default_Handler  GPIO0_5_Handler
				Set_Default_Handler  GPIO0_6_Handler
				Set_Default_Handler  GPIO0_7_Handler
				Set_Default_Handler  GPIO0_8_Handler
				Set_Default_Handler  GPIO0_9_Handler
				Set_Default_Handler  GPIO0_10_Handler
				Set_Default_Handler  GPIO0_11_Handler
				Set_Default_Handler  GPIO0_12_Handler
				Set_Default_Handler  GPIO0_13_Handler
				Set_Default_Handler  GPIO0_14_Handler
				Set_Default_Handler  GPIO0_15_Handler

                ALIGN


; User setup Stack & Heap

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END

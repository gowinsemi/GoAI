; **************************************************************************************
; *
; 		(C) COPYRIGHT 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
; *
; * File Name	:	startup_gw1ns4c.s
; * Author		:	Embedded Development Team
; * Version		:	V1.0.0
; * Date		:	2019-10-1 09:00:00
; * Description	:	GW1NS-4C Devices vector table for ARM toolchain
; *					This module performs:
; *					- Set the initial SP
; *					- Set the initial PC == Reset_Handler
; *					- Set the vector table entries with exceptions ISR address
; *					- Configure the system clock
; *					- Branches to __main in the C library(which eventually calls main())
; *					After Reset the Cortex-M3 processor is in Thread mode,
; *					priority is Privileged and the Stach is set to Main
; *
; * <<< Use Configuration Wizard in Context Menu >>>
; *
; ****************************************************************************************

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     UART0_Handler             ; [0] UART 0 RX and TX Handler
                DCD     USER_INT0_Handler         ; [1] Interrupt handler 0 to user extension 
                DCD     UART1_Handler             ; [2] UART 1 RX and TX Handler
                DCD     USER_INT1_Handler         ; [3] Interrupt handler 1 to user extension
                DCD     USER_INT2_Handler         ; [4] Interrupt handler 2 to user extension
                DCD     RTC_Handler               ; [5] Reserved
                DCD     PORT0_COMB_Handler        ; [6] GPIO Port 0 Combined Handler
                DCD     USER_INT3_Handler         ; [7] Interrupt handler 3 to user extension
                DCD     TIMER0_Handler            ; [8] TIMER 0 handler
                DCD     TIMER1_Handler            ; [9] TIMER 1 handler
                DCD     0                         ; [10] Reserved
                DCD     I2C_Handler               ; [11] I2C handler
                DCD     UARTOVF_Handler           ; [12] UART 0,1 Overflow Handler
                DCD     USER_INT4_Handler         ; [13] Interrupt handler 4 to user extension
                DCD     USER_INT5_Handler         ; [14] Interrupt handler 5 to user extension
                DCD     Spare15_Handler           ; [15] Not Used
                DCD     PORT0_0_Handler           ; [16] GPIO Port 0 pin 0 Handler
                DCD     PORT0_1_Handler           ; [17] GPIO Port 0 pin 1 Handler
                DCD     PORT0_2_Handler           ; [18] GPIO Port 0 pin 2 Handler
                DCD     PORT0_3_Handler           ; [19] GPIO Port 0 pin 3 Handler
                DCD     PORT0_4_Handler           ; [20] GPIO Port 0 pin 4 Handler
                DCD     PORT0_5_Handler           ; [21] GPIO Port 0 pin 5 Handler
                DCD     PORT0_6_Handler           ; [22] GPIO Port 0 pin 6 Handler
                DCD     PORT0_7_Handler           ; [23] GPIO Port 0 pin 7 Handler
                DCD     PORT0_8_Handler           ; [24] GPIO Port 0 pin 8 Handler
                DCD     PORT0_9_Handler           ; [25] GPIO Port 0 pin 9 Handler
                DCD     PORT0_10_Handler          ; [26] GPIO Port 0 pin 10 Handler
                DCD     PORT0_11_Handler          ; [27] GPIO Port 0 pin 11 Handler
                DCD     PORT0_12_Handler          ; [28] GPIO Port 0 pin 12 Handler
                DCD     PORT0_13_Handler          ; [29] GPIO Port 0 pin 13 Handler
                DCD     PORT0_14_Handler          ; [30] GPIO Port 0 pin 14 Handler
                DCD     PORT0_15_Handler          ; [31] GPIO Port 0 pin 15 Handler
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler
; Branches to __main in the C library(which eventually calls main())
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT UART0_Handler              [WEAK]
                EXPORT USER_INT0_Handler          [WEAK]
                EXPORT UART1_Handler              [WEAK]
                EXPORT USER_INT1_Handler          [WEAK]
                EXPORT USER_INT2_Handler          [WEAK]
				EXPORT RTC_Handler                [WEAK]
                EXPORT PORT0_COMB_Handler         [WEAK]
                EXPORT USER_INT3_Handler          [WEAK]
                EXPORT TIMER0_Handler             [WEAK]
                EXPORT TIMER1_Handler             [WEAK]
                EXPORT I2C_Handler                [WEAK]
                EXPORT UARTOVF_Handler            [WEAK]
                EXPORT USER_INT4_Handler          [WEAK]
                EXPORT USER_INT5_Handler          [WEAK]
                EXPORT Spare15_Handler            [WEAK]
                EXPORT PORT0_0_Handler            [WEAK]
                EXPORT PORT0_1_Handler            [WEAK]
                EXPORT PORT0_2_Handler            [WEAK]
                EXPORT PORT0_3_Handler            [WEAK]
                EXPORT PORT0_4_Handler            [WEAK]
                EXPORT PORT0_5_Handler            [WEAK]
                EXPORT PORT0_6_Handler            [WEAK]
                EXPORT PORT0_7_Handler            [WEAK]
                EXPORT PORT0_8_Handler            [WEAK]
                EXPORT PORT0_9_Handler            [WEAK]
                EXPORT PORT0_10_Handler           [WEAK]
                EXPORT PORT0_11_Handler           [WEAK]
                EXPORT PORT0_12_Handler           [WEAK]
                EXPORT PORT0_13_Handler           [WEAK]
                EXPORT PORT0_14_Handler           [WEAK]
                EXPORT PORT0_15_Handler           [WEAK]

UART0_Handler
USER_INT0_Handler
UART1_Handler
USER_INT1_Handler
USER_INT2_Handler
RTC_Handler
PORT0_COMB_Handler
USER_INT3_Handler
TIMER0_Handler
TIMER1_Handler
I2C_Handler
UARTOVF_Handler
USER_INT4_Handler
USER_INT5_Handler
Spare15_Handler
PORT0_0_Handler
PORT0_1_Handler
PORT0_2_Handler
PORT0_3_Handler
PORT0_4_Handler
PORT0_5_Handler
PORT0_6_Handler
PORT0_7_Handler
PORT0_8_Handler
PORT0_9_Handler
PORT0_10_Handler
PORT0_11_Handler
PORT0_12_Handler
PORT0_13_Handler
PORT0_14_Handler
PORT0_15_Handler
                B       .

                ENDP


                ALIGN

;*******************************************************
; User Initial Stack and Heap
;*******************************************************

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END

;*************************GowinSemiconductor*****END OF FILE*********************

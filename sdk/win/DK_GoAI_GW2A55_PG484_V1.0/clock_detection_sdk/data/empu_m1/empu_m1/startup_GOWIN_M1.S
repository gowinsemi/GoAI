/**************************************************************************************
 *
 		(C) COPYRIGHT 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 *
 * File Name	:	startup_GOWIN_M1.S
 * Author		:	Embedded Development Team
 * Version		:	V1.6.1
 * Date			:	2021-01-01 09:00:00
 * Description	:	Cortex-M1 vector table for ARM toolchain
 *					This module performs:
 *					- Set the initial SP
 *					- Set the initial PC == Reset_Handler
 *					- Set the vector table entries with exceptions ISR address
 *					- Configure the system clock
 *					- Branches to __main in the C library(which eventually calls main())
 *					After Reset the Cortex-M1 processor is in Thread mode,
 *					priority is Privileged and the Stach is set to Main
 *
 * <<< Use Configuration Wizard in Context Menu >>>
 *
 ***************************************************************************************/

/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

                .syntax  unified
                .arch    armv6-m


/*
;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ     Stack_Size, 0x00001000

                .section .stack
                .align   3
	            .globl   __StackTop
	            .globl   __StackLimit
__StackLimit:
                .space   Stack_Size
                .size    __StackLimit, . - __StackLimit
__StackTop:
                .size    __StackTop, . - __StackTop


/*
;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ     Heap_Size, 0x00000200

                .if      Heap_Size != 0                     /* Heap is provided */
                .section .heap
                .align   3
	            .globl   __HeapBase
	            .globl   __HeapLimit
__HeapBase:
                .space   Heap_Size
                .size    __HeapBase, . - __HeapBase
__HeapLimit:
                .size    __HeapLimit, . - __HeapLimit
                .endif


                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVCall Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    UART0_Handler                      /*   0 Interrupt UART0 */
                .long    UART1_Handler                      /*   1 Interrupt UART1 */
                .long    TIMER0_Handler                     /*   2 Interrupt Timer0 */
                .long    TIMER1_Handler                     /*   3 Interrupt Timer1 */
                .long    GPIO0_Handler                      /*   4 Interrupt GPIO0 */
                .long    UARTOVF_Handler                    /*   5 Interrupt UARTOVF */
                .long    RTC_Handler                        /*   6 Interrupt RTC */
                .long    I2C_Handler                        /*   7 Interrupt I2C */
                .long    CAN_Handler                        /*   8 Interrupt CAN */
                .long    ENT_Handler                        /*   9 Interrupt Ethernet */
				.long    Interrupt10_Handler                /*   10 Interrupt 10 */
				.long    DTimer_Handler                     /*   11 Interrupt DualTimer */
				.long    TRNG_Handler                       /*   12 Interrupt TRNG */
				.long    Interrupt13_Handler                /*   13 Interrupt 13 */
				.long    Interrupt14_Handler                /*   14 Interrupt 14 */
				.long    Interrupt15_Handler                /*   15 Interrupt 15 */
				.long    GPIO0_0_Handler                    /*   16 Interrupt GPIO0_0 */
				.long    GPIO0_1_Handler                    /*   17 Interrupt GPIO0_1 */
				.long    GPIO0_2_Handler                    /*   18 Interrupt GPIO0_2 */
				.long    GPIO0_3_Handler                    /*   19 Interrupt GPIO0_3 */
				.long    GPIO0_4_Handler                    /*   20 Interrupt GPIO0_4 */
				.long    GPIO0_5_Handler                    /*   21 Interrupt GPIO0_5 */
				.long    GPIO0_6_Handler                    /*   22 Interrupt GPIO0_6 */
				.long    GPIO0_7_Handler                    /*   23 Interrupt GPIO0_7 */
				.long    GPIO0_8_Handler                    /*   24 Interrupt GPIO0_8 */
				.long    GPIO0_9_Handler                    /*   25 Interrupt GPIO0_9 */
				.long    GPIO0_10_Handler                   /*   26 Interrupt GPIO0_10 */
				.long    GPIO0_11_Handler                   /*   27 Interrupt GPIO0_11 */
				.long    GPIO0_12_Handler                   /*   28 Interrupt GPIO0_12 */
				.long    GPIO0_13_Handler                   /*   29 Interrupt GPIO0_13 */
				.long    GPIO0_14_Handler                   /*   30 Interrupt GPIO0_14 */
				.long    GPIO0_15_Handler                   /*   31 Interrupt GPIO0_15 */

__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
/* Firstly it copies data from read only memory to RAM.
 * There are two schemes to copy. One can copy more than one sections.
 * Another can copy only one section. The former scheme needs more
 * instructions and read-only data to implement than the latter.
 * Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.
 */

#ifdef __STARTUP_COPY_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of triplets, each of which specify:
 *   offset 0: LMA of start of a section to copy from
 *   offset 4: VMA of start of a section to copy to
 *   offset 8: size of the section to copy. Must be multiply of 4
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]
                ldr      r2, [r4, #4]
                ldr      r3, [r4, #8]

.L_loop0_0:
                subs     r3, #4
                blt      .L_loop0_0_done
                ldr      r0, [r1, r3]
                str      r0, [r2, r3]
                b        .L_loop0_0

.L_loop0_0_done:
                adds     r4, #12
                b        .L_loop0

.L_loop0_done:
#else
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                ldr      r1, =__etext
                ldr      r2, =__data_start__
                ldr      r3, =__data_end__

                subs     r3, r2
                ble      .L_loop1_done

.L_loop1:
                subs     r3, #4
                ldr      r0, [r1,r3]
                str      r0, [r2,r3]
                bgt      .L_loop1

.L_loop1_done:
#endif /*__STARTUP_COPY_MULTIPLE */

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of tuples specifying:
 *   offset 0: Start of a BSS section
 *   offset 4: Size of this BSS section. Must be multiply of 4
 */
                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]
                ldr      r2, [r3, #4]
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4
                blt      .L_loop2_0_done
                str      r0, [r1, r2]
                b        .L_loop2_0
.L_loop2_0_done:

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
                ldr      r1, =__bss_start__
                ldr      r2, =__bss_end__

                movs     r0, 0
                subs     r2, r1
                ble      .L_loop3_done

.L_loop3:
                subs     r2, #4
                str      r0, [r1, r2]
                bgt      .L_loop3
.L_loop3_done:
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

                bl       SystemInit
                bl       _start

                .fnend
                .size    Reset_Handler, . - Reset_Handler


                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

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


                .end

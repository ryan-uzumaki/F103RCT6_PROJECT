/*
*********************************************************************************************************
*
*	模块名称 : BSP模块(For STM32H7)
*	文件名称 : bsp.h
*	版    本 : V1.0
*	说    明 : 这是硬件底层驱动程序的主文件。每个c文件可以 #include "bsp.h" 来包含所有的外设驱动模块。
*			   bsp = Borad surport packet 板级支持包
*
*********************************************************************************************************
*/

#ifndef _BSP_H
#define _BSP_H


/* 定义 BSP 版本号 */
#define __STM32F1_BSP_VERSION		"1.1"

/* CPU空闲时执行的函数 */
//#define CPU_IDLE()		bsp_Idle()
#define  USE_RTX   1
/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 这个宏仅用于调试阶段排错 */
#define BSP_Printf		printf
//#define BSP_Printf(...)


#define ERROR_HANDLER()		Error_Handler(__FILE__, __LINE__)

/* 默认是关闭状态 */
#define  Enable_EventRecorder  0

#if Enable_EventRecorder == 1
	#include "EventRecorder.h"
#endif

#include "stm32F1xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f1xx.h"
#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/* 定义优先级分组 */
#define NVIC_PREEMPT_PRIORITY	4


/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
//#include "bsp_msg.h"
//#include "bsp_user_lib.h"
//#include "bsp_timer.h"
#include "bsp_led.h"
#include "bsp_dwt.h"
#include "bsp_relay.h"
#include "bsp_can.h"
#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_watchdog.h"
#include "bsp_spi_bus.h"
#include "bsp_timer.h"
#include "bsp_ps2.h"
#include "bsp_servo.h"
#include "bsp_motor.h"
#include "bsp_encoder.h"
#include "bsp_uart.h"
#include "bsp_can.h"
//#include "bsp_iic.h"

#include "mpuiic.h"

#include "SEGGER_RTT.h"


#include "bsp_adc.h"
#include "bsp_oled.h"
/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void System_Init(void);
void bsp_Idle(void);

void bsp_GetCpuID(uint32_t *_id);
void bsp_RunPer10ms(void);
void bsp_RunPer1ms(void);
void Error_Handler(char *file, uint32_t line);
void bsp_ResetSystem(void);
void UartInfoTransmit(uint8_t * USART_RX_BUF,uint8_t _len);

#endif



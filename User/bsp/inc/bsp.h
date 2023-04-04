/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32H7)
*	�ļ����� : bsp.h
*	��    �� : V1.0
*	˵    �� : ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" ���������е���������ģ�顣
*			   bsp = Borad surport packet �弶֧�ְ�
*
*********************************************************************************************************
*/

#ifndef _BSP_H
#define _BSP_H


/* ���� BSP �汾�� */
#define __STM32F1_BSP_VERSION		"1.1"

/* CPU����ʱִ�еĺ��� */
//#define CPU_IDLE()		bsp_Idle()
#define  USE_RTX   1
/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

/* ���������ڵ��Խ׶��Ŵ� */
#define BSP_Printf		printf
//#define BSP_Printf(...)


#define ERROR_HANDLER()		Error_Handler(__FILE__, __LINE__)

/* Ĭ���ǹر�״̬ */
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

/* �������ȼ����� */
#define NVIC_PREEMPT_PRIORITY	4


/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ�����ײ�����ģ�� */
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
/* �ṩ������C�ļ����õĺ��� */
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



#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "PS2.h"
#include <stdio.h>
#include <stdlib.h>

void Servo_Control_UART(int);//���ڶ�����ƺ���
void pulse_modify(int);//�ı�ռ�ձ�
void Servo_Control_Gate(void);
void Angle_Control_PS2_Gate(void);
void Servo_Control_Baffle(void);
void Angle_Control_PS2_Baffle(void);




static int _angle_gate = 0;
static int _width_gate = 0;
static int _angle_baffle = 0;
static int _width_baffle = 0;
extern TIM_HandleTypeDef htim3;


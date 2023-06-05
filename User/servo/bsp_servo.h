#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "PS2.h"
#include <stdio.h>
#include <stdlib.h>

void Servo_Control_UART(int);//串口舵机控制函数
void pulse_modify(int);//改变占空比


void pulse_modify_Gate1(int);//改变占空比
void pulse_modify_Gate2(int);//改变占空比
void Servo_Control_Gate(void);
void Angle_Control_PS2_Gate(void);

void pulse_modify_Baffle3(int);//改变占空比
void pulse_modify_Baffle4(int);//改变占空比
void Servo_Control_Baffle(void);
void Angle_Control_PS2_Baffle(void);

static int _angle_gate = 0;
static int _angle_baffle = 180;

static int _width_gate1 = 0;
static int _width_gate2 = 0;
static int _width_baffle3 = 0;
static int _width_baffle4 = 0;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;


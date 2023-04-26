#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "PS2.h"
#include <stdio.h>
#include <stdlib.h>

void Servo_Control_UART(int);//串口舵机控制函数
void Servo_Control(void);//舵机控制函数
void pulse_modify(int);//改变占空比
void Angle_Control_PS2();

static int _angle_ = 0;
static int _width_ = 0;
extern TIM_HandleTypeDef htim3;


#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

void Servo_Control(int);//舵机控制函数
void pulse_modify(int);//改变占空比
extern TIM_HandleTypeDef htim3;


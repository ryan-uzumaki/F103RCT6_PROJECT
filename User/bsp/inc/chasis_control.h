#ifndef __CHASIS_CONTROL_H__
#define __CHASIS_CONTROL_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./bsp_motor.h"
#include "bsp_encoder.h"
#include "./pid.h"
#include "PS2.h"
#include "stm32f1xx.h"

static uint16_t motorA_target_speed;
static uint16_t motorB_target_speed;
static uint16_t motorC_target_speed;
static uint16_t motorD_target_speed;
static uint16_t motorA_pwm_PID_speed;
static uint16_t motorB_pwm_PID_speed;
static uint16_t motorC_pwm_PID_speed;
static uint16_t motorD_pwm_PID_speed;
static int _speed_ = 500;

void Chasis_Control(void);
void Chasis_Speed(void);
void Speed_Synchronization(void);
void Speed_PID_Calculate(void);
#endif



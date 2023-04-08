#ifndef __CHASIS_CONTROL_H__
#define __CHASIS_CONTROL_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./bsp_motor.h"
#include "./pid.h"
#include "PS2.h"
#include "stm32f1xx.h"

static int _speed_ = 1000;
void Chasis_Control(void);
void Chasis_Speed(void);

#endif



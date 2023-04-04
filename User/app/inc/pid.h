#ifndef __PID_H__
#define __PID_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f1xx.h"
typedef struct{
    float P;
    float I;
    float D;

    float PrevError;
    float SumError;

}Pid_t;

void bsp_InitPid(void);

int wheelSpeedPidCalc(uint8_t _ucWheelNum, uint16_t _usMeasure, uint16_t _usTarget);
void PID_Param_SetZero(void);
#endif /*__PID_H__*/

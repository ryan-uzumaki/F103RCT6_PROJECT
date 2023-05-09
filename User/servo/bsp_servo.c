#include "./servo/bsp_servo.h"

/**
  * @brief  �ı�pwmռ�ձ�
  * @param  ����0-1000��PWM_PERIOD_COUNT=1000��ռ�ձ�=width/PWM_PERIOD_COUNT��
  * @retval ��
  */
void pulse_modify(int width)
{
//	printf("input width : %d\n",width);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, width);
	printf("successfully modified width\n");
}


/**
  * @brief  ���ڸı����Ƕ�
  * @param  angle(0-180)
  * @retval ��
  */
void Servo_Control_UART(int angle)
{
//	printf("angle = %d\n", angle);
	angle = (0.5 + angle / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify(angle);
//	printf("successfully modified angle\n");
}


void Servo_Control_Gate(void)
{
	_width_gate = (0.5 + _angle_gate / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify(_width_gate);
}

void Angle_Control_PS2_Gate(void)
{
	if((PS2_Data.Key_L1 == 1)&&(PS2_Data.Key_R1 == 0))
	{
		_angle_gate -= 10;
	}
	else if((PS2_Data.Key_R1 == 1)&&(PS2_Data.Key_L1 == 0))
	{
		_angle_gate += 10;
	}
	if(_angle_gate > 180) _angle_gate = 180;
	else if(_angle_gate < 0) _angle_gate = 0;
}


void Servo_Control_Baffle(void)
{
	_width_baffle = (0.5 + _angle_baffle / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify(_width_baffle);
}

void Angle_Control_PS2_Baffle(void)
{
	if((PS2_Data.Key_L2 == 1)&&(PS2_Data.Key_R2 == 0))
	{
		_angle_baffle -= 10;
	}
	else if((PS2_Data.Key_R2 == 1)&&(PS2_Data.Key_L2 == 0))
	{
		_angle_baffle += 10;
	}
	if(_angle_baffle > 180) _angle_baffle = 180;
	else if(_angle_baffle < 0) _angle_baffle = 0;
}



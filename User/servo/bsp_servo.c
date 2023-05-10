#include "./servo/bsp_servo.h"

/**
  * @brief  改变pwm占空比
  * @param  脉宽0-1000（PWM_PERIOD_COUNT=1000，占空比=width/PWM_PERIOD_COUNT）
  * @retval 无
  */
void pulse_modify(int width)
{
//	printf("input width : %d\n",width);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, width);
	printf("successfully modified width\n");
}


/**
  * @brief  串口改变舵机角度
  * @param  angle(0-180)
  * @retval 无
  */
void Servo_Control_UART(int angle)
{
//	printf("angle = %d\n", angle);
	angle = (0.5 + angle / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify(angle);
//	printf("successfully modified angle\n");
}


////gate
//void pulse_modify_Gate(int width)
//{
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, width);
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, width);
//}


//void Servo_Control_Gate(void)
//{
//	_width_gate = (0.5 + _angle_gate / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
//	pulse_modify_Gate(_width_gate);
//}

//void Angle_Control_PS2_Gate(void)
//{
//	if((PS2_Data.Key_L1 == 1)&&(PS2_Data.Key_R1 == 0))
//	{
//		_angle_gate -= 10;
//	}
//	else if((PS2_Data.Key_R1 == 1)&&(PS2_Data.Key_L1 == 0))
//	{
//		_angle_gate += 10;
//	}
//	if(_angle_gate > 180)
//	{
//		_angle_gate = 180;
//	}
//		
//	else if(_angle_gate < 0)
//	{
//		_angle_gate = 0;
//	}
//}


////baffle
//void pulse_modify_Baffle(int width)
//{
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, width);
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, width);
//}


//void Servo_Control_Baffle(void)
//{
//	_width_baffle = (0.5 + _angle_baffle / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
//	pulse_modify_Baffle(_width_baffle);
//}

//void Angle_Control_PS2_Baffle(void)
//{
//	if((PS2_Data.Key_L2 == 1)&&(PS2_Data.Key_R2 == 0))
//	{
//		_angle_baffle -= 10;
//	}
//	else if((PS2_Data.Key_R2 == 1)&&(PS2_Data.Key_L2 == 0))
//	{
//		_angle_baffle += 10;
//	}
//	if(_angle_baffle > 180)
//	{
//		_angle_baffle = 180;
//	}		
//	
//	else if(_angle_baffle < 0)
//	{
//		_angle_baffle = 0;
//	}		
//}


//gate
void pulse_modify_Gate1(int width)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, width);
}

void pulse_modify_Gate2(int width)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, width);
}

void Servo_Control_Gate(void)
{
	_width_gate1 = (0.5 + _angle_gate / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	_width_gate2 = (0.5 + (180-_angle_gate) / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify_Gate1(_width_gate1);
	pulse_modify_Gate2(_width_gate2);
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
	if(_angle_gate > 180)
	{
		_angle_gate = 180;
	}
		
	else if(_angle_gate < 0)
	{
		_angle_gate = 0;
	}
}


//baffle
void pulse_modify_Baffle3(int width)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, width);
}

void pulse_modify_Baffle4(int width)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, width);
}


void Servo_Control_Baffle(void)
{
	_width_baffle3 = (0.5 + _angle_baffle / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	_width_baffle4 = (0.5 + (180-_angle_baffle) / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify_Baffle3(_width_baffle3);
	pulse_modify_Baffle4(_width_baffle4);
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
	if(_angle_baffle > 180)
	{
		_angle_baffle = 180;
	}		
	
	else if(_angle_baffle < 0)
	{
		_angle_baffle = 0;
	}		
}






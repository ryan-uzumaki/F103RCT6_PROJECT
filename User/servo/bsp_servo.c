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
  * @brief  改变舵机角度
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


void Servo_Control(void)
{
	_width_ = (0.5 + _angle_ / 180.0 * (2.5 - 0.5)) / 20.0 * 1000;
	pulse_modify(_width_);
}

void Angle_Control_PS2()
{
	if((PS2_Data.Key_L1 == 1)&&(PS2_Data.Key_R1 == 0))
	{
		_angle_ -= 10;
	}
	else if((PS2_Data.Key_R1 == 1)&&(PS2_Data.Key_L1 == 0))
	{
		_angle_ += 10;
	}
	if(_angle_ > 180) _angle_ = 180;
	else if(_angle_ < 0) _angle_ = 0;
}



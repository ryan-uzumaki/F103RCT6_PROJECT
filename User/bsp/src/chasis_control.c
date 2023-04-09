#include "chasis_control.h"


void Chasis_Control(void)
{
	printf("_speed_ : %d\n", _speed_);
	printf("motorA_pwm_PID_speed : %d\n", motorA_pwm_PID_speed);
//	printf("motorB_pwm_PID_speed : %d\n", motorB_pwm_PID_speed);
//	printf("motorC_pwm_PID_speed : %d\n", motorC_pwm_PID_speed);
//	printf("motorD_pwm_PID_speed : %d\n", motorD_pwm_PID_speed);
	//ORIGIN-STOP
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(0,0);//FORWARD CH_1
		MotoBSetSpeed(0,0);//FORWARD CH_2
		MotoCSetSpeed(0,0);//FORWARD CH_3
		MotoDSetSpeed(0,0);//FORWARD CH_4
		PID_Param_SetZero();
	}
	//FORWARD
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(0,motorA_pwm_PID_speed);//FORWARD CH_1
		MotoBSetSpeed(0,motorB_pwm_PID_speed);//FORWARD CH_2
		MotoCSetSpeed(0,motorC_pwm_PID_speed);//FORWARD CH_3
		MotoDSetSpeed(0,motorD_pwm_PID_speed);//FORWARD CH_4
	}
	//BACKWARD
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,motorA_pwm_PID_speed);//BACKWARD CH_1
		MotoBSetSpeed(1,motorB_pwm_PID_speed);//BACKWARD CH_2
		MotoCSetSpeed(1,motorC_pwm_PID_speed);//BACKWARD CH_3
		MotoDSetSpeed(1,motorD_pwm_PID_speed);//BACKWARD CH_4
	}
	//RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(0,motorA_pwm_PID_speed);//FORWARD CH_1
		MotoBSetSpeed(1,motorB_pwm_PID_speed);//BACKWARD CH_2
		MotoCSetSpeed(0,motorC_pwm_PID_speed);//FORWARD CH_3
		MotoDSetSpeed(1,motorD_pwm_PID_speed);//BACKWARD CH_4
	}
	//LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(1,motorA_pwm_PID_speed);//BACKWARD CH_1
		MotoBSetSpeed(0,motorB_pwm_PID_speed);//FORWARD CH_2
		MotoCSetSpeed(1,motorC_pwm_PID_speed);//BACKWARD CH_3
		MotoDSetSpeed(0,motorD_pwm_PID_speed);//FORWARD CH_4
	}
	//UP_LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(1,0);//BACKWARD CH_1
		MotoBSetSpeed(0,motorB_pwm_PID_speed);//FORWARD CH_2
		MotoCSetSpeed(1,0);//BACKWARD CH_3
		MotoDSetSpeed(0,motorD_pwm_PID_speed);//FORWARD CH_4
	}
	//DOWN_LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,motorA_pwm_PID_speed);//BACKWARD CH_1
		MotoBSetSpeed(1,0);//BACKWARD CH_2
		MotoCSetSpeed(1,motorC_pwm_PID_speed);//BACKWARD CH_3
		MotoDSetSpeed(1,0);//BACKWARD CH_4
	}
	//UP_RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(0,motorA_pwm_PID_speed);//FORWARD CH_1
		MotoBSetSpeed(1,0);//BACKWARD CH_2
		MotoCSetSpeed(0,motorC_pwm_PID_speed);//FORWARD CH_3
		MotoDSetSpeed(1,0);//BACKWARD CH_4
	}
	//DOWM_RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,0);//BACKWARD CH_1
		MotoBSetSpeed(1,motorB_pwm_PID_speed);//BACKWARD CH_2
		MotoCSetSpeed(1,0);//BACKWARD CH_3
		MotoDSetSpeed(1,motorD_pwm_PID_speed);//BACKWARD CH_4
	}
	//CCW
	if((PS2_Data.Rocker_RX == -127)&&(PS2_Data.Rocker_RY == 0))
	{
		MotoASetSpeed(1,motorA_pwm_PID_speed);//BACKWARD CH_1
		MotoBSetSpeed(1,motorB_pwm_PID_speed);//BACKWARD CH_2
		MotoCSetSpeed(0,motorC_pwm_PID_speed);//FORWARD CH_3
		MotoDSetSpeed(0,motorD_pwm_PID_speed);//FORWARD CH_4
	}
	//CW
	if((PS2_Data.Rocker_RX == 127)&&(PS2_Data.Rocker_RY == 0))
	{
		MotoASetSpeed(0,motorA_pwm_PID_speed);//FORWARD CH_1
		MotoBSetSpeed(0,motorB_pwm_PID_speed);//FORWARD CH_2
		MotoCSetSpeed(1,motorC_pwm_PID_speed);//BACKWARD CH_3
		MotoDSetSpeed(1,motorD_pwm_PID_speed);//BACKWARD CH_4
	}
}


void Chasis_Speed(void)
{
	if((PS2_Data.Key_R_Up == 1)&&(PS2_Data.Key_R_Down == 0))
	{
		_speed_+=5;
		if(_speed_>1000)_speed_=1000;
	}
	if((PS2_Data.Key_R_Up == 0)&&(PS2_Data.Key_R_Down == 1))
	{
		_speed_-=5;
		if(_speed_<0)_speed_=0;
	}
}

void Speed_Synchronization(void)
{
	motorA_target_speed = _speed_;
	motorB_target_speed = _speed_;
	motorC_target_speed = _speed_;
	motorD_target_speed = _speed_;
}

void Speed_PID_Calculate(void)
{
	motorA_pwm_PID_speed = 2*wheelSpeedPidCalc(0, g_WheelSpeed[0],  motorA_target_speed) > 2000 ? 2000 : 2*wheelSpeedPidCalc(0, g_WheelSpeed[0],  motorA_target_speed);
	motorB_pwm_PID_speed = 2*wheelSpeedPidCalc(1, g_WheelSpeed[1],  motorB_target_speed) > 2000 ? 2000 : 2*wheelSpeedPidCalc(1, g_WheelSpeed[1],  motorB_target_speed);
	motorC_pwm_PID_speed = 2*wheelSpeedPidCalc(2, g_WheelSpeed[2],  motorC_target_speed) > 2000 ? 2000 : 2*wheelSpeedPidCalc(2, g_WheelSpeed[2],  motorC_target_speed);
	motorD_pwm_PID_speed = 2*wheelSpeedPidCalc(3, g_WheelSpeed[3],  motorD_target_speed) > 2000 ? 2000 : 2*wheelSpeedPidCalc(3, g_WheelSpeed[3],  motorD_target_speed);
}







#include "chasis_control.h"


void Chasis_Control(void)
{
	printf("_speed_ : %d\n", _speed_);
	//ORIGIN-STOP
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(0,0);//FORWARD CH_1
		MotoBSetSpeed(0,0);//FORWARD CH_2
		MotoCSetSpeed(0,0);//FORWARD CH_3
		MotoDSetSpeed(0,0);//FORWARD CH_4
	}
	//FORWARD
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(0,_speed_);//FORWARD CH_1
		MotoBSetSpeed(0,_speed_);//FORWARD CH_2
		MotoCSetSpeed(0,_speed_);//FORWARD CH_3
		MotoDSetSpeed(0,_speed_);//FORWARD CH_4
	}
	//BACKWARD
	if((PS2_Data.Rocker_LX == 0)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,_speed_);//BACKWARD CH_1
		MotoBSetSpeed(1,_speed_);//BACKWARD CH_2
		MotoCSetSpeed(1,_speed_);//BACKWARD CH_3
		MotoDSetSpeed(1,_speed_);//BACKWARD CH_4
	}
	//RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(0,_speed_);//FORWARD CH_1
		MotoBSetSpeed(1,_speed_);//BACKWARD CH_2
		MotoCSetSpeed(0,_speed_);//FORWARD CH_3
		MotoDSetSpeed(1,_speed_);//BACKWARD CH_4
	}
	//LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == 0))
	{
		MotoASetSpeed(1,_speed_);//BACKWARD CH_1
		MotoBSetSpeed(0,_speed_);//FORWARD CH_2
		MotoCSetSpeed(1,_speed_);//BACKWARD CH_3
		MotoDSetSpeed(0,_speed_);//FORWARD CH_4
	}
	//UP_LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(1,0);//BACKWARD CH_1
		MotoBSetSpeed(0,_speed_);//FORWARD CH_2
		MotoCSetSpeed(1,0);//BACKWARD CH_3
		MotoDSetSpeed(0,_speed_);//FORWARD CH_4
	}
	//DOWN_LEFT
	if((PS2_Data.Rocker_LX == -127)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,_speed_);//BACKWARD CH_1
		MotoBSetSpeed(1,0);//BACKWARD CH_2
		MotoCSetSpeed(1,_speed_);//BACKWARD CH_3
		MotoDSetSpeed(1,0);//BACKWARD CH_4
	}
	//UP_RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == 127))
	{
		MotoASetSpeed(0,_speed_);//FORWARD CH_1
		MotoBSetSpeed(1,0);//BACKWARD CH_2
		MotoCSetSpeed(0,_speed_);//FORWARD CH_3
		MotoDSetSpeed(1,0);//BACKWARD CH_4
	}
	//DOWM_RIGHT
	if((PS2_Data.Rocker_LX == 127)&&(PS2_Data.Rocker_LY == -127))
	{
		MotoASetSpeed(1,0);//BACKWARD CH_1
		MotoBSetSpeed(1,_speed_);//BACKWARD CH_2
		MotoCSetSpeed(1,0);//BACKWARD CH_3
		MotoDSetSpeed(1,_speed_);//BACKWARD CH_4
	}
	//CCW
	if((PS2_Data.Rocker_RX == -127)&&(PS2_Data.Rocker_RY == 0))
	{
		MotoASetSpeed(1,_speed_);//BACKWARD CH_1
		MotoBSetSpeed(1,_speed_);//BACKWARD CH_2
		MotoCSetSpeed(0,_speed_);//FORWARD CH_3
		MotoDSetSpeed(0,_speed_);//FORWARD CH_4
	}
	//CW
	if((PS2_Data.Rocker_RX == 127)&&(PS2_Data.Rocker_RY == 0))
	{
		MotoASetSpeed(0,_speed_);//FORWARD CH_1
		MotoBSetSpeed(0,_speed_);//FORWARD CH_2
		MotoCSetSpeed(1,_speed_);//BACKWARD CH_3
		MotoDSetSpeed(1,_speed_);//BACKWARD CH_4
	}
}


void Chasis_Speed(void)
{
	if((PS2_Data.Key_R_Up == 1)&&(PS2_Data.Key_R_Down == 0))
	{
		_speed_+=10;
		if(_speed_>2000)_speed_=2000;
	}
	if((PS2_Data.Key_R_Up == 0)&&(PS2_Data.Key_R_Down == 1))
	{
		_speed_-=10;
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
	motorA_pwm_PID_speed = wheelSpeedPidCalc(0, g_WheelSpeed[0],  motorA_target_speed);
	motorB_pwm_PID_speed = wheelSpeedPidCalc(1, g_WheelSpeed[1],  motorB_target_speed);
	motorC_pwm_PID_speed = wheelSpeedPidCalc(2, g_WheelSpeed[2],  motorC_target_speed);
	motorD_pwm_PID_speed = wheelSpeedPidCalc(3, g_WheelSpeed[3],  motorD_target_speed);
}







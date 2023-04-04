#include "./motor.h"
#include "./pid.h"

extern uint16_t g_WheelSpeed[4];

/*
*********************************************************************************************************
*	�� �� ��: MotorControl
*	����˵��: ����˶�����
*	��    ��: _ucAngularDirectionת����,_ucAngularSpeedת���ٶ�, _ucMotionDirection�˶�����, _usMotionSpeed�˶��ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MotorControl(uint8_t _ucAngularDirection, uint16_t _ucAngularSpeed, uint8_t _ucMotionDirection, uint16_t _usMotionSpeed)
{
    uint16_t _usMotorA_Speed = 0;
    uint16_t _usMotorB_Speed = 0;
    uint16_t _usMotorC_Speed = 0;
    uint16_t _usMotorD_Speed = 0;

    uint16_t _usMotorA_PWM = 0;
    uint16_t _usMotorB_PWM = 0;
    uint16_t _usMotorC_PWM = 0;
    uint16_t _usMotorD_PWM = 0;

    uint8_t _ucMotorA_Direction = 0;
    uint8_t _ucMotorB_Direction = 0;
    uint8_t _ucMotorC_Direction = 0;
    uint8_t _ucMotorD_Direction = 0;

    uint16_t _usLinearSpeed = 0; //���ݽ��ٶȼ�������ٶ�

    if((_ucAngularSpeed == 0) && (_usMotionSpeed == 0))//���趨�Ľ��ٶȻ����˶��ٶ�Ϊ0ʱ ��PID���ۼ���������0
    {
        PID_Param_SetZero();

    }

    if(_usMotionSpeed >= AUTO_SPEED_MAX)//��ʻ�ٶ�����
    {
        _usMotionSpeed = AUTO_SPEED_MAX;
    }

    if(_ucAngularSpeed == 0)//ֱ����ʻ
    {
        if(_ucMotionDirection == 0)
        {
            _ucMotorA_Direction = 0;
            _ucMotorB_Direction = 0;
            _ucMotorC_Direction = 1;
            _ucMotorD_Direction = 1;
        }
        else
        {
            _ucMotorA_Direction = 1;
            _ucMotorB_Direction = 1;
            _ucMotorC_Direction = 0;
            _ucMotorD_Direction = 0;
        }
        _usMotorA_Speed = _usMotionSpeed;
        _usMotorB_Speed = _usMotionSpeed;
        _usMotorC_Speed = _usMotionSpeed;
        _usMotorD_Speed = _usMotionSpeed;
    }
    else//��ֱ����ʻ
    {
        _usLinearSpeed = (uint16_t)(_ucAngularSpeed * 0.01 * (TIRE_SPACE * TIRE_SPACE + WHEELBASE * WHEELBASE) / (2 * TIRE_SPACE));
        
        if(_ucAngularDirection == 0)//��ת��
        {
            if(_ucMotionDirection == 0)//ǰ���˶�
            {
                _ucMotorC_Direction  = 1;
                _ucMotorD_Direction = _ucMotorC_Direction;//ͬһ�������˶�������ͬ

                _usMotorC_Speed = _usLinearSpeed + _usMotionSpeed;

                _usMotorD_Speed = _usMotorC_Speed;//ͬһ�������˶��ٶ����

                if(_usMotionSpeed >= _usLinearSpeed)
                {
                    _ucMotorA_Direction = 0;
                    _ucMotorB_Direction = _ucMotorA_Direction;
                    _usMotorA_Speed = _usMotionSpeed - _usLinearSpeed;
                    _usMotorB_Speed = _usMotorA_Speed;
                }
                else
                {
                    _ucMotorA_Direction = 1;
                    _ucMotorB_Direction = _ucMotorA_Direction;
                    _usMotorA_Speed     = _usLinearSpeed - _usMotionSpeed;
                    _usMotorB_Speed     = _usMotorA_Speed;

                }

            }
            else//�����˶�
            {
                _ucMotorC_Direction = 0;
                _ucMotorD_Direction = _ucMotorC_Direction;//ͬһ�������˶�������ͬ
                _usMotorC_Speed = _usLinearSpeed + _usMotionSpeed;
                _usMotorD_Speed = _usMotorC_Speed; //ͬһ�������˶��ٶ����

                if(_usMotionSpeed >= _usLinearSpeed)
                {
                    _ucMotorA_Direction = 1;
                    _ucMotorB_Direction = _ucMotorA_Direction;
                    _usMotorA_Speed = _usMotionSpeed - _usLinearSpeed;
                    _usMotorB_Speed = _usMotorA_Speed;
                }
                else
                {
                    _ucMotorA_Direction = 0;
                    _ucMotorB_Direction = _ucMotorA_Direction;
                    _usMotorA_Speed     = _usLinearSpeed - _usMotionSpeed;
                    _usMotorB_Speed     = _usMotorA_Speed;

                }

            }


        }
        else//��ת��
        {
            if(_ucMotionDirection == 0) //ǰ���˶�
            {
                _ucMotorA_Direction = 0;
                _ucMotorB_Direction = _ucMotorA_Direction;//ͬһ�������˶�������ͬ
                _usMotorA_Speed =  _usLinearSpeed + _usMotionSpeed;
                _usMotorB_Speed =  _usMotorA_Speed;//ͬһ�������˶��ٶ����
                if(_usMotionSpeed >= _usLinearSpeed)
                {
                    _ucMotorC_Direction = 1;
                    _ucMotorD_Direction = _ucMotorC_Direction;
                    _usMotorC_Speed = _usMotionSpeed - _usLinearSpeed;
                    _usMotorD_Speed = _usMotorC_Speed;
                }
                else
                {
                    _ucMotorC_Direction = 0;
                    _ucMotorD_Direction = _ucMotorC_Direction;
                    _usMotorC_Speed = _usLinearSpeed - _usMotionSpeed;
                    _usMotorD_Speed = _usMotorC_Speed;

                }

            }
            else//�����˶�
            {
                _ucMotorA_Direction = 1;
                _ucMotorB_Direction = _ucMotorA_Direction;//ͬһ�������˶�������ͬ
                _usMotorA_Speed = _usLinearSpeed + _usMotionSpeed;
                _usMotorB_Speed = _usMotorA_Speed;//ͬһ�������˶��ٶ����

                if(_usMotionSpeed >= _usLinearSpeed)
                {
                    _ucMotorC_Direction = 0;
                    _ucMotorD_Direction = _ucMotorC_Direction;
                    _usMotorC_Speed = _usMotionSpeed - _usLinearSpeed;
                    _usMotorD_Speed = _usMotorC_Speed;
                }
                else
                {
                    _ucMotorC_Direction = 1;
                    _ucMotorD_Direction = _ucMotorC_Direction;
                    _usMotorC_Speed = _usLinearSpeed - _usMotionSpeed;
                    _usMotorD_Speed = _usMotorC_Speed;
                }
            }
        }
    }
    _usMotorA_PWM = wheelSpeedPidCalc(0, g_WheelSpeed[0],  _usMotorA_Speed);//ִ��PID����
    _usMotorB_PWM = _usMotorA_PWM;//ͬһ�������ٶ����
    _usMotorC_PWM = wheelSpeedPidCalc(2, g_WheelSpeed[2],  _usMotorC_Speed);//ִ��PID����
    _usMotorD_PWM = _usMotorC_PWM; //ͬһ�������ٶ����
		printf("%d   %d   %d  %d   %d   %d   %d  %d   %d   %d   %d  %d\r\n",_usMotorA_Speed,_usMotorB_Speed,_usMotorC_Speed,_usMotorD_Speed,_usMotorA_PWM,_usMotorB_PWM,_usMotorC_PWM,_usMotorD_PWM,g_WheelSpeed[0],g_WheelSpeed[1],g_WheelSpeed[2],g_WheelSpeed[3]);

    //����ٶ�Ŀ���ٶ�Ϊ0ʱ�����ö�ӦPWM=0
    if(_usMotorA_Speed == 0)
    {
        _usMotorA_PWM = 0;
    }
    if(_usMotorB_Speed == 0)
    {
        _usMotorB_PWM = 0;
    }
    if(_usMotorC_Speed == 0)
    {
        _usMotorC_PWM = 0;
    }
    if(_usMotorD_Speed == 0)
    {
        _usMotorD_PWM = 0;
    }


    //����PID�����PWMֵ�������
    MotoASetSpeed(_ucMotorA_Direction, _usMotorA_PWM);
    MotoBSetSpeed(_ucMotorB_Direction, _usMotorB_PWM);
    MotoCSetSpeed(_ucMotorC_Direction, _usMotorC_PWM);
    MotoDSetSpeed(_ucMotorD_Direction, _usMotorD_PWM);

}
/*
*********************************************************************************************************
*	�� �� ��: MotorControl_Ps2
*	����˵��: �ֱ�����ת��Ϊʵ���˶��ٶ�
*	��    ��: _Ps2PadXValue�ֱ�X�����ֵ _Ps2PadYValue�ֱ�Y�����ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorControl_Ps2(uint8_t _Ps2PadXValue,uint8_t  _Ps2PadYValue)
{
	uint8_t _ps2AngularDirection=0;
	uint16_t _ps2AngularSpeed=0;
	uint8_t _ps2MotionDirection=0;
	uint16_t _ps2MotionSpeed=0;
	  
	if(_Ps2PadXValue<=138&_Ps2PadXValue>=118)//ֱ����ʻ
	{
	
			_ps2AngularDirection=0;
			_ps2AngularSpeed=0;
	}
		if(_Ps2PadXValue<118)//��ת����ʻ
	{
		_ps2AngularDirection=0;
		
		_ps2AngularSpeed=(uint8_t)((127-_Ps2PadXValue)*ANGULAR_SPEED_MAX/127);
	}
	if(_Ps2PadXValue>138)//��ת����ʻ
	{
		_ps2AngularDirection=1;
		_ps2AngularSpeed=(_Ps2PadXValue-127)*ANGULAR_SPEED_MAX/127;
	}
		if(_Ps2PadYValue<=138&_Ps2PadYValue>=118)//ֱ����ʻ
	{
	
			_ps2MotionDirection=0;
			_ps2MotionSpeed=0;
	}
			if(_Ps2PadYValue<118)//ǰ��
	{
			_ps2MotionDirection=0;
		
		_ps2MotionSpeed=(uint8_t)((127-_Ps2PadYValue)*PS2_SPEED_MAX/127);
	}
			if(_Ps2PadYValue>138)//����
	{
			_ps2MotionDirection=1;
		
		_ps2MotionSpeed=(uint8_t)((_Ps2PadYValue-127)*PS2_SPEED_MAX/127);
	}
        MotorControl(_ps2AngularDirection, _ps2AngularSpeed, _ps2MotionDirection, _ps2MotionSpeed);
}
























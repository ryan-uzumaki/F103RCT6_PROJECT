/*
*********************************************************************************************************
*
*	ģ������ : ת��������
*	�ļ����� : steercontrol.c
*	��    �� : V1.0
*	˵    �� :
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "includes.h"

/*
*********************************************************************************************************
*	�� �� ��: EpsInit
*	����˵��: ת��ϵͳ��ʼ����ʹ�������90��λ�ã�ǰ�ְ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void EpsInit(void)
{
    servoSetPluse(1, EPS_ZEROVALUE);//ʹ�������90��λ�ã�ǰ�ְ���
}

/*
*********************************************************************************************************
*	�� �� ��: EpsSteerControl_Ps2
*	����˵��: �ֱ�ң��ת�����
*	��    ��: _Ps2PadXValue �ֱ���ҡ��X�᷽���ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ps2_epsSteerControl(uint8_t _Ps2PadXValue)
{

    uint16_t _pulse = EPS_ZEROVALUE;

    _pulse = EPS_LVALUE + (EPS_RVALUE - EPS_LVALUE) * (_Ps2PadXValue - 0) / 255; //�����ֱ��г̣�ת��Χ������ռ�ձ�


    servoSetPluse(1, _pulse);
}
/*
*********************************************************************************************************
*	�� �� ��: EpsSteerControl_Auto
*	����˵��: �Զ���ʻת�����
*	��    ��: _SteerDirectionת���� _SteerAngleת��Ƕ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void auto_epsSteerControl(uint8_t _ucSteerDirection, uint8_t _ucSteerAngle)
{
    if(_ucSteerDirection == 0) //��ת
    {
        uint16_t _pulse = EPS_ZEROVALUE;

        _pulse = EPS_ZEROVALUE - (EPS_ZEROVALUE - EPS_LVALUE) * _ucSteerAngle / EPS_RANGE;

        servoSetPluse(1, _pulse);

    }
    if(_ucSteerDirection == 1) //��ת
    {

        uint16_t _pulse = EPS_ZEROVALUE;

        _pulse = EPS_ZEROVALUE + (EPS_RVALUE - EPS_ZEROVALUE) * _ucSteerAngle / EPS_RANGE;

        servoSetPluse(1, _pulse);

    }

}





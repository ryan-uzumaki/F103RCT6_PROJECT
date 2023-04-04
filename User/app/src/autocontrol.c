/*
*********************************************************************************************************
*
*	ģ������ : �Զ���ʻ����
*	�ļ����� : autocontol.c
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
*	�� �� ��: AutoControl_UartMsg
*	����˵��: �������λ�����յ���ָ�������ת���ٶȿ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void auto_ControlCarCmdHandle()
{
    uint8_t  _ucAngularDirection = 0;
    uint16_t _ucAngularSpeed     = 0;

    uint8_t   _ucMotionDirection = 0;
    uint16_t _ucMotionSpeed      = 0;

    if(g_uartFrame.code == 01)
    {
        _ucMotionDirection  = g_uartFrame.buf[1];
        _ucMotionSpeed      = g_uartFrame.buf[2] * 256 + g_uartFrame.buf[3];
        _ucAngularDirection = g_uartFrame.buf[7];
        _ucAngularSpeed     = g_uartFrame.buf[8] * 256 + g_uartFrame.buf[9];

        MotorControl(_ucAngularDirection, _ucAngularSpeed, _ucMotionDirection, _ucMotionSpeed);
    }

}
/*
*********************************************************************************************************
*	�� �� ��: AutoControl_CarStop
*	����˵��: ͣ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void auto_ControlCarStop()
{
    auto_epsSteerControl(0, 0);
    MotoASetSpeed(0, 0);
    MotoBSetSpeed(0, 0);
    MotoCSetSpeed(0, 0);
    MotoDSetSpeed(0, 0);
    PID_Param_SetZero();
}





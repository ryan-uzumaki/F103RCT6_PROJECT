#include "./bsp_encoder.h"

#define   REDUCTION_RATIO    30//������ٱ�
Encoder_t g_EncoderValue;
uint16_t g_WheelSpeed[4] = {0, 0, 0, 0} ; //�����е�ÿһ��Ԫ�طֱ����һ������,���ڴ�ų���ת��



/*
*********************************************************************************************************
*	�� �� ��: GetSpeedInfo
*	����˵��: �ѱ�������õ�ֵת��ΪС��ʵ���ٶ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void GetSpeedInfo(uint16_t* _speed, uint16_t _EncoderDirection1, uint16_t _EncoderDirection2)
{
    uint16_t _encoder = 0;
    _encoder = _EncoderDirection1 > _EncoderDirection2 ? _EncoderDirection1 : _EncoderDirection2;
    *_speed = _encoder * 20 * 3.1416 * 80  / 330 > 1000 ? 1000 : _encoder * 20 * 3.1416 * 80  / 330; //80-��ֱ̥�� 330-���������� 20-��������ȡ������Ƶ��
//	printf("wheel_speed = %f\n",*_speed);
}



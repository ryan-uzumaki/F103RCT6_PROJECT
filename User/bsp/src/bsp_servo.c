/*
*********************************************************************************************************
*
*	ģ������ : �趨�����ռ�ձ�
*	�ļ����� : bsp_servo.c
*	��    �� : V1.0
*	˵    �� : 
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾  
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "bsp.h"
#include "includes.h"
uint16_t g_feedback_SteerAngle=0;
uint8_t g_feedback_SteerDirection=0;

/*
*********************************************************************************************************
*	�� �� ��: Servo1_SetPluse
*	����˵��: �趨���1��ռ�ձ�
*	��    ��: _pluse��ռ�ձ�=_pluse/20000��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void servoSetPluse(uint8_t _num, uint16_t _pluse)
{
	uint32_t _channel; 
    TIM_HandleTypeDef _temp;
    switch(_num)
    {
        case 1: 
            _temp = htimServo;
            _channel = TIM_CHANNEL_1;
            
        break;
        case 2:
            _temp = htimServo;
            _channel = TIM_CHANNEL_2;
        break;
        
        case 3:
            _temp = htimServo;
            _channel = TIM_CHANNEL_3;
        break;
        
        case 4:
             _temp   = htimServo;
            _channel = TIM_CHANNEL_4;
        break;
        
        case 5:
            
            _temp    = htimServo1;
            _channel = TIM_CHANNEL_4;
        break;
        
        defalut:
            
        break;
    
    }
    __HAL_TIM_SET_COMPARE(&_temp, _channel,_pluse);

	
	if(_pluse<=1500)
	{
        g_feedback_SteerDirection=0;
		g_feedback_SteerAngle=(uint16_t)((EPS_ZEROVALUE-_pluse)*EPS_RANGE)/(EPS_ZEROVALUE-EPS_LVALUE);

	}
	if(_pluse>1500)
	{
		g_feedback_SteerDirection=1;
		g_feedback_SteerAngle=(uint16_t)((_pluse-EPS_ZEROVALUE)*EPS_RANGE)/(EPS_RVALUE-EPS_ZEROVALUE);
	}

 
}



#if 1
/*
*********************************************************************************************************
*	�� �� ��: Servo2_SetPluse
*	����˵��: �趨���3��ռ�ձ�
*	��    ��: _pluse��ռ�ձ�=_pluse/20000��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Servo2_SetPluse(uint16_t _pluse)
{	  
	__HAL_TIM_SET_COMPARE(&htimServo, TIM_CHANNEL_2, _pluse);
}
/*
*********************************************************************************************************
*	�� �� ��: Servo3_SetPluse
*	����˵��: �趨���3��ռ�ձ�
*	��    ��: _pluse��ռ�ձ�=_pluse/20000��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Servo3_SetPluse(uint16_t _pluse)
{	  
	__HAL_TIM_SET_COMPARE(&htimServo, TIM_CHANNEL_3, _pluse);

}
/*
*********************************************************************************************************
*	�� �� ��: Servo4_SetPluse
*	����˵��: �趨���4��ռ�ձ�
*	��    ��: _pluse��ռ�ձ�=_pluse/20000��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Servo4_SetPluse(uint16_t _pluse)
{	  	
	__HAL_TIM_SET_COMPARE(&htimServo, TIM_CHANNEL_4, _pluse);	
 
}
/*
*********************************************************************************************************
*	�� �� ��: Servo5_SetPluse
*	����˵��: �趨���5��ռ�ձ�
*	��    ��: _pluse��ռ�ձ�=_pluse/20000��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Servo5_SetPluse(uint16_t _pluse)
{	  		
		__HAL_TIM_SET_COMPARE(&htimServo1, TIM_CHANNEL_1, _pluse);
}
#endif

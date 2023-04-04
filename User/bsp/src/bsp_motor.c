#include "./bsp_motor.h"

/*
*********************************************************************************************************
*	�� �� ��: MotorA_Forward
*	����˵��: ���A��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorA_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 , GPIO_PIN_SET);

}
/*
*********************************************************************************************************
*	�� �� ��: MotorA_Forward
*	����˵��: ���A��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorA_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 , GPIO_PIN_RESET);

}
/*
*********************************************************************************************************
*	�� �� ��: MotorB_Forward
*	����˵��: ���B��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorB_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3 , GPIO_PIN_SET);

}
/*
*********************************************************************************************************
*	�� �� ��: MotorB_Backward
*	����˵��: ���B��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorB_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3 , GPIO_PIN_RESET);
	/*
*********************************************************************************************************
*	�� �� ��: MotorC_Forward
*	����˵��: ���C��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

}void MotorC_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 , GPIO_PIN_SET);

}
	/*
*********************************************************************************************************
*	�� �� ��: MotorC_Backward
*	����˵��: ���C��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorC_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 , GPIO_PIN_RESET);

}
	/*
*********************************************************************************************************
*	�� �� ��: MotorD_Forward
*	����˵��: ���D��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorD_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 , GPIO_PIN_SET);

}
	/*
*********************************************************************************************************
*	�� �� ��: MotorD_Backward
*	����˵��: ���D��ת
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MotorD_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 , GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 , GPIO_PIN_RESET);

}

/*
*********************************************************************************************************
*	�� �� ��: MotoASetSpeed
*	����˵��: A�����ռ�ձ�����
*	��    ��: _direction ���˶����� 00��ʾ��ת 01��ʾ��ת _speed��ռ�ձ�ֵ ��Χ0~2000
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MotoASetSpeed(int8_t _direction,int16_t _speed)
{
    if(_direction == 0)
			
    {
			
			MotorA_Forward();
			
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, abs(_speed));

    
    }
    else
    {
			MotorA_Backward();
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, abs(_speed));
    }

}

/*
*********************************************************************************************************
*	�� �� ��: MotoBSetSpeed
*	����˵��: B�����ռ�ձ�����
*	��    ��: _direction ���˶����� 00��ʾ��ת 01��ʾ��ת _speed��ռ�ձ�ֵ ��Χ0~2000
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MotoBSetSpeed(int8_t _direction,int16_t _speed)
{
    if(_direction == 0)
    {
			MotorB_Forward();
			
     __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, abs(_speed));
    
    }
    else
    {
		MotorB_Backward();
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, abs(_speed));
    }

}
/*
*********************************************************************************************************
*	�� �� ��: MotoCSetSpeed
*	����˵��: C�����ռ�ձ�����
*	��    ��: _direction ���˶����� 00��ʾ��ת 01��ʾ��ת _speed��ռ�ձ�ֵ ��Χ0~2000
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MotoCSetSpeed(int8_t _direction,int16_t _speed)
{
    if(_direction==0)
    {

				MotorC_Forward();
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, abs(_speed));
    
    }
    else
    {
			MotorC_Backward();
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, abs(_speed));
    }

}
/*
*********************************************************************************************************
*	�� �� ��: MotoDSetSpeed
*	����˵��: D�����ռ�ձ�����
*	��    ��: _direction ���˶����� 00��ʾ��ת 01��ʾ��ת _speed��ռ�ձ�ֵ ��Χ0~2000
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void MotoDSetSpeed(int8_t _direction,int16_t _speed)
{
    if(_direction==0)
    {
		MotorD_Forward();
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, abs(_speed));
    
    }
    else
    {
		MotorD_Backward();
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, abs(_speed));
    }

}


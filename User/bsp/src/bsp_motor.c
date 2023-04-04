#include "./bsp_motor.h"

/*
*********************************************************************************************************
*	函 数 名: MotorA_Forward
*	功能说明: 电机A正转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorA_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 , GPIO_PIN_SET);

}
/*
*********************************************************************************************************
*	函 数 名: MotorA_Forward
*	功能说明: 电机A反转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorA_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 , GPIO_PIN_RESET);

}
/*
*********************************************************************************************************
*	函 数 名: MotorB_Forward
*	功能说明: 电机B正转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorB_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3 , GPIO_PIN_SET);

}
/*
*********************************************************************************************************
*	函 数 名: MotorB_Backward
*	功能说明: 电机B反转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorB_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3 , GPIO_PIN_RESET);
	/*
*********************************************************************************************************
*	函 数 名: MotorC_Forward
*	功能说明: 电机C正转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

}void MotorC_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 , GPIO_PIN_SET);

}
	/*
*********************************************************************************************************
*	函 数 名: MotorC_Backward
*	功能说明: 电机C反转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorC_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 , GPIO_PIN_RESET);

}
	/*
*********************************************************************************************************
*	函 数 名: MotorD_Forward
*	功能说明: 电机D正转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorD_Forward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 , GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 , GPIO_PIN_SET);

}
	/*
*********************************************************************************************************
*	函 数 名: MotorD_Backward
*	功能说明: 电机D反转
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MotorD_Backward(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 , GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 , GPIO_PIN_RESET);

}

/*
*********************************************************************************************************
*	函 数 名: MotoASetSpeed
*	功能说明: A电机的占空比设置
*	形    参: _direction ：运动方向 00表示正转 01表示反转 _speed：占空比值 范围0~2000
*	返 回 值: 无
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
*	函 数 名: MotoBSetSpeed
*	功能说明: B电机的占空比设置
*	形    参: _direction ：运动方向 00表示正转 01表示反转 _speed：占空比值 范围0~2000
*	返 回 值: 无
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
*	函 数 名: MotoCSetSpeed
*	功能说明: C电机的占空比设置
*	形    参: _direction ：运动方向 00表示正转 01表示反转 _speed：占空比值 范围0~2000
*	返 回 值: 无
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
*	函 数 名: MotoDSetSpeed
*	功能说明: D电机的占空比设置
*	形    参: _direction ：运动方向 00表示正转 01表示反转 _speed：占空比值 范围0~2000
*	返 回 值: 无
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


#include "./bsp_encoder.h"

#define   REDUCTION_RATIO    30//电机减速比
Encoder_t g_EncoderValue;
uint16_t g_WheelSpeed[4] = {0, 0, 0, 0} ; //数组中的每一个元素分别代表一个车轮,用于存放车轮转速

static uint16_t s_EncodeValue[8] = {0};

/*
*********************************************************************************************************
*	函 数 名: GetSpeedInfo
*	功能说明: 把编码器测得的值转化为小车实际速度
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

void GetSpeedInfo(uint16_t* _speed, uint16_t _EncoderDirection1, uint16_t _EncoderDirection2)
{
    uint16_t _encoder = 0;
    _encoder = _EncoderDirection1 > _EncoderDirection2 ? _EncoderDirection1 : _EncoderDirection2;
    *_speed = _encoder * 20 * 3.1416 * 65  / 330; //65-轮胎直径 330-编码器线数 20-编码器获取方波的频率

}

/*
*********************************************************************************************************
*	函 数 名: HAL_TIM_PeriodElapsedCallback
*	功能说明: 定时器5更新中断
*	形    参: htim
*	返 回 值: 无
*********************************************************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    GetSpeedInfo(g_WheelSpeed, s_EncodeValue[0], s_EncodeValue[1]);
    GetSpeedInfo(g_WheelSpeed + 1, s_EncodeValue[2], s_EncodeValue[3]);

    GetSpeedInfo(g_WheelSpeed + 2, s_EncodeValue[4], s_EncodeValue[5]);
    GetSpeedInfo(g_WheelSpeed + 3, s_EncodeValue[6], s_EncodeValue[7]);

//     printf("---%d-%d---\r\n", g_EncoderValue.RightEncoderValue1.speed,g_EncoderValue.RightEncoderValue1.dir);
//       printf("---%d---%d------%d---%d---\r\n",s_EncodeValue[3], s_EncodeValue[4],s_EncodeValue[7], s_EncodeValue[8]);
    for(int i = 0; i < 8; i ++)//每次更新中断时，清空：s_EncodeValue[i]
    {
        s_EncodeValue[i] = 0;

    }
}
/*
*********************************************************************************************************
*	函 数 名: HAL_TIM_IC_CaptureCallback
*	功能说明: TIM_IC回调函数
*	形    参: htim
*	返 回 值: 无
*********************************************************************************************************
*/

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim)/*输入捕获中断回调函数*/
{
    if(htim->Instance == TIM5)/*判断定时器*/
    {

        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)/*判断通道*/
        {
            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
            {
                g_EncoderValue.MotorA_EncoderValue.dir = 1;
                s_EncodeValue[0] ++;

            }
            else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
            {
                g_EncoderValue.MotorA_EncoderValue.dir = 0;
                s_EncodeValue[1] ++;

            }


        }

        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {

            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
            {
                g_EncoderValue.MotorB_EncoderValue.dir = 1;
                s_EncodeValue[2] ++;


            }
            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0)
            {
                g_EncoderValue.MotorB_EncoderValue.dir = 0;
                s_EncodeValue[3] ++;

            }

//           g_EncoderValue.LeftEncoderValue1.speed += s_EncodeValue[2] > s_EncodeValue[3] ? s_EncodeValue[2] : s_EncodeValue[3];
            //printf("---%d-%d---\r\n", g_EncoderValue.LeftEncoderValue1.speed,g_EncoderValue.LeftEncoderValue1.dir);
        }
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1)
            {
                g_EncoderValue.MotorC_EncoderValue.dir = 1;
                s_EncodeValue[4] ++;


            }
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0)
            {
                g_EncoderValue.MotorC_EncoderValue.dir = 0;
                s_EncodeValue[5] ++;

            }



        }

        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {

            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1)
            {
                g_EncoderValue.MotorD_EncoderValue.dir = 1;
                s_EncodeValue[6] ++;


            }
            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0)
            {
                g_EncoderValue.MotorD_EncoderValue.dir = 0;
                s_EncodeValue[7] ++;

            }

//           g_EncoderValue.LeftEncoderValue1.speed += s_EncodeValue[6] > s_EncodeValue[7] ? s_EncodeValue[6] : s_EncodeValue[7];
            //printf("---%d-%d---\r\n", g_EncoderValue.LeftEncoderValue1.speed,g_EncoderValue.LeftEncoderValue1.dir);
        }


    }


}


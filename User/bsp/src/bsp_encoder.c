#include "./bsp_encoder.h"

#define   REDUCTION_RATIO    30//电机减速比
Encoder_t g_EncoderValue;
uint16_t g_WheelSpeed[4] = {0, 0, 0, 0} ; //数组中的每一个元素分别代表一个车轮,用于存放车轮转速



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
    *_speed = _encoder * 20 * 3.1416 * 80  / 330 > 1000 ? 1000 : _encoder * 20 * 3.1416 * 80  / 330; //80-轮胎直径 330-编码器线数 20-编码器获取方波的频率
//	printf("wheel_speed = %f\n",*_speed);
}



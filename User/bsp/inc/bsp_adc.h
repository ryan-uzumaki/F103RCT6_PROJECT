

#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stdint.h"

/* ���ⲿ���õĺ������� */
void bsp_InitAdc(void); 				//ADCͨ����ʼ��
uint16_t getAdcvalue(uint32_t ch);    		        //���ĳ��ͨ��ֵ 
uint16_t getAdcAverageValue(uint32_t ch,uint8_t times);//�õ�ĳ��ͨ����������������ƽ��ֵ

#endif



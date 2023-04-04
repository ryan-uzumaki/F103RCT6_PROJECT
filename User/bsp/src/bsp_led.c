/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.c
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ��
*
*
*********************************************************************************************************
*/

#include "bsp.h"

#define ALL_LED_GPIO_CLK_ENABLE()	do{\
                                        __HAL_RCC_GPIOA_CLK_ENABLE();\
                                        __HAL_RCC_GPIOB_CLK_ENABLE();\
                                        __HAL_RCC_GPIOC_CLK_ENABLE();\
                                        __HAL_RCC_GPIOD_CLK_ENABLE();\
                                        __HAL_RCC_GPIOF_CLK_ENABLE();\
                                        }while(0);

#define GPIO_LED1	GPIOC
#define PIN_LED1	GPIO_PIN_14

//#define GPIO_LED2	GPIOB
//#define PIN_LED2	GPIO_PIN_7
                                      
	                                     

#define LED1_ON()  	   GPIO_LED1->BSRR = ((uint32_t)PIN_LED1 << 16U)				/* LED1 = 0 */
#define LED1_OFF()     GPIO_LED1->BSRR = PIN_LED1				/* LED1 = 1 */
                       
#define LED1_IS_ON()   ((GPIO_LED1->IDR & PIN_LED1) == 0)	/* ����ѵ���������1 */
                       
//#define LED2_ON()  	 GPIO_LED2->BSRR = ((uint32_t)PIN_LED2 << 16U)				/* LED1 = 0 */
//#define LED2_OFF()     GPIO_LED2->BSRR = PIN_LED2				/* LED1 = 1 */
//                       
//#define LED2_IS_ON()   ((GPIO_LED2->IDR & PIN_LED2) == 0)	/* ����ѵ���������1 */

                                    
/*
*********************************************************************************************************
*	�� �� ��: bsp_InitLed
*	����˵��: ����LEDָʾ����ص�GPIO,  �ú����� bsp_Init() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef gpio_init;

	/* ��1������GPIOʱ�� */
	ALL_LED_GPIO_CLK_ENABLE();
	
	
	
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;	/* ���ÿ�©��� */
	gpio_init.Pull = GPIO_NOPULL;			/* ���������費ʹ�� */
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;  /* GPIO�ٶȵȼ� */	
	gpio_init.Pin = PIN_LED1;	
	HAL_GPIO_Init(GPIO_LED1, &gpio_init);	

//    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;	/* ���ÿ�©��� */
//	gpio_init.Pull = GPIO_NOPULL;			/* ���������費ʹ�� */
//	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;  /* GPIO�ٶȵȼ� */	
//	gpio_init.Pin = PIN_LED2;	
//	HAL_GPIO_Init(GPIO_LED2, &gpio_init);	
	
	bsp_LedOff(1);
	//bsp_LedOff(2);
}


/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOn
*	����˵��: ����ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	switch(_no)
	{
		case 1:
			LED1_ON();
		break;
		case 2 :
			//LED2_ON();
		break;
		case 3:
			//LED3_ON();
		break;
		case 4 :
			//LED4_ON();
		break;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOff
*	����˵��: Ϩ��ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no)
{
	switch(_no)
	{
		case 1:
			LED1_OFF();
		break;
		case 2 :
			//LED2_OFF();
		break;
		case 3:
			//LED3_OFF();
		break;
		case 4 :
			//LED4_OFF();
		break;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedToggle
*	����˵��: ��תָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��������
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no)
{
	if (bsp_IsLedOn(_no))
	{
		bsp_LedOff(_no);
	}
	else
	{
		bsp_LedOn(_no);
	}
}


/*
*********************************************************************************************************
*	�� �� ��: bsp_IsLedOn
*	����˵��: �ж�LEDָʾ���Ƿ��Ѿ�������
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: 1��ʾ�Ѿ�������0��ʾδ����
*********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
	switch(_no)
	{
		case 1:
			return LED1_IS_ON();
		break;
		case 2 :
			//return LED2_IS_ON();
		break;
		case 3:
			//return LED3_IS_ON();
		break;
		case 4 :
			//return LED4_IS_ON();
		break;
	}
	return 0;
}






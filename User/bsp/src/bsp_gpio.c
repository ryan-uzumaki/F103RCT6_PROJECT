#include "bsp.h"
#include "relayControl.h"



/*********************************************************************************************************
*	�� �� ��: bsp_InitGpio
*	����˵��: GPIO��ʼ����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitGpio(void)
{
    GPIO_InitTypeDef gpio_init;
    /* ��1������GPIOʱ�� */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
        
    gpio_init.Mode  = GPIO_MODE_IT_RISING_FALLING;
    //gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Pull  = GPIO_NOPULL;
        
    
    gpio_init.Pin = GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOC, &gpio_init);	
        
    gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOA, &gpio_init);
    
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
        
    HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

/*********************************************************************************************************
*	�� �� ��: ReadGpioLevel
*	����˵��: ��ȡGPIO��״̬��
*	��    ��: _num ���ź�
*	�� �� ֵ: ����״̬
*********************************************************************************************************
*/
uint8_t ReadGpioLevel(uint8_t _num)
{
    uint8_t _gpioLevel = 0;
    switch(_num)
	{
        case 1: 
            _gpioLevel =  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
        break;
        case 2: 
            _gpioLevel =  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
        break;
        case 3: 
            _gpioLevel =  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        break;	
            case 4: 
            _gpioLevel =  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
        break;	
        default :
            _gpioLevel = 2;
	}
		
	return _gpioLevel;
}


/*********************************************************************************************************
*	�� �� ��: EXTI15_10_IRQHandler
*	����˵��: �ⲿ�ж�10 - 15��������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}

/*********************************************************************************************************
*	�� �� ��: EXTI1_IRQHandler
*	����˵��: �ⲿ�ж�1��������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void EXTI1_IRQHandler(void)
{
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

/*********************************************************************************************************
*	�� �� ��: HAL_GPIO_EXTI_Callback
*	����˵��: �ⲿ�жϻص�������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	status_t _status;
	if(GPIO_Pin == GPIO_PIN_14)
	{
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_RESET)
		SetStatus(0, 1);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_SET)
		SetStatus(0, 0);
		
	}
	else if(GPIO_Pin == GPIO_PIN_15)
	{
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET)
		SetStatus(1, 1);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET)
		SetStatus(1, 0);
		
	}
	else if(GPIO_Pin == GPIO_PIN_1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		SetStatus(3, 1);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
		SetStatus(3, 0);
	}

}


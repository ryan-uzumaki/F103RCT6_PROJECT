/*
*********************************************************************************************************
*
*	ģ������ : ��ʱ��PWM�����벶������ģ��
*	�ļ����� : bsp_timer.c
*	��    �� : V1.0
*	˵    �� : 
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾  
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "bsp.h"

#define MOTO_TIMx                           TIM3
#define MOTO_TIM_RCC_CLK_ENABLE()           __HAL_RCC_TIM3_CLK_ENABLE()
#define MOTO_TIM_RCC_CLK_DISABLE()          __HAL_RCC_TIM3_CLK_DISABLE()
#define MOTOAB_TIM_GPIO_RCC_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define MOTOCD_TIM_GPIO_RCC_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTOA_PWM_PORT                      GPIOA
#define MOTOA_PWM_PIN                       GPIO_PIN_6
#define MOTOB_PWM_PORT                      GPIOA
#define MOTOB_PWM_PIN                       GPIO_PIN_7
#define MOTOC_PWM_PORT                      GPIOB
#define MOTOC_PWM_PIN                       GPIO_PIN_0
#define MOTOD_PWM_PORT                      GPIOB
#define MOTOD_PWM_PIN                       GPIO_PIN_1



#define MOTO_ENCODER_TIMx                     TIM5
#define MOTO_ENCODER_TIM_RCC_CLK_ENABLE()      __HAL_RCC_TIM5_CLK_ENABLE()
#define MOTO_ENCODER_RCC_CLK_DISABLE()         __HAL_RCC_TIM5_CLK_DISABLE()
#define MOTO_ENCODER_GPIO_RCC_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

#define MOTOCD_ENCODER_TIMx                    TIM1
#define MOTOCD_ENCODER_TIM_RCC_CLK_ENABLE()    __HAL_RCC_TIM1_CLK_ENABLE()
#define MOTOCD_ENCODER_RCC_CLK_DISABLE()       __HAL_RCC_TIM1_CLK_DISABLE()
#define MOTOCD_ENCODER_GPIO_RCC_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()

#define MOTOA_ENCODER_PORT                     GPIOC
#define MOTOA_ENCODER_PIN                      GPIO_PIN_6
#define MOTOB_ENCODER_PORT                     GPIOC
#define MOTOB_ENCODER_PIN                      GPIO_PIN_8
#define MOTOC_ENCODER_PORT                     GPIOA
#define MOTOC_ENCODER_PIN                      GPIO_PIN_8
#define MOTOD_ENCODER_PORT                     GPIOA
#define MOTOD_ENCODER_PIN                      GPIO_PIN_10

#define STEERING1_PORT                         GPIOC
#define STEERING1_PIN                          GPIO_PIN_6
#define STEERING2_PORT                         GPIOC
#define STEERING2_PIN                          GPIO_PIN_7
#define STEERING3_PORT                         GPIOC
#define STEERING3_PIN                          GPIO_PIN_8
#define STEERING4_PORT                         GPIOC
#define STEERING4_PIN                          GPIO_PIN_9
#define STEERING5_PORT                         GPIOA
#define STEERING5_PIN                          GPIO_PIN_8

TimServo_t   g_Servo;

TIM_HandleTypeDef    htim4Motor;
TIM_HandleTypeDef    htim3Motor;
TIM_HandleTypeDef    htimServo;
TIM_HandleTypeDef    htimEncoder;
TIM_HandleTypeDef    htimEncoder_Motor;
TIM_HandleTypeDef    htimServo1;

/*********************************************************************************************************
*	�� �� ��: HAL_TIM_MspInit
*	����˵��: TIM���ų�ʼ��
*	��    ��: htim  ��ʱ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_TIM_MspInit(TIM_HandleTypeDef* htim)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    if(htim->Instance == TIM4)
    {
                
    }
    else if(htim->Instance == TIM3)
    {
				MOTOCD_TIM_GPIO_RCC_CLK_ENABLE();
        MOTOAB_TIM_GPIO_RCC_CLK_ENABLE();
        /* ��ʱ��ͨ��1��������IO��ʼ�� */
        GPIO_InitStruct.Pin = MOTOA_PWM_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MOTOA_PWM_PORT, &GPIO_InitStruct);
        
         /* ��ʱ��ͨ��2��������IO��ʼ�� */
        GPIO_InitStruct.Pin = MOTOB_PWM_PIN;
        HAL_GPIO_Init(MOTOB_PWM_PORT, &GPIO_InitStruct);

         /* ��ʱ��ͨ��2��������IO��ʼ�� */
        GPIO_InitStruct.Pin = MOTOC_PWM_PIN;
        HAL_GPIO_Init(MOTOC_PWM_PORT, &GPIO_InitStruct);
			         /* ��ʱ��ͨ��2��������IO��ʼ�� */
        GPIO_InitStruct.Pin = MOTOD_PWM_PIN;
        HAL_GPIO_Init(MOTOD_PWM_PORT, &GPIO_InitStruct);
    
    
    }
    else if(htim->Instance == TIM8)

    {
        MOTO_ENCODER_GPIO_RCC_CLK_ENABLE();
        /* ��ʱ��ͨ��1��������IO��ʼ�� */
        GPIO_InitStruct.Pin   = STEERING1_PIN | STEERING2_PIN | STEERING3_PIN | STEERING4_PIN;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(STEERING1_PORT, &GPIO_InitStruct);
    }
	 else if(htim->Instance == TIM1)

    {
        __HAL_RCC_GPIOA_CLK_ENABLE(); 
        /* ��ʱ��ͨ��1��������IO��ʼ�� */
        GPIO_InitStruct.Pin   = STEERING5_PIN;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(STEERING5_PORT, &GPIO_InitStruct);
        
    }
    else if(htim->Instance == TIM5)
    {

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /* ��ʱ��ͨ��1��������IO��ʼ�� */
        GPIO_InitStruct.Pin   = GPIO_PIN_0| GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        

    }
    
}
/*********************************************************************************************************
*	�� �� ��: bsp_InitTim8
*	����˵��: Tim8���ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitTim8(void)
{		
		TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
   
    __HAL_RCC_TIM8_CLK_ENABLE();//��ʱ��ʱ��ʹ��
    
	  htimServo.Instance          = TIM8;//
    htimServo.Init.Prescaler    = 72-1;//��Ƶϵ��
    htimServo.Init.CounterMode  = TIM_COUNTERMODE_UP;//����ģʽ
    htimServo.Init.Period       = 19999;  /*��װ��ֵ*/
    htimServo.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;/*ʱ�ӷ�Ƶ/1 */
    HAL_TIM_Base_Init(&htimServo);
    
	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;/*ʱ��Դ �ⲿʱ��*/
    HAL_TIM_ConfigClockSource(&htimServo, &sClockSourceConfig);/*����ʱ��Դ*/
    
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;/*����PWM1���ģʽ*/
    sConfigOC.Pulse = 0;/*����ռ�ձ�*/
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;/*����PWM1�������*/
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htimServo, &sConfigOC, TIM_CHANNEL_1);/*����PWM1���ͨ��*/
    
    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htimServo, &sConfigOC, TIM_CHANNEL_2);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htimServo, &sConfigOC, TIM_CHANNEL_3);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htimServo, &sConfigOC, TIM_CHANNEL_4);

    HAL_TIM_MspInit(&htimServo);      
    
      /* ����ͨ��PWM��� */
    HAL_TIM_PWM_Start(&htimServo,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htimServo,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htimServo,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htimServo,TIM_CHANNEL_4);
}
/*********************************************************************************************************
*	�� �� ��: bsp_InitTim1
*	����˵��: Tim1���ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitTim1(void)
{		
		TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
   
    __HAL_RCC_TIM1_CLK_ENABLE();
       	
		htimServo1.Instance          = TIM1;
    htimServo1.Init.Prescaler    = 72-1;
    htimServo1.Init.CounterMode  = TIM_COUNTERMODE_UP;
    htimServo1.Init.Period       = 19999;  /*1ms  1000 * 1us*/
    htimServo1.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htimServo1);
    
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htimServo1, &sClockSourceConfig);
    
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htimServo1, &sConfigOC, TIM_CHANNEL_1);
    
		


    HAL_TIM_MspInit(&htimServo1);

    /* ����ͨ��PWM��� */
    HAL_TIM_PWM_Start(&htimServo1,TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start(&htimServo1,TIM_CHANNEL_2);
//    HAL_TIM_PWM_Start(&htimServo1,TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htimServo1,TIM_CHANNEL_4);
}

/*********************************************************************************************************
*	�� �� ��: bsp_InitTim5
*	����˵��: Tim5���ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitTim5(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig   = {0};
    TIM_MasterConfigTypeDef sMasterConfig       = {0};
    TIM_IC_InitTypeDef sConfigIC                = {0};
   
    HAL_TIM_MspInit(&htimEncoder_Motor);
	__HAL_RCC_TIM5_CLK_ENABLE();

    
    htimEncoder_Motor.Instance           = TIM5;
    htimEncoder_Motor.Init.Prescaler     = 72 - 1;
    htimEncoder_Motor.Init.CounterMode   = TIM_COUNTERMODE_UP;
    htimEncoder_Motor.Init.Period        = 50000 - 1;
    htimEncoder_Motor.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htimEncoder_Motor.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    
    if(HAL_TIM_Base_Init(&htimEncoder_Motor) != HAL_OK)/*���ö�ʱ��ʱ��*/
    {
        Error_Handler(__FILE__, __LINE__);
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if(HAL_TIM_ConfigClockSource(&htimEncoder_Motor, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler(__FILE__,__LINE__);
    }
    
    if (HAL_TIM_IC_Init(&htimEncoder_Motor) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htimEncoder_Motor, &sMasterConfig) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 1;
    
    if (HAL_TIM_IC_ConfigChannel(&htimEncoder_Motor, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    if (HAL_TIM_IC_ConfigChannel(&htimEncoder_Motor, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    if (HAL_TIM_IC_ConfigChannel(&htimEncoder_Motor, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    if (HAL_TIM_IC_ConfigChannel(&htimEncoder_Motor, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    
    
    HAL_NVIC_SetPriority(TIM5_IRQn , 3, 0);
		
    HAL_NVIC_EnableIRQ(TIM5_IRQn );
    HAL_TIM_Base_Start_IT(&htimEncoder_Motor);
    

	HAL_TIM_IC_Start_IT(&htimEncoder_Motor, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htimEncoder_Motor, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htimEncoder_Motor, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htimEncoder_Motor, TIM_CHANNEL_4);  

}
/*********************************************************************************************************
*	�� �� ��: bsp_InitTim3
*	����˵��: Tim3���ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitTim3(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    

    htim3Motor.Instance          = MOTO_TIMx;
    htim3Motor.Init.Prescaler    = 1;
    htim3Motor.Init.CounterMode  = TIM_COUNTERMODE_UP;
    htim3Motor.Init.Period       = 2000;  /*1ms  1000 * 1us*/
    htim3Motor.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim3Motor);
    
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim3Motor, &sClockSourceConfig);
    
//    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//    HAL_TIMEx_MasterConfigSynchronization(&htim2MotoA, &sMasterConfig);
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim3Motor, &sConfigOC, TIM_CHANNEL_1);
    
    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim3Motor, &sConfigOC, TIM_CHANNEL_2);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim3Motor, &sConfigOC, TIM_CHANNEL_3);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim3Motor, &sConfigOC, TIM_CHANNEL_4);

    HAL_TIM_MspInit(&htim3Motor);
    
   
    
      /* ����ͨ��PWM��� */
    HAL_TIM_PWM_Start(&htim3Motor,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3Motor,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3Motor,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3Motor,TIM_CHANNEL_4);
    
  
    
}
/*********************************************************************************************************
*	�� �� ��: bsp_InitTim4
*	����˵��: Tim4���ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitTim4(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    

    htim4Motor.Instance          = TIM4;
    htim4Motor.Init.Prescaler    = 1;
    htim4Motor.Init.CounterMode  = TIM_COUNTERMODE_UP;
    htim4Motor.Init.Period       = 2000;  /*1ms  1000 * 1us*/
    htim4Motor.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim4Motor);
    
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim4Motor, &sClockSourceConfig);
    

    
    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim4Motor, &sConfigOC, TIM_CHANNEL_1);
    
    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim4Motor, &sConfigOC, TIM_CHANNEL_2);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim4Motor, &sConfigOC, TIM_CHANNEL_3);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim4Motor, &sConfigOC, TIM_CHANNEL_4);

    HAL_TIM_MspInit(&htim4Motor);
    
   
    
      /* ����ͨ��PWM��� */
    HAL_TIM_PWM_Start(&htim4Motor,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4Motor,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4Motor,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4Motor,TIM_CHANNEL_4);
    
}
/*********************************************************************************************************
*	�� �� ��: HAL_TIM_Base_MspInit
*	����˵��: ��ʱ������ʱ��ʹ��
*	��    ��: htim_base��ʱ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM4)
  {
    /* ������ʱ������ʱ��ʹ�� */
    __HAL_RCC_TIM4_CLK_ENABLE();
  }
  else if(htim_base->Instance==MOTO_TIMx)
  {
    MOTO_TIM_RCC_CLK_ENABLE();
  }
}
/*********************************************************************************************************
*	�� �� ��: HAL_TIM_Base_MspDeInit
*	����˵��: ��ʱ������ʱ�ӹر�
*	��    ��: htim_base��ʱ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM4)
  {
    /* ������ʱ������ʱ�Ӳ�ʹ�� */
    __HAL_RCC_TIM4_CLK_DISABLE();
  }
  else if(htim_base->Instance==MOTO_TIMx)
  {
    MOTO_TIM_RCC_CLK_DISABLE();
  }
} 




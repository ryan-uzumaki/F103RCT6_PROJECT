/*
*********************************************************************************************************
*
*	ģ������ : bsp����
*	�ļ����� : bsp_key.c
*	��    �� : V1.0
*	˵    �� : ����ɨ������
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾  
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "bsp.h"
#include "pid.h"
/*
*********************************************************************************************************
*	                                   ��������
*********************************************************************************************************
*/
static void SystemClock_Config(void);

/*
*********************************************************************************************************
*	�� �� ��: System_Init
*	����˵��: ϵͳ��ʼ������Ҫ��MPU��Cache��ϵͳʱ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void System_Init(void)
{
	
	/* 
       STM32F1xx HAL ���ʼ��
	   - ���ú���HAL_InitTick����ʼ���δ�ʱ���ж�1ms��
	   - ����NVIV���ȼ�����Ϊ4��
	 */
	HAL_Init();

	/* 
       ����ϵͳʱ�ӵ�72MHz
       - �л�ʹ��HSE��
       - �˺��������ȫ�ֱ���SystemCoreClock������������HAL_InitTick��
    */
	SystemClock_Config();

	/* 
	   Event Recorder��
	   - �����ڴ���ִ��ʱ�������MDK5.25�������ϰ汾��֧�֣�IAR��֧�֡�
	   - Ĭ�ϲ����������Ҫʹ�ܴ�ѡ���ؿ�V7�������û��ֲ��8��
	*/	
#if Enable_EventRecorder == 1  
	/* ��ʼ��EventRecorder������ */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif

}
/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ�����е�Ӳ���豸���ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����ֻ��Ҫ����һ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/



void bsp_Init(void)
{
	bsp_InitLed();
 
    bsp_InitDWT();
    bsp_InitUart();
    
   
	bsp_InitTim3();
	bsp_InitTim4();
	bsp_InitTim8();
	bsp_InitTim1();
	bsp_InitMotorEnGpio();

	bsp_InitEncoder();
    PS2_init();
	bsp_InitPid();
	MPU_IIC_Init();
	bsp_InitAdc();
	bsp_InitKey();
	bsp_InitOled();
	bsp_InitCan();
	
	    /*���OLED�豸�Ƿ����*/
//    if(i2c_CheckDevice(0x78) == 0)
//    {
//    
//        printf("---0x78---\r\n");
//    }
		
		
}

/*
*********************************************************************************************************
*	�� �� ��: SystemClock_Config
*	����˵��: ��ʼ��ϵͳʱ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler(__FILE__, __LINE__);
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler(__FILE__, __LINE__);
  }
}

/*
*********************************************************************************************************
*	�� �� ��: Error_Handler
*	��    ��: file : Դ�����ļ����ơ��ؼ��� __FILE__ ��ʾԴ�����ļ�����
*			  line �������кš��ؼ��� __LINE__ ��ʾԴ�����к�
*	�� �� ֵ: ��
*		Error_Handler(__FILE__, __LINE__);
*********************************************************************************************************
*/
void Error_Handler(char *file, uint32_t line)
{
	/* 
		�û���������Լ��Ĵ��뱨��Դ�����ļ����ʹ����кţ����罫�����ļ����кŴ�ӡ������
	*/	
	printf("Wrong parameters value: file %s on line %d\r\n", file, line); 
	
	
	/* ����һ����ѭ��������ʧ��ʱ������ڴ˴��������Ա����û���� */
	if (line == 0)
	{
		return;
	}
	
	while(1)
	{
	}
}



/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	;
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */
}


/*
*********************************************************************************************************
*	�� �� ��: bsp_ResetSystem
*	����˵��: CPU��λ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_ResetSystem(void)
{
	NVIC_SystemReset();	/* ��λCPU */
}





/*
*********************************************************************************************************
*
*	ģ������ : ������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� :
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "includes.h"
/*
**********************************************************************************************************
											�궨��
**********************************************************************************************************
*/

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static void AppTaskCreate(void);
static void AppTaskControl(void* argument);
static void AppTaskMsgBack(void* argument);
static void AppTaskStart(void* argument);
static void AppTimerHanle(void* argument);

uint8_t ble_control(void);
/*
**********************************************************************************************************
											 ����
**********************************************************************************************************
*/


/*��ʱ����ID*/
osTimerId_t g_TimerHand_Id;

/* ������������� */
const osThreadAttr_t ThreadStart_Attr =
{

    .name = "osRtxStartThread",
    .attr_bits = osThreadDetached,
    .priority = osPriorityNormal3,
    .stack_size = 4096,
};


const osThreadAttr_t ThreadControl_Attr =
{
    .name = "osRtxThreadControl",
    .attr_bits = osThreadDetached,
    .priority = osPriorityNormal2,
    .stack_size = 4096,
};

const osThreadAttr_t ThreadMsgBack_Attr =
{
    .name = "osRtxThreadMsgBack",
    .attr_bits = osThreadDetached,
    .priority = osPriorityNormal1,
    .stack_size = 1024,
};


/* ������ */
osThreadId_t ThreadIdTaskControl = NULL;
osThreadId_t ThreadIdTaskMsgBack = NULL;
osThreadId_t ThreadIdStart       = NULL;


/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ���������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

int main(void)
{

    System_Init();

    osKernelInitialize();

    ThreadIdStart = osThreadNew(AppTaskStart, NULL, &ThreadStart_Attr);

    osKernelStart();
    while(1);
}

/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��Ϣ���д���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AppObjCreate(void)
{


}


/*
*********************************************************************************************************
*	�� �� ��: AppTaskMsgBack
*	����˵��: ���ݷ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

static void AppTaskMsgBack(void* argument)
{


    while(1)
    {




        osDelay(5);
    }

}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskControl
*	����˵��: �˶�����
*	��    ��: ��
*	�� �� ֵ: ��
*   �� �� ��: osPriorityNormal (��ֵԽС���ȼ�Խ�ͣ������uCOS�෴)
*********************************************************************************************************
*/


static void AppTaskControl(void* argument)
{

    uint8_t _disLinkCnt = 0;
    uint8_t ucKeyCode ;
    LinkStatus_t _linkStatus;
	    Ps2Pad_t _left  = {0};
    Ps2Pad_t _right = {0};
    while(1)
    {

        /*ͨ����������С��*/
        if(ble_control() == 1)
        {


        }
		/*ͨ��PS2�ֱ�����С��*/
		/*��ȡPS2����*/
//		__set_PRIMASK(1);
//				Ps2ClearData();
//				Ps2GetData();
//			Ps2DataKey();
//		__set_PRIMASK(0);	

//        if( (Ps2CheckMode() == 1) && (Ps2_DisLinkStatus()== 0) ) /*�ֱ�ģʽ*/
//        {				
//					/*�ֱ�����*/

//            Ps2GetAnalogValue(&_left, &_right);					
////					printf("_keyValue_X: %d _keyValue_Y: %d \r\n", _left.Ps2PadXValue,_right.Ps2PadYValue);
//					  MotorControl_Ps2(_left.Ps2PadXValue,_right.Ps2PadYValue);					

//        }
 


        osDelay(10);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStart
*	����˵��: ����������������BSP����������
*	��    ��: ��
*	�� �� ֵ: ��
*   �� �� ��: osPriorityNormal4
*********************************************************************************************************
*/


void AppTaskStart(void* argument)
{
    const uint16_t usFrequency = 100; /* �ӳ����� */

    uint32_t tick;

    bsp_Init();


    /*jlink��ӡ*/
    /* ����ͨ��0����������*/
    SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

    /* ����ͨ��0����������*/
    SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    /* �������� */
    AppTaskCreate();
    AppObjCreate();



    /* ��ȡ��ǰʱ�� */
    tick = osKernelGetTickCount();

    while(1)
    {

        /* ����ӳ� */
        tick += usFrequency;
        osDelayUntil(tick);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTimerHanle
*	����˵��: �����ʱ���Ļص�������������ִ��ι��������״̬��
*	��    ��: ��
*	�� �� ֵ: ��
*   �� �� ��: osPriorityNormal4
*********************************************************************************************************
*/

void AppTimerHanle(void* argument)
{

    bsp_LedToggle(1);//ָʾ����˸

}


/*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ���񴴽���
*	��    ��: ��
*	�� �� ֵ: ��
*   �� �� ��: osPriorityNormal4
*********************************************************************************************************
*/
static void AppTaskCreate(void)
{


    ThreadIdTaskMsgBack = osThreadNew(AppTaskMsgBack, NULL, &ThreadMsgBack_Attr);
    ThreadIdTaskControl = osThreadNew(AppTaskControl, NULL, &ThreadControl_Attr);
    g_TimerHand_Id      = osTimerNew(AppTimerHanle, osTimerPeriodic, NULL, NULL);

    osTimerStart(g_TimerHand_Id, 100);

}


/*��������ָ������ݴ���*/

uint8_t ble_control(void)
{
    static uint8_t  _byte = 0;
    static uint16_t _bleMoveSpeed = 0;
    static uint8_t  _bleMoveDir = 0;
    static uint8_t  _blePivotSteerDir = 0;
    static uint16_t  _blePivotSteerSpeed = 0;
    static uint16_t  _blePivotMoveSpeed = 350;

    if(comGetChar(COM5, &_byte) != 0)
    {


        switch(_byte)
        {
        case'0':/*ͣ��*/
        case'5':/*ͣ��*/
            _bleMoveSpeed = 0;
            _bleMoveDir = 0;
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 0;


            break;
        case'3':/*��ת��*/
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 200;


            break;
        case'4':/*��ת��*/
            _blePivotSteerDir = 1;
            _blePivotSteerSpeed = 200;

            break;
        case'6':/*ǰ��*/
            _bleMoveSpeed = _blePivotMoveSpeed;
            _bleMoveDir = 0;


            break;
        case'7':/*����*/
            _bleMoveSpeed = _blePivotMoveSpeed;
            _bleMoveDir = 1;

            break;

        case'a':/*�ٶ�����*/
            _blePivotMoveSpeed = _blePivotMoveSpeed + 50;
            if(_blePivotMoveSpeed >= 800)
            {
                _blePivotMoveSpeed = 800;
            }
            break;
        case'b':/*�ٶȼ���*/
           if(_blePivotMoveSpeed > 0)
           {
              _blePivotMoveSpeed = _blePivotMoveSpeed - 50;
           }

            if(_blePivotMoveSpeed <= 0)
            {
                _blePivotMoveSpeed = 0;
            }
            break;
        case'8':/*��ԭ��ת��*/
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 200;
            break;
        case'9':/*��ԭ��ת��*/

            _blePivotSteerDir = 1;
            _blePivotSteerSpeed = 200;
            break;
        case'1':
            case'2':
                    break;
        default:
            auto_ControlCarStop();
        }
//        printf("_bleMoveSpeed  = %d \r\n",_bleMoveSpeed);
        MotorControl(_blePivotSteerDir, _blePivotSteerSpeed, _bleMoveDir, _bleMoveSpeed);
        return 1;
    }
    else
    {
        return 0;
    }

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

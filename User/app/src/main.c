/*
*********************************************************************************************************
*
*	模块名称 : 主程序
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 :
*
*   Copyright (C), 2019-2030, 武汉酷点机器人科技有限公司
*   淘宝店铺地址：https://shop559826635.taobao.com/
*********************************************************************************************************
*/
#include "includes.h"
/*
**********************************************************************************************************
											宏定义
**********************************************************************************************************
*/

/*
**********************************************************************************************************
											函数声明
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
											 变量
**********************************************************************************************************
*/


/*定时任务ID*/
osTimerId_t g_TimerHand_Id;

/* 任务的属性设置 */
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


/* 任务句柄 */
osThreadId_t ThreadIdTaskControl = NULL;
osThreadId_t ThreadIdTaskMsgBack = NULL;
osThreadId_t ThreadIdStart       = NULL;


/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: 程序主入口
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: AppObjCreate
*	功能说明: 消息队列创建
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void AppObjCreate(void)
{


}


/*
*********************************************************************************************************
*	函 数 名: AppTaskMsgBack
*	功能说明: 数据反馈
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: AppTaskControl
*	功能说明: 运动控制
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityNormal (数值越小优先级越低，这个跟uCOS相反)
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

        /*通过蓝牙控制小车*/
        if(ble_control() == 1)
        {


        }
		/*通过PS2手柄控制小车*/
		/*获取PS2数据*/
//		__set_PRIMASK(1);
//				Ps2ClearData();
//				Ps2GetData();
//			Ps2DataKey();
//		__set_PRIMASK(0);	

//        if( (Ps2CheckMode() == 1) && (Ps2_DisLinkStatus()== 0) ) /*手柄模式*/
//        {				
//					/*手柄控制*/

//            Ps2GetAnalogValue(&_left, &_right);					
////					printf("_keyValue_X: %d _keyValue_Y: %d \r\n", _left.Ps2PadXValue,_right.Ps2PadYValue);
//					  MotorControl_Ps2(_left.Ps2PadXValue,_right.Ps2PadYValue);					

//        }
 


        osDelay(10);
    }
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskStart
*	功能说明: 启动任务，这里用作BSP驱动包处理。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityNormal4
*********************************************************************************************************
*/


void AppTaskStart(void* argument)
{
    const uint16_t usFrequency = 100; /* 延迟周期 */

    uint32_t tick;

    bsp_Init();


    /*jlink打印*/
    /* 配置通道0，上行配置*/
    SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

    /* 配置通道0，下行配置*/
    SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    /* 创建任务 */
    AppTaskCreate();
    AppObjCreate();



    /* 获取当前时间 */
    tick = osKernelGetTickCount();

    while(1)
    {

        /* 相对延迟 */
        tick += usFrequency;
        osDelayUntil(tick);
    }
}

/*
*********************************************************************************************************
*	函 数 名: AppTimerHanle
*	功能说明: 软件定时器的回调函数，周期性执行喂狗及发送状态。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityNormal4
*********************************************************************************************************
*/

void AppTimerHanle(void* argument)
{

    bsp_LedToggle(1);//指示灯闪烁

}


/*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 任务创建。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityNormal4
*********************************************************************************************************
*/
static void AppTaskCreate(void)
{


    ThreadIdTaskMsgBack = osThreadNew(AppTaskMsgBack, NULL, &ThreadMsgBack_Attr);
    ThreadIdTaskControl = osThreadNew(AppTaskControl, NULL, &ThreadControl_Attr);
    g_TimerHand_Id      = osTimerNew(AppTimerHanle, osTimerPeriodic, NULL, NULL);

    osTimerStart(g_TimerHand_Id, 100);

}


/*蓝牙控制指令处理数据处理*/

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
        case'0':/*停车*/
        case'5':/*停车*/
            _bleMoveSpeed = 0;
            _bleMoveDir = 0;
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 0;


            break;
        case'3':/*左转弯*/
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 200;


            break;
        case'4':/*右转弯*/
            _blePivotSteerDir = 1;
            _blePivotSteerSpeed = 200;

            break;
        case'6':/*前进*/
            _bleMoveSpeed = _blePivotMoveSpeed;
            _bleMoveDir = 0;


            break;
        case'7':/*后退*/
            _bleMoveSpeed = _blePivotMoveSpeed;
            _bleMoveDir = 1;

            break;

        case'a':/*速度增加*/
            _blePivotMoveSpeed = _blePivotMoveSpeed + 50;
            if(_blePivotMoveSpeed >= 800)
            {
                _blePivotMoveSpeed = 800;
            }
            break;
        case'b':/*速度减少*/
           if(_blePivotMoveSpeed > 0)
           {
              _blePivotMoveSpeed = _blePivotMoveSpeed - 50;
           }

            if(_blePivotMoveSpeed <= 0)
            {
                _blePivotMoveSpeed = 0;
            }
            break;
        case'8':/*左原地转弯*/
            _blePivotSteerDir = 0;
            _blePivotSteerSpeed = 200;
            break;
        case'9':/*右原地转弯*/

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

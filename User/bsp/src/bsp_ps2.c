#include "./bsp_ps2.h"


uint8_t g_Ps2Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t g_Ps2Cmd[2]={0x01,0x42};	//开始命令。请求数据

static uint16_t s_Ps2Key = 0;

static uint16_t MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键明


void Ps2Cmd(uint8_t _data)
{
    volatile uint16_t ref=0x01;
    g_Ps2Data[1] = 0x00;
    
    for(ref = 0x01; ref < 0x0100; ref <<= 1)
    {
        if(ref & _data)
        {
            SPI1_MOSI_1();
        }
        else
        {
            SPI1_MOSI_0();
        }
        
        SPI1_CLK_1();
        HAL_Delay(5);
        SPI1_CLK_0();
        HAL_Delay(5);
        SPI1_CLK_1();
        
        if(SPI1_MISO())
        {
            g_Ps2Data[1] = ref | g_Ps2Data[1];
        }
    }
     HAL_Delay(1);
    
}

void Ps2GetData(void)
{
    volatile uint8_t  byte=0;
	volatile uint16_t ref=0x01;
    
    SPI1_CS_0();
    
    Ps2Cmd(g_Ps2Cmd[0]);
    Ps2Cmd(g_Ps2Cmd[1]);
    
    for(byte=2;byte<9;byte++)          //???????????
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			SPI1_CLK_1();
			SPI1_CLK_0();
			HAL_Delay(5);
			SPI1_CLK_1();
		      if(SPI1_MISO())
		      g_Ps2Data[byte] = ref | g_Ps2Data[byte];
		}
        
        HAL_Delay(1);
    }
    
     SPI1_CS_1();

}

//清除数据缓冲区
void Ps2ClearData(void)
{
	uint8_t i;
	for(i = 0; i < 9; i++)
		g_Ps2Data[i]=0x00;
    
}

uint8_t  Ps2DataKey(void)
{
    uint8_t _index;

//    for(int i = 0; i < 9; i ++)
//    {
//        printf("%x ", g_Ps2Data[i]); 
//    }
//    printf("\r\n");
    s_Ps2Key = (g_Ps2Data[4] << 8) | g_Ps2Data[3];
    
    for(_index = 0; _index < 16; _index++)
	{	    
		if((s_Ps2Key & ( 1 << ( MASK[_index] - 1))) == 0)
		return _index + 1;
	}
    
    
    
    return 0;
}


uint8_t Ps2CheckMode(void)
{
    uint8_t x = g_Ps2Data[1];
	 
	
    if(x == 0x73) /*红灯模式*/
        return 1;
    else          /*绿灯模式*/
        return 0;
    
}

uint8_t Ps2_DisLinkStatus(void)
{
    if(g_Ps2Data[6] == 0x80&g_Ps2Data[7] == 0x80&g_Ps2Data[8] == 0x80) /*断联模式(红灯模式下断联)*/
        return 1;
    else          
        return 0;
    
}

void Ps2GetAnalogValue(Ps2Pad_t *_leftPs2Pad, Ps2Pad_t *_rightPs2Pad)
{

        _leftPs2Pad->Ps2PadXValue  = g_Ps2Data[7];
        _leftPs2Pad->Ps2PadYValue  = g_Ps2Data[8];
        _rightPs2Pad->Ps2PadXValue = g_Ps2Data[5];
        _rightPs2Pad->Ps2PadYValue = g_Ps2Data[6];
   
	 
}



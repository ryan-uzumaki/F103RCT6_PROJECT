/*
*********************************************************************************************************
*
*	ģ������ : oled����
*	�ļ����� : bsp_oled.c
*	��    �� : V1.0
*	˵    �� :
*
*   Copyright (C), 2019-2030, �人�������˿Ƽ����޹�˾
*   �Ա����̵�ַ��https://shop559826635.taobao.com/
*
*********************************************************************************************************
*/
#include "bsp.h"
#include "oledfont.h"


#define I2C_SCL_PIN    GPIO_PIN_4
#define I2C_SCL_GPIO   GPIOB

#define I2C_SDA_PIN    GPIO_PIN_5
#define I2C_SDA_GPIO   GPIOB

#define ALL_I2C_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SCL_1()                  HAL_GPIO_WritePin(I2C_SCL_GPIO, I2C_SCL_PIN, GPIO_PIN_SET);
#define I2C_SCL_0()                  HAL_GPIO_WritePin(I2C_SCL_GPIO, I2C_SCL_PIN, GPIO_PIN_RESET);
#define I2C_SDA_1()                  HAL_GPIO_WritePin(I2C_SDA_GPIO, I2C_SDA_PIN, GPIO_PIN_SET);
#define I2C_SDA_0()                  HAL_GPIO_WritePin(I2C_SDA_GPIO, I2C_SDA_PIN, GPIO_PIN_RESET);

#define I2C_SDA_READ()  			HAL_GPIO_ReadPin(I2C_SDA_GPIO, I2C_SDA_PIN)	/* ��SDA����״̬ */
#define I2C_SCL_READ()  			HAL_GPIO_ReadPin(I2C_SCL_GPIO, I2C_SCL_PIN)	/* ��SCL����״̬ */


#define I2C_WR	0		/* ��????bit */
#define I2C_RD	1		/* ??????bit */

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


u8 OLED_GRAM[144][8];



void i2c_Delay(void)
{
    bsp_DelayUS(7);

}

void i2c_Start(void)
{
    I2C_SDA_1();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_0();
    i2c_Delay();

    I2C_SCL_0();
    i2c_Delay();

}

void i2c_start(void)
{
    I2C_SDA_1();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_0();
    i2c_Delay();

    I2C_SCL_0();
    i2c_Delay();

}

void i2c_Stop(void)
{
    I2C_SDA_0();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_1();
    i2c_Delay();
}

void i2c_SendByte(uint8_t _ucByte)
{
    uint8_t i;

    for(i = 0; i < 8; i ++)
    {
        if(_ucByte & 0x80)
        {
            I2C_SDA_1();
        }
        else
        {
            I2C_SDA_0();

        }
        i2c_Delay();
        I2C_SCL_1();
        i2c_Delay();
        I2C_SCL_0();
        if(i == 7)
        {
            I2C_SDA_1();
        }
        _ucByte <<= 1;

        i2c_Delay();
    }

}

uint8_t i2c_ReadByte(void)
{
    uint8_t i = 0;
    uint8_t _value = 0;
    for(i = 0; i < 8; i ++)
    {
        _value <<= 1;
        I2C_SCL_1();
        i2c_Delay();
        if(I2C_SDA_READ())
        {
            _value ++;
        }
        I2C_SCL_0();
        i2c_Delay();
    }

    return _value;

}


/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    ��:  ��
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
    uint8_t re;

    I2C_SDA_1();	/* CPU�ͷ�SDA���� */
    i2c_Delay();
    I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
    i2c_Delay();
    re = I2C_SDA_READ();
    if(re)	/* CPU��ȡSDA����״̬ */
    {

        re = 1;
    }
    else
    {
        re = 0;
    }
    I2C_SCL_0();
    i2c_Delay();
    return re;
}


/*
*********************************************************************************************************
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Ack(void)
{
    I2C_SDA_0();	/* CPU����SDA = 0 */
    i2c_Delay();
    I2C_SCL_1();	/* CPU����1��ʱ�� */
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
    I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_NAck(void)
{
    I2C_SDA_1();	/* CPU����SDA = 1 */
    i2c_Delay();
    I2C_SCL_1();	/* CPU����1��ʱ�� */
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    ��:  _Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    if(I2C_SDA_READ() && I2C_SCL_READ())
    {

        i2c_Start();		/* ���������ź� */

        /* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
        i2c_SendByte(_Address | I2C_WR);
        ucAck = i2c_WaitAck();	/* ����豸��ACKӦ�� */

        i2c_Stop();			/* ����ֹͣ�ź� */

        return ucAck;
    }

    return 1;	/* I2C�����쳣 */
}



//����һ���ֽ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat, u8 mode)
{
    i2c_start();
    i2c_SendByte(0x78);
    i2c_WaitAck();
    if(mode)
    {
        i2c_SendByte(0x40);
    }
    else
    {
        i2c_SendByte(0x00);
    }
    i2c_WaitAck();
    i2c_SendByte(dat);
    i2c_WaitAck();
    i2c_Stop();
}


//���Ժ���
void OLED_ColorTurn(u8 i)
{
    if(i == 0)
    {
        OLED_WR_Byte(0xA6, OLED_CMD); //������ʾ
    }
    if(i == 1)
    {
        OLED_WR_Byte(0xA7, OLED_CMD); //��ɫ��ʾ
    }
}

//��Ļ��ת180��
void OLED_DisplayTurn(u8 i)
{
    if(i == 0)
    {
        OLED_WR_Byte(0xC8, OLED_CMD); //������ʾ
        OLED_WR_Byte(0xA1, OLED_CMD);
    }
    if(i == 1)
    {
        OLED_WR_Byte(0xC0, OLED_CMD); //��ת��ʾ
        OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

//����OLED��ʾ
void OLED_DisPlay_On(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x14, OLED_CMD); //������ɱ�
    OLED_WR_Byte(0xAF, OLED_CMD); //������Ļ
}

//�ر�OLED��ʾ
void OLED_DisPlay_Off(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x10, OLED_CMD); //�رյ�ɱ�
    OLED_WR_Byte(0xAE, OLED_CMD); //�ر���Ļ
}

//�����Դ浽OLED
void OLED_Refresh(void)
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0 + i, OLED_CMD); //��������ʼ��ַ
        OLED_WR_Byte(0x00, OLED_CMD);  //���õ�����ʼ��ַ
        OLED_WR_Byte(0x10, OLED_CMD);  //���ø�����ʼ��ַ
        i2c_start();
        i2c_SendByte(0x78);
        i2c_WaitAck();
        i2c_SendByte(0x40);
        i2c_WaitAck();
        for(n = 0; n < 128; n++)
        {
            i2c_SendByte(OLED_GRAM[n][i]);
            i2c_WaitAck();
        }
        i2c_Stop();
    }
}
//��������
void OLED_Clear(void)
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        for(n = 0; n < 128; n++)
        {
            OLED_GRAM[n][i] = 0; //�����������
        }
    }
    OLED_Refresh();//������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(u8 x, u8 y, u8 t)
{
    u8 i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    if(t)
    {
        OLED_GRAM[x][i] |= n;
    }
    else
    {
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
        OLED_GRAM[x][i] |= n;
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    }
}

//����
//x1,y1:�������
//x2,y2:��������
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2, u8 mode)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1; //�����������
    uCol = y1;
    if(delta_x > 0)incx = 1; //���õ�������
    else if(delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_x;
    }
    if(delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;
    for(t = 0; t < distance + 1; t++)
    {
        OLED_DrawPoint(uRow, uCol, mode); //����
        xerr += delta_x;
        yerr += delta_y;
        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(u8 x, u8 y, u8 r)
{
    int a, b, num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b, 1);
        OLED_DrawPoint(x - a, y - b, 1);
        OLED_DrawPoint(x - a, y + b, 1);
        OLED_DrawPoint(x + a, y + b, 1);

        OLED_DrawPoint(x + b, y + a, 1);
        OLED_DrawPoint(x + b, y - a, 1);
        OLED_DrawPoint(x - b, y - a, 1);
        OLED_DrawPoint(x - b, y + a, 1);

        a++;
        num = (a * a + b * b) - r * r; //���㻭�ĵ���Բ�ĵľ���
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}



//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1, u8 mode)
{
    u8 i, m, temp, size2, chr1;
    u8 x0 = x, y0 = y;
    if(size1 == 8)size2 = 6;
    else size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���
    chr1 = chr - ' '; //����ƫ�ƺ��ֵ
    for(i = 0; i < size2; i++)
    {
        if(size1 == 8)
        {
            temp = asc2_0806[chr1][i];   //����0806����
        }
        else if(size1 == 12)
        {
            temp = asc2_1206[chr1][i];   //����1206����
        }
        else if(size1 == 16)
        {
            temp = asc2_1608[chr1][i];   //����1608����
        }
        else if(size1 == 24)
        {
            temp = asc2_2412[chr1][i];   //����2412����
        }
        else return;
        for(m = 0; m < 8; m++)
        {
            if(temp & 0x01)OLED_DrawPoint(x, y, mode);
            else OLED_DrawPoint(x, y, !mode);
            temp >>= 1;
            y++;
        }
        x++;
        if((size1 != 8) && ((x - x0) == size1 / 2))
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}


//��ʾ�ַ���
//x,y:�������
//size1:�����С
//*chr:�ַ�����ʼ��ַ
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowString(u8 x, u8 y, u8* chr, u8 size1, u8 mode)
{
    while((*chr >= ' ') && (*chr <= '~')) //�ж��ǲ��ǷǷ��ַ�!
    {
        OLED_ShowChar(x, y, *chr, size1, mode);
        if(size1 == 8)x += 6;
        else x += size1 / 2;
        chr++;
    }
}

//m^n
u32 OLED_Pow(u8 m, u8 n)
{
    u32 result = 1;
    while(n--)
    {
        result *= m;
    }
    return result;
}

//��ʾ����
//x,y :�������
//num :Ҫ��ʾ������
//len :���ֵ�λ��
//size:�����С
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1, u8 mode)
{
    u8 t, temp, m = 0;
    if(size1 == 8)m = 2;
    for(t = 0; t < len; t++)
    {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;
        if(temp == 0)
        {
            OLED_ShowChar(x + (size1 / 2 + m)*t, y, '0', size1, mode);
        }
        else
        {
            OLED_ShowChar(x + (size1 / 2 + m)*t, y, temp + '0', size1, mode);
        }
    }
}

//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChinese(u8 x, u8 y, u8 num, u8 size1, u8 mode)
{
    u8 m, temp;
    u8 x0 = x, y0 = y;
    u16 i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; //�õ�����һ���ַ���Ӧ������ռ���ֽ���
    for(i = 0; i < size3; i++)
    {
        if(size1 == 16)
        {
            temp = Hzk1[num][i];   //����16*16����
        }
        else if(size1 == 24)
        {
            temp = Hzk2[num][i];   //����24*24����
        }
        else if(size1 == 32)
        {
            temp = Hzk3[num][i];   //����32*32����
        }
        else if(size1 == 64)
        {
            temp = Hzk4[num][i];   //����64*64����
        }
        else return;
        for(m = 0; m < 8; m++)
        {
            if(temp & 0x01)OLED_DrawPoint(x, y, mode);
            else OLED_DrawPoint(x, y, !mode);
            temp >>= 1;
            y++;
        }
        x++;
        if((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ScrollDisplay(u8 num, u8 space, u8 mode)
{
    u8 i, n, t = 0, m = 0, r;
    while(1)
    {
        if(m == 0)
        {
            OLED_ShowChinese(128, 24, t, 16, mode); //д��һ�����ֱ�����OLED_GRAM[][]������
            t++;
        }
        if(t == num)
        {
            for(r = 0; r < 16 * space; r++) //��ʾ���
            {
                for(i = 1; i < 144; i++)
                {
                    for(n = 0; n < 8; n++)
                    {
                        OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
                    }
                }
                OLED_Refresh();
            }
            t = 0;
        }
        m++;
        if(m == 16)
        {
            m = 0;
        }
        for(i = 1; i < 144; i++) //ʵ������
        {
            for(n = 0; n < 8; n++)
            {
                OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
            }
        }
        OLED_Refresh();
    }
}

//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowPicture(u8 x, u8 y, u8 sizex, u8 sizey, u8 BMP[], u8 mode)
{
    u16 j = 0;
    u8 i, n, temp, m;
    u8 x0 = x, y0 = y;
    sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
    for(n = 0; n < sizey; n++)
    {
        for(i = 0; i < sizex; i++)
        {
            temp = BMP[j];
            j++;
            for(m = 0; m < 8; m++)
            {
                if(temp & 0x01)OLED_DrawPoint(x, y, mode);
                else OLED_DrawPoint(x, y, !mode);
                temp >>= 1;
                y++;
            }
            x++;
            if((x - x0) == sizex)
            {
                x = x0;
                y0 = y0 + 8;
            }
            y = y0;
        }
    }
}

void bsp_InitOled(void)
{
    GPIO_InitTypeDef gpio_init;

    /* ��1������GPIOʱ�� */
    ALL_I2C_GPIO_CLK_ENABLE();

    gpio_init.Mode = GPIO_MODE_OUTPUT_OD;	/* ���ÿ�©��� */
    gpio_init.Pull = GPIO_NOPULL;			/* ���������費ʹ�� */
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;  /* GPIO�ٶȵȼ� */

    gpio_init.Pin = I2C_SCL_PIN;
    HAL_GPIO_Init(I2C_SCL_GPIO, &gpio_init);

    gpio_init.Pin = I2C_SDA_PIN;
    HAL_GPIO_Init(I2C_SDA_GPIO, &gpio_init);

    /* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
    i2c_Stop();



    OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
    OLED_WR_Byte(0x30, OLED_CMD); //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); //
    OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
    OLED_Clear();
    OLED_WR_Byte(0xAF, OLED_CMD);

}

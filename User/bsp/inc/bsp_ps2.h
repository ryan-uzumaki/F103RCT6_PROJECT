#ifndef __PS2_H__
#define __PS2_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "tim.h"


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

#define SPI1_CS_1()      SPIx_CS_PIN_GPIO_Port->BSRR = SPIx_CS_PIN_Pin                        /*CSÖÃ1*/
#define SPI1_CS_0()      SPIx_CS_PIN_GPIO_Port->BSRR = ((uint32_t)SPIx_CS_PIN_Pin << 16U)     /*CSÖÃ0*/

#define SPI1_CLK_1()      SPIx_SCK_PIN_GPIO_Port->BSRR = SPIx_SCK_PIN_Pin                        /*CSÖÃ1*/
#define SPI1_CLK_0()      SPIx_SCK_PIN_GPIO_Port->BSRR = ((uint32_t)SPIx_SCK_PIN_Pin << 16U)     /*CSÖÃ0*/

#define SPI1_MOSI_1()      SPIx_MOSI_PIN_GPIO_Port->BSRR = SPIx_MOSI_PIN_Pin                        /*CSÖÃ1*/
#define SPI1_MOSI_0()      SPIx_MOSI_PIN_GPIO_Port->BSRR = ((uint32_t)SPIx_MOSI_PIN_Pin << 16U)     /*CSÖÃ0*/

#define SPI1_MISO()       HAL_GPIO_ReadPin(SPIx_MISO_PIN_GPIO_Port ,SPIx_MISO_PIN_Pin)


typedef struct {

    uint8_t Ps2PadXValue;
    uint8_t Ps2PadYValue;

}Ps2Pad_t;
    
void PS2_init(void);
void Ps2Cmd(uint8_t _data);
void Ps2GetData(void);
void Ps2ClearData(void);
uint8_t  Ps2DataKey(void);
uint8_t Ps2CheckMode(void);
void Ps2GetAnalogValue(Ps2Pad_t *_leftPs2Pad, Ps2Pad_t *_rightPs2Pad);
uint8_t Ps2_DisLinkStatus(void);
#endif /*__PS2_H__*/






#ifndef __BSP_DWT_H
#define __BSP_DWT_H

/*
*********************************************************************************************************
*                                             �Ĵ���
*********************************************************************************************************
*/
#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
#define  DWT_CR      *(volatile unsigned int *)0xE0001000
#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004

#define  DEM_CR_TRCENA               (1 << 24)
#define  DWT_CR_CYCCNTENA            (1 <<  0)


/*
*********************************************************************************************************
*                                             ����
*********************************************************************************************************
*/
void bsp_InitDWT(void);
void bsp_DelayUS(uint32_t _ulDelayTime);
void bsp_DelayMS(uint32_t _ulDelayTime);

#endif



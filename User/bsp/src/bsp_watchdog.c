#include "bsp.h"

IWDG_HandleTypeDef IWDG_Handle;

/*********************************************************************************************************
*	函 数 名: IWDG_Config
*	功能说明: 独立看门狗初始化
*	形    参: prv 时钟分频系数   rlv 重装在值
*	返 回 值: 无
*********************************************************************************************************
*/

void IWDG_Config(uint8_t prv, uint16_t rlv)
{
	IWDG_Handle.Instance = IWDG;
	
	IWDG_Handle.Init.Prescaler = prv;
	
	IWDG_Handle.Init.Reload = rlv;
	
	HAL_IWDG_Init(&IWDG_Handle);
	
	__HAL_IWDG_START(&IWDG_Handle);

}
/*********************************************************************************************************
*	函 数 名: IWDG_Feed
*	功能说明: 独立看门狗喂狗
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

void IWDG_Feed(void)
{
	HAL_IWDG_Refresh(&IWDG_Handle);
}

/*********************************************************************************************************
*	函 数 名: bsp_initIwdg
*	功能说明: 初始化独立看门狗
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

void bsp_initIwdg(void)
{
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	{
		// bsp_LedToggle(1);
		/*清除标志*/
		__HAL_RCC_CLEAR_RESET_FLAGS();
	
	}
	
	/*5s*/
	IWDG_Config(IWDG_PRESCALER_64, 3125);

}
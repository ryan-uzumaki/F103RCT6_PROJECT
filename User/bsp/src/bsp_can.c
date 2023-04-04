#include "includes.h"
#include "bsp.h"

CAN_HandleTypeDef     CanHandle;
CAN_TxHeaderTypeDef   TxMessage; 
CAN_RxHeaderTypeDef   RxMessage;
uint32_t              TxMailbox;


/*********************************************************************************************************
*	�� �� ��: bsp_InitCan
*	����˵��: CAN��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitCan(void)
{
  CAN_FilterTypeDef  sFilterConfig;
  GPIO_InitTypeDef   GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* CAN1 Periph clock enable */
  CANx_CLK_ENABLE();
  /* Enable GPIO clock ****************************************/
  CANx_GPIO_CLK_ENABLE();
  /* Enable AFIO clock and Remap CAN PINs to PB8 and PB9*******/
  CANx_AFIO_REMAP_CLK_ENABLE();
  CANx_AFIO_REMAP_RX_TX_PIN();
	
  /*##-2- Configure peripheral GPIO ##########################################*/
  /* CAN1 TX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStruct);

  /* CAN1 RX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_RX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStruct);
  
  /*##-3- Configure the NVIC #################################################*/
  /* NVIC configuration for CAN1 Reception complete interrupt */
  HAL_NVIC_SetPriority(CANx_RX_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(CANx_RX_IRQn);

  /* Configure the CAN peripheral */
  CanHandle.Instance = CANx;

  CanHandle.Init.TimeTriggeredMode = DISABLE;
  CanHandle.Init.AutoBusOff = ENABLE;
  CanHandle.Init.AutoWakeUp = ENABLE;
  CanHandle.Init.AutoRetransmission = DISABLE;
  CanHandle.Init.ReceiveFifoLocked = DISABLE;
  CanHandle.Init.TransmitFifoPriority = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_NORMAL;
  CanHandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
  CanHandle.Init.TimeSeg1 = CAN_BS1_7TQ;
  CanHandle.Init.TimeSeg2 = CAN_BS2_4TQ;
  CanHandle.Init.Prescaler = 6;

  if (HAL_CAN_Init(&CanHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(__FILE__, __LINE__);
  }

  /* Configure the CAN Filter */
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler(__FILE__, __LINE__);
  }

  /* Start the CAN peripheral */
  if (HAL_CAN_Start(&CanHandle) != HAL_OK)
  {
    /* Start Error */
    Error_Handler(__FILE__, __LINE__);
  }

  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(&CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler(__FILE__, __LINE__);
  }
 
  
}

/*********************************************************************************************************
*	�� �� ��: CAN1_RX0_IRQHandler
*	����˵��: CAN�жϴ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void CAN1_RX0_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&CanHandle);

}

/*********************************************************************************************************
*	�� �� ��: CanTransmit
*	����˵��: CAN���ݷ��ͺ���
*	��    ��: _id CAN����ID  _buf ����CAN���ݵĻ�����   _num �������ݵĳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void CanTransmit(uint16_t _id, uint8_t *_buf, uint8_t _num)
{

  /* Configure Transmission process */
  TxMessage.StdId = _id;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = _num;

	
	if(HAL_CAN_AddTxMessage(&CanHandle, &TxMessage, _buf, &TxMailbox) != HAL_OK)
	{
	   printf("___fail___\r\n");
	}
	osDelay(1);
	

}


/*********************************************************************************************************
*	�� �� ��: HAL_CAN_RxFifo0MsgPendingCallback
*	����˵��: CAN�жϴ��������ɵĻص�����
*	��    ��: CanHandle can�豸ָ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
	 //uint8_t g_Can1RxData[8];
   if(CanHandle->Instance == CAN1)
	 {
		
			 //HAL_CAN_GetRxMessage(CanHandle,CAN_RX_FIFO0,&RxMessage,g_Can1RxData);

	 }
}





/**
  ******************************************************************************
  * @file    	USART/Printf/stm32f10x_it.c 
  * @author  	ARMVN Application Team
  * @version 	V1.0
  * @date    	19/03/2010
  * @brief   	Main Interrupt Service Routines.
  *          		This file provides template for all exceptions handler and peripherals
  *          		interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ARMVIETNAM SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 ARMVIETNAM</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "UART.h"
#include "TIMER.h"



void USART1_IRQHandler(void)
{
	while(USART_GetFlagStatus (UART_RF, USART_FLAG_RXNE)==RESET){}	
	{
		UART_rf.cmd[UART_rf.counter++] = USART_ReceiveData(UART_RF);
		UART_rf.time_out = 0 ;
		if(UART_rf.counter > 95)
		{
			UART_rf.counter = 95;
		}
		TIM_SetCounter(TIM2, 1);
		TIM_Cmd(TIM2, ENABLE);
	}
}

void USART2_IRQHandler(void)
{
	while(USART_GetFlagStatus (USART2, USART_FLAG_RXNE)==RESET){}	
	{
		UART2_sensor.cmd[UART2_sensor.counter++] = USART_ReceiveData(USART2);
		UART2_sensor.time_out = 0 ;
		if(UART2_sensor.counter > 95)
		{
			UART2_sensor.counter = 95;
		}
		TIM_SetCounter(TIM2, 1);
		TIM_Cmd(TIM2, ENABLE);
	}
}

void USART3_IRQHandler(void)
{
	while(USART_GetFlagStatus (USART3, USART_FLAG_RXNE)==RESET){}	
	{
		UART3_sensor.cmd[UART3_sensor.counter++] = USART_ReceiveData(USART3);
		UART3_sensor.time_out = 0 ;
		if(UART3_sensor.counter > 95)
		{
			UART3_sensor.counter = 95;
		}
		TIM_SetCounter(TIM2, 1);
		TIM_Cmd(TIM2, ENABLE);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
		if(UART_rf.counter > 0) UART_rf.time_out++;
		if(UART_rf.time_out > 10)
		{
			UART_rf.flag = 1;
			UART_rf.len = UART_rf.counter; // chieu dai du lieu
			UART_rf.counter = 0;
		}
		if(UART2_sensor.counter > 0) UART2_sensor.time_out++;
		if(UART2_sensor.time_out > 10)
		{
			UART2_sensor.flag = 1;
			UART2_sensor.len = UART2_sensor.counter;
			UART2_sensor.counter = 0;
		}
		
		if(UART3_sensor.counter > 0) UART3_sensor.time_out++;
		if(UART3_sensor.time_out > 10)
		{
			UART3_sensor.flag = 1;
			UART3_sensor.len = UART3_sensor.counter;
			UART3_sensor.counter = 0;
		}
		if(UART_rf.counter == 0 && UART2_sensor.counter == 0 && UART3_sensor.counter == 0) TIM_Cmd(TIM2, DISABLE);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}  
}

void SysTick_Handler(void)
{
	systick.SysTick_Counter++;
}
/*******************************************************************************
* Function Name  	: EXTI9_5_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 13/04/2009
* Description		: This function handles External lines 9 to 5 interrupt request.
* Notes			: 
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  	: EXTI15_10_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 13/04/2009
* Description		: This function handles External lines 15 to 10 interrupt request.
* Notes			: 
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{		

}


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*******************************************************************************
* Function Name  	: WWDG_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles WWDG interrupt request.
* Notes			: 
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: PVD_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles PVD interrupt request.
* Notes			: 
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TAMPER_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles Tamper interrupt request. 
* Notes			: 
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: RTC_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles RTC global interrupt request.
* Notes			: 
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: FLASH_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles Flash interrupt request.
* Notes			: 
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: RCC_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles RCC interrupt request. 
* Notes			: 
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI0_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles External interrupt Line 0 request.
* Notes			: 
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI1_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles External interrupt Line 1 request.
* Notes			: 
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI2_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles External interrupt Line 2 request.
* Notes			: 
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 13/04/2009
* Description		: This function handles External interrupt Line 3 request.
* Notes			: 
*******************************************************************************/
void EXTI3_IRQHandler(void)
{  	
}

/*******************************************************************************
* Function Name  	: EXTI4_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles External interrupt Line 4 request.
* Notes			: 
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel1_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 1 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel2_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 2 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 3 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel4_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 4 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel5_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 5 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel6_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 6 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel7_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA1 Channel 7 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: ADC1_2_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles ADC1 and ADC2 global interrupts requests.
* Notes			: 
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USB_HP_CAN_TX_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles USB High Priority or CAN TX interrupts requests.
* Notes			: 
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
  //CTR_HP();
}

/*******************************************************************************
* Function Name  	: USB_LP_CAN_RX0_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles USB Low Priority or CAN RX0 interrupts requests.
* Notes			: 
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
  //USB_Istr();
}

/*******************************************************************************
* Function Name  	: CAN_RX1_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles CAN RX1 interrupt request.
* Notes			: 
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: CAN_SCE_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles CAN SCE interrupt request.
* Notes			: 
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}



/*******************************************************************************
* Function Name  	: TIM1_BRK_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM1 Break interrupt request.
* Notes			: 
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM1_UP_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM1 overflow and update interrupt request.
* Notes			: 
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM1_TRG_COM_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM1 Trigger and commutation interrupts requests.
* Notes			: 
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM1_CC_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM1 capture compare interrupt request.
* Notes			: 
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}


/*******************************************************************************
* Function Name  	: TIM3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM3 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM3_IRQHandler(void)
{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
	

/*******************************************************************************
* Function Name  	: TIM4_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM4 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM4_IRQHandler(void)
{
			TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	 
}

/*******************************************************************************
* Function Name  	: I2C1_EV_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles I2C1 Event interrupt request.
* Notes			: 
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C1_ER_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles I2C1 Error interrupt request.
* Notes			: 
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C2_EV_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles I2C2 Event interrupt request.
* Notes			: 
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C2_ER_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles I2C2 Error interrupt request.
* Notes			: 
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI1_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles SPI1 global interrupt request.
* Notes			: 
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI2_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles SPI2 global interrupt request.
* Notes			: 
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}




/*******************************************************************************
* Function Name  	: RTCAlarm_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles RTC Alarm interrupt request.
* Notes			: 
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USBWakeUp_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles USB WakeUp interrupt request.
* Notes			: 
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_BRK_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM8 Break interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_UP_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM8 overflow and update interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_TRG_COM_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM8 Trigger and commutation interrupts requests.
* Notes			: 
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_CC_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM8 capture compare interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: ADC3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles ADC3 global interrupt request.
* Notes			: 
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: FSMC_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles FSMC global interrupt request.
* Notes			: 
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SDIO_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles SDIO global interrupt request.
* Notes			: 
*******************************************************************************/
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  //SD_ProcessIRQSrc();
}

/*******************************************************************************
* Function Name  	: TIM5_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM5 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles SPI3 global interrupt request.
* Notes			: 
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: UART4_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles UART4 global interrupt request.
* Notes			: 
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: UART5_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles UART5 global interrupt request.
* Notes			: 
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM6_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM6 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM7_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles TIM7 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel1_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA2 Channel 1 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel2_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA2 Channel 2 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel3_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA2 Channel 3 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel4_5_IRQHandler
* Return         	: None
* Parameters 		: None
* Created by		: Phung The Vu
* Date created	: 19/01/2009
* Description		: This function handles DMA2 Channel 4 and DMA2 Channel 5 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 ARMVIETNAM *****END OF FILE****/

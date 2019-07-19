#include "ADC.h"

adc_value_typedef adc_value;




void config_ADC(uint8_t port)
{
	switch(port)
	{
		case PORT8: RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
								RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
									
								GPIO_InitStructure.GPIO_Pin = PORT8_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);
		
		
								DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
								DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_value.port;
								DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
								DMA_InitStructure.DMA_BufferSize = 1;
								DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
								DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
								DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
								DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
								DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
								DMA_InitStructure.DMA_Priority = DMA_Priority_High;
								DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
								DMA_Init(DMA1_Channel1, &DMA_InitStructure);
								
								DMA_Cmd(DMA1_Channel1, ENABLE);
									
								ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
								ADC_InitStructure.ADC_ScanConvMode = ENABLE;
								ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
								ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
								ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
								ADC_InitStructure.ADC_NbrOfChannel = 1;
								ADC_Init(ADC1, &ADC_InitStructure);
								
								ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
								
								ADC_DMACmd(ADC1, ENABLE);

								ADC_Cmd(ADC1, ENABLE);
  
								ADC_ResetCalibration(ADC1);
								while(ADC_GetResetCalibrationStatus(ADC1)){};
									
								ADC_StartCalibration(ADC1);
								while(ADC_GetCalibrationStatus(ADC1)){};
									 
								ADC_SoftwareStartConvCmd(ADC1, ENABLE);
								break;
		case PORT9: RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
								RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
								
								GPIO_InitStructure.GPIO_Pin = PORT8_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);
									
								GPIO_InitStructure.GPIO_Pin = PORT9_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_Init(PORT9_A_GPIO, &GPIO_InitStructure);	
		
								DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
								DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_value.port;
								DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
								DMA_InitStructure.DMA_BufferSize = 2;
								DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
								DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
								DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
								DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
								DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
								DMA_InitStructure.DMA_Priority = DMA_Priority_High;
								DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
								DMA_Init(DMA1_Channel1, &DMA_InitStructure);
								
								DMA_Cmd(DMA1_Channel1, ENABLE);
									
								ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
								ADC_InitStructure.ADC_ScanConvMode = ENABLE;
								ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
								ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
								ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
								ADC_InitStructure.ADC_NbrOfChannel = 2;
								ADC_Init(ADC1, &ADC_InitStructure);
								
								ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
								ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_55Cycles5);
								
								ADC_DMACmd(ADC1, ENABLE);

								ADC_Cmd(ADC1, ENABLE);
  
								ADC_ResetCalibration(ADC1);
								while(ADC_GetResetCalibrationStatus(ADC1)){};
									
								ADC_StartCalibration(ADC1);
								while(ADC_GetCalibrationStatus(ADC1)){};
									 
								ADC_SoftwareStartConvCmd(ADC1, ENABLE);
								break;
		case PORT10: RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
								RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
								
								GPIO_InitStructure.GPIO_Pin = PORT8_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);
									
								GPIO_InitStructure.GPIO_Pin = PORT9_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_Init(PORT9_A_GPIO, &GPIO_InitStructure);
								
								GPIO_InitStructure.GPIO_Pin = PORT10_PIN1;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
								GPIO_Init(PORT10_GPIO, &GPIO_InitStructure);
		
								DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
								DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_value.port;
								DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
								DMA_InitStructure.DMA_BufferSize = 3;
								DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
								DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
								DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
								DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
								DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
								DMA_InitStructure.DMA_Priority = DMA_Priority_High;
								DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
								DMA_Init(DMA1_Channel1, &DMA_InitStructure);
								
								DMA_Cmd(DMA1_Channel1, ENABLE);
									
								ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
								ADC_InitStructure.ADC_ScanConvMode = ENABLE;
								ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
								ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
								ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
								ADC_InitStructure.ADC_NbrOfChannel = 3;
								ADC_Init(ADC1, &ADC_InitStructure);
								
								ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
								ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_55Cycles5);
								ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 3, ADC_SampleTime_55Cycles5);
								
								ADC_DMACmd(ADC1, ENABLE);

								ADC_Cmd(ADC1, ENABLE);
  
								ADC_ResetCalibration(ADC1);
								while(ADC_GetResetCalibrationStatus(ADC1)){};
									
								ADC_StartCalibration(ADC1);
								while(ADC_GetCalibrationStatus(ADC1)){};
									 
								ADC_SoftwareStartConvCmd(ADC1, ENABLE);
								break;
		default: break;
	}
}





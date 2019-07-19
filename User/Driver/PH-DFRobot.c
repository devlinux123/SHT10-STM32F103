#include "PH-DFRobot.h"
#include "ADC.h"
#include "FLASH.h"

data_ph_typedef	data_ph;


void PH_Read(uint8_t port)
{
	uint8_t i;
	data_ph.PH = 0;
	for(i = 0 ; i < NUM_SAMP_ADC; i++)
	{
		if(port == PORT5)
		{
			data_ph.Voltage += (uint32_t)adc_value.port[0]*6600/4095;
		}
		else if(port == PORT6)
		{
			data_ph.Voltage += (uint32_t)adc_value.port[1]*6600/4095;
		}
		else if(port == PORT8)
		{
			data_ph.Voltage += (uint32_t)adc_value.port[2]*6600/4095;
		}
		else if(port == PORT9)
		{
			data_ph.Voltage += (uint32_t)adc_value.port[3]*6600/4095;
		}
		else if(port == PORT10)
		{
			data_ph.Voltage += (uint32_t)adc_value.port[4]*6600/4095;
		}
		
		data_ph.Voltage = data_ph.Voltage - 2500;
		data_ph.PH += (int32_t)(7000 - (int32_t)(data_ph.Voltage*1000/59.16f));
	}
	data_ph.PH = data_ph.PH/NUM_SAMP_ADC;
	if(data_ph.set_phos == 0)
	{
		data_ph.PH = data_ph.PH - data_ph.PH_Offset;
		if(data_ph.PH > 14000) data_ph.PH = 14000;
		if(data_ph.PH < 0) data_ph.PH = 0;
	}
	if(data_ph.set_phos > 0)
	{
		data_ph.PH_Offset += (int32_t)(data_ph.PH - data_ph.PH_Base);
		data_ph.set_phos--;
		if(data_ph.set_phos == 0)
		{
			data_ph.PH_Offset = data_ph.PH_Offset/NUM_SAMP_ADC;
			write_FLASH();
		}
	}
}



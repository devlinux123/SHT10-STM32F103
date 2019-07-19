#include "FLASH.h"
#include "SHT1x.h"
#include "MQ-Series.h"
#include "YGC-Series.h"
#include "DS18B20.h"
//#include "MH-Z19B.h"
#include "ZH03B.h"
#include "BMP180.h"
#include "WinSen-Series.h"
#include "ADC.h"

flash_typedef flash;


void FLASH_update_information(void)
{
	uint8_t i;
	read_FLASH();
	if(flash.buff[ADDR_CHECK] != FLASH_CHECK)
	{
		default_value();
	}
	else
	{
		HUMI.Offset_RH = (int16_t)flash.buff[ADDR_RH_OFFSET];
		TEMP.Offset_Temp = (int16_t)flash.buff[ADDR_TEMP_OFFSET];
		CO.Ro = flash.buff[ADDR_CO_OFFSET];
		CO2.offset = (int32_t)flash.buff[ADDR_CO2_OFFSET];
		GAS.Ro = flash.buff[ADDR_GAS_OFFSET];
		H2.Ro = flash.buff[ADDR_H2_OFFSET];
		WIND_SPEED.offset = flash.buff[ADDR_WIND_SPEED_OFFSET];
		WIND_DIRECT.offset = flash.buff[ADDR_WIND_DIRECT_OFFSET];
		PRESSURE.Offset_value = flash.buff[ADDR_PRESSURE_OFFSET];
		DUST.offset = flash.buff[ADDR_DUST_OFFSET];
		
		for(i = 0; i < 10; i++)
		{
			flash.property_buff[i] = flash.buff[ADDR_PROPERTY+i];
			flash.interface_buff[i] = flash.buff[ADDR_INTERFACE+i];
		}
	}
}


void read_FLASH(void)
{
	uint8_t i;
	for(i = 0; i < FLASH_SIZE; i++)
	{
		flash.buff[i] = (*(__IO uint32_t*) (FLASH_ADDR+(i*4)));
	}
}

void write_FLASH(void)
{
	uint8_t i;
	FLASH_Unlock();
	FLASH_ErasePage(FLASH_ADDR);
	
	flash.buff[ADDR_CHECK] = FLASH_CHECK;
	flash.buff[ADDR_RH_OFFSET] = HUMI.Offset_RH;
	flash.buff[ADDR_TEMP_OFFSET] = TEMP.Offset_Temp;
	flash.buff[ADDR_CO_OFFSET] = CO.Ro;
	flash.buff[ADDR_CO2_OFFSET] = CO2.offset;
	flash.buff[ADDR_GAS_OFFSET] = GAS.Ro;
	flash.buff[ADDR_H2_OFFSET] = H2.Ro;
	flash.buff[ADDR_WIND_SPEED_OFFSET] = WIND_SPEED.offset;
	flash.buff[ADDR_WIND_DIRECT_OFFSET] = WIND_DIRECT.offset;
	flash.buff[ADDR_PRESSURE_OFFSET] = PRESSURE.Offset_value;
	flash.buff[ADDR_DUST_OFFSET] = DUST.offset;
	
	for(i = 0; i < 10; i++)
	{
		flash.buff[ADDR_PROPERTY + i] = flash.property_buff[i]; 
		flash.buff[ADDR_INTERFACE + i] = flash.interface_buff[i]; 
	}
//	for(i = 0; i < NUM_SAMP_ADC; i++)
//	{
//		adc_value.port[i] = 0;
//	}
	for(i = 0; i < FLASH_SIZE; i++)
	{
		FLASH_ProgramWord(FLASH_ADDR+(i*4), flash.buff[i]);
	}
	FLASH_Lock();
}



void default_value(void)
{
	uint8_t i;
	
	HUMI.Offset_RH = RH_OFFSET_DEFAULT;              //===== SHT1x.h =====//  
	TEMP.Offset_Temp = TEMP_OFFSET_DEFAULT;          //=== DS18B20.h ===//
	CO.Ro = CO_RO_DEFAULT;                           //=== MQ-Series.h ===//
	CO2.offset = CO2_OFFSET_DEFAULT;                 //=== WinSen-Series.h ===//
	GAS.Ro = GAS_RO_DEFAULT;                         //=== MQ-Series.h ===//
	H2.Ro = H2_RO_DEFAULT;                           //=== MQ-Series.h ===//
	WIND_SPEED.offset = WIND_SPEED_OFFSET_DEFAULT;   //=== YGC-Series.h ===//
	WIND_DIRECT.offset = WIND_DIRECT_OFFSET_DEFAULT; //=== YGC-Series.h ===//
	PRESSURE.Offset_value = PRESSURE_DEFAULT;        // BMP180.h //
	DUST.offset = DUST_OFFSET_DEFAULT;               //=== ZH03B.h ===//
	
	for(i = 0; i < 10; i++)
	{
		flash.property_buff[i] = 0x00;
		flash.interface_buff[i] = 0x00;
	}
	write_FLASH();
}



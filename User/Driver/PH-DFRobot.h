#include "GPIO.h"


typedef struct
{
	__IO uint16_t ADC;
	int16_t Voltage;
	int16_t PH_Base;
	int32_t PH;
	int32_t PH_Offset;
	uint8_t set_phos;
	
}data_ph_typedef;

extern data_ph_typedef	data_ph;


void PH_Read(uint8_t port);


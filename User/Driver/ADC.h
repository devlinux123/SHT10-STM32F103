#include "GPIO.h"

#define NUM_SAMP_ADC				(uint8_t)30

typedef struct
{
	__IO uint16_t port[3];
	
}adc_value_typedef;

extern adc_value_typedef adc_value;

void config_ADC(uint8_t port);


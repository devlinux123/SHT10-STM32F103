#include "GPIO.h"


typedef struct
{
	uint16_t base;
	int16_t offset;
	uint8_t flag;
	uint16_t value_samp[NUM_SAMP_RESPONSE];
	uint16_t count;
	uint32_t value;
	uint8_t check_sum;
	uint8_t flag_start;
	uint8_t data[9];
	
}data_winsen_typedef;


extern data_winsen_typedef CO2;

void WinSen_UART_Read(uint8_t port, data_winsen_typedef *data);
void WinSen_DIGITAL_Read(uint8_t port, data_winsen_typedef *data);

void get_WINSEN(uint16_t port, uint8_t property, uint8_t checksum0, uint16_t data);


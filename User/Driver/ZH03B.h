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
	
}data_dust_uart_typedef;


extern data_dust_uart_typedef DUST;

void Dust_UART_Read(uint8_t port);
void Dust_DIGITAL_Read(uint8_t port);
void get_Dust(uint16_t port);


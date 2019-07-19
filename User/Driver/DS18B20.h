#include "GPIO.h"

#define INACTIVE 		0x00
#define ACTIVE			0x01


typedef struct {
	
	int16_t Temp[NUM_SAMP_RESPONSE+1];
	uint8_t Data_Temp[9];
	uint8_t check_data;
	int16_t Base_Temp;
	int16_t Offset_Temp;
	uint8_t flag;
	
}data_temp_typedef;


extern data_temp_typedef TEMP;

uint8_t DS18B20_Read(uint8_t port);

void get_Temp(uint16_t port);

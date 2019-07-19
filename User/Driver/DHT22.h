#include "GPIO.h"


typedef struct
{
	uint16_t rh_raw;
	uint16_t rh[NUM_SAMP_RESPONSE+1];
	uint8_t buff_rh[16];
	uint8_t buff_temp[16];
	uint8_t buff_chekcsum[16];
	int16_t temp_raw;
	int16_t temp[NUM_SAMP_RESPONSE+1];
	uint8_t check_sum;
	uint8_t check;
	int16_t Base_RH;
	int16_t Offset_RH;
	int16_t Base_Temp;
	int16_t Offset_Temp;
	uint8_t flag_rh;
	uint8_t flag_temp;
	
}dht22_typedef;


extern dht22_typedef dht22;

void DHT22_Read(uint8_t port);

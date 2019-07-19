#include "GPIO.h"

typedef struct
{
	uint8_t data[8];
	uint16_t check_crc;
	uint16_t value;
	uint16_t degree;
	uint16_t base;
	int32_t offset;
	uint8_t flag;
	uint8_t flag_start;
	uint8_t buff_cmd[8];
	uint8_t flag_cmd;
	
}data_wind_typedef;


extern data_wind_typedef WIND_SPEED;
extern data_wind_typedef WIND_DIRECT;


void WIND_DIRECT_Read(uint8_t port);
void WIND_SPEED_Read(uint8_t port);
void get_Wind_Speed(uint16_t port);
void get_Wind_Direct(uint16_t port);



#include "GPIO.h"


typedef struct
{
	int32_t lc_offset;
	int32_t lc_base;
	int32_t lc_value;
	uint8_t flag;
	int32_t lc_ratio;

}data_lc_typedef;


extern data_lc_typedef data_lc;


void HX711_Read(uint8_t port);




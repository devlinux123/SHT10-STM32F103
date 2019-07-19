#include "GPIO.h"



typedef struct
{
	double_t ratio_temp;
	double_t ratio_humi;
	uint32_t base;
	uint8_t flag;
	uint8_t flag_temp;
	uint8_t flag_humi;
	uint32_t Voltage;
	uint32_t value;
	uint16_t value_samp[NUM_SAMP_RESPONSE*5];
	uint32_t Rs;
	uint32_t Ro;
	double_t Ratio;
	
}data_mq_typedef;



extern data_mq_typedef CO;
extern data_mq_typedef H2;
extern data_mq_typedef GAS;



void H2_Read(uint8_t port);
void CO_Read(uint8_t port);
void Gas_Read(uint8_t port);
void get_H2(uint16_t port);
void get_CO(uint16_t port);
void get_GAS(uint16_t port);



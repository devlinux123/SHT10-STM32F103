#include "GPIO.h"



#define BMP180_MODE_TEMPERATURE		((uint8_t)0x2E)
#define BMP180_MODE_PRESSURE			((uint8_t)0x34)
#define BMP180_MSB								((uint8_t)0xF6)
#define BMP180_CONTROL						((uint8_t)0xF4)
#define BMP180_MODULE_ADDR				((uint8_t)0x77)
#define BMP180_CALIB							((uint8_t)0xAA)


typedef struct
{
	int32_t val_B5;
	uint8_t check;
	int32_t temp;
	int32_t value;
	uint32_t Base_value;
	int32_t Offset_value;
	int32_t value_samp[NUM_SAMP_RESPONSE + 1];
	uint8_t flag;
	int16_t AC1;
	int16_t AC2;
	int16_t AC3;	
	uint16_t AC4;
	uint16_t AC5;
	uint16_t AC6;
	int16_t B1;
	int16_t B2;
	int16_t MB;
	int16_t MC;
	int16_t MD;
	uint8_t data[22];
	int16_t altitude;
}data_pressure_typedef;



extern data_pressure_typedef PRESSURE;


void BMP180_ReadCalib(uint8_t module_addr,uint8_t reg_addr, uint8_t port);
int32_t BMP180_ReadTemp(uint8_t port);
int32_t BMP180_ReadPressure(uint8_t port);
void get_Pressure(uint16_t port);



#include "GPIO.h"

#define INACTIVE		0x00
#define ACTIVE			0x01

typedef struct
{
	uint8_t data[100];
	
}i2c_typedef;

extern i2c_typedef i2c;



void I2C_StartCondition(uint8_t port);
void I2C_StopCondition(uint8_t port);
void I2C_Pulse(uint8_t port, uint8_t times);
uint16_t I2C_Read(uint8_t module_addr,uint8_t reg_addr, uint8_t port);
uint8_t I2C_Write(uint8_t module_addr,uint8_t reg_addr, uint8_t port,uint8_t data);
void I2C_ReadBuffer(uint8_t module_addr,uint8_t reg_addr, uint8_t port, uint8_t lenght);


#include "GPIO.h"

#define MLX90614_CMD						(uint8_t)0x07
#define MLX90614_POLY						(uint8_t)0x07
#define MLX90614_SA							(uint8_t)0x5A


typedef struct
{
	uint16_t dataM;
	uint16_t dataL;
	uint16_t data;
	uint8_t ack;
	uint8_t flag;
	uint8_t crc;
	uint8_t crc_temp;
	uint8_t crc_check;
	double Temp;
}data_mlx_typedef;

extern data_mlx_typedef data_mlx;



void MLX90614_Read(uint8_t addr, uint8_t port);


#include "MLX90614.h"
#include "I2C.h"
#include "SHT1x.h"


data_mlx_typedef data_mlx;


void MLX90614_Read(uint8_t addr, uint8_t port)
{
	I2C_ReadBuffer(addr, MLX90614_CMD, port, 3);
	data_mlx.dataL = i2c.data[0];
	data_mlx.dataM = i2c.data[1];
	data_mlx.data = data_mlx.dataM << 8 | data_mlx.dataL;
	data_mlx.crc = i2c.data[2];
	data_mlx.crc_check = SHT1x_CRC8_Check(data_mlx.data, MLX90614_CMD, MLX90614_POLY);
	if(data_mlx.crc_check == data_mlx.crc)
	{
		data_mlx.Temp = (data_mlx.data*2 - 27315)/10.0f;
		printf("Temp = %.1f\r\n",(double)data_mlx.Temp/10);
	}
}

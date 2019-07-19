#include "BMP180.h"
#include "I2C.h"
#include "UART.h"

data_pressure_typedef PRESSURE =
{
	.flag = FLAG_INACTIVE,
};

void BMP180_ReadCalib(uint8_t module_addr,uint8_t reg_addr, uint8_t port)
{
	I2C_ReadBuffer(BMP180_MODULE_ADDR,BMP180_CALIB, port, 22);
	PRESSURE.AC1 = (int16_t)i2c.data[0]*256 + i2c.data[1];
	PRESSURE.AC2 = (int16_t)i2c.data[2]*256 + i2c.data[3];
	PRESSURE.AC3 = (int16_t)i2c.data[4]*256 + i2c.data[5];
	PRESSURE.AC4 = (uint16_t)i2c.data[6]*256 + i2c.data[7];
	PRESSURE.AC5 = (uint16_t)i2c.data[8]*256 + i2c.data[9];
	PRESSURE.AC6 = (uint16_t)i2c.data[10]*256 + i2c.data[11];
	PRESSURE.B1 = (int16_t)i2c.data[12]*256 + i2c.data[13];
	PRESSURE.B2 = (int16_t)i2c.data[14]*256 + i2c.data[15];
	PRESSURE.MB = (int16_t)i2c.data[16]*256 + i2c.data[17];
	PRESSURE.MC = (int16_t)i2c.data[18]*256 + i2c.data[19];
	PRESSURE.MD = (int16_t)i2c.data[20]*256 + i2c.data[21];
}

int32_t BMP180_ReadTemp(uint8_t port)
{
	int32_t UT, x1, x2, temp;
	I2C_Write(BMP180_MODULE_ADDR, BMP180_CONTROL, port, BMP180_MODE_TEMPERATURE);
	delay_us(4500);
	UT = I2C_Read(BMP180_MODULE_ADDR, BMP180_MSB, port);
	x1 = ((UT - PRESSURE.AC6) * PRESSURE.AC5) >> 15;
	x2 = (PRESSURE.MC << 11) / (x1 + PRESSURE.MD);
	PRESSURE.val_B5 = x1 + x2;
	temp = ((PRESSURE.val_B5 + 8) >> 4);
	return temp;
}

int32_t BMP180_ReadPressure(uint8_t port)
{
	int32_t B3,B6,X3,p,UP;
	uint32_t B4,B7;
	I2C_Write(BMP180_MODULE_ADDR, BMP180_CONTROL, port, BMP180_MODE_PRESSURE);
	delay_us(4500);
	UP = I2C_Read(BMP180_MODULE_ADDR,BMP180_MSB, port);
	B6 = PRESSURE.val_B5 - 4000;
	X3 = ((PRESSURE.B2 * ((B6 * B6) >> 12)) >> 11) + ((PRESSURE.AC2 * B6) >> 11);
	B3 = (((((int32_t)PRESSURE.AC1) * 4 + X3) << 0) + 2) >> 2;
	X3 = (((PRESSURE.AC3 * B6) >> 13) + ((PRESSURE.B1 * ((B6 * B6) >> 12)) >> 16) + 2) >> 2;
	B4 = (PRESSURE.AC4 * (uint32_t)(X3 + 32768)) >> 15;
	B7 = ((uint32_t)UP - B3) * (50000 >> 0);
	if (B7 < 0x80000000) p = (B7 << 1) / B4; else p = (B7 / B4) << 1;
	p += ((((p >> 8) * (p >> 8) * 3038) >> 16) + ((-7357 * p) >> 16) + 3791) >> 4;
	return p;
}

void get_Pressure(uint16_t port)
{
	uartPC_putchar(SECURITY);
	uartPC_putchar(START);
	uartPC_putchar(SIZE_H);
	uartPC_putchar(SIZE_L);
	uartPC_putchar(STATUS);
	uartPC_putchar(ID_PAN);
	uartPC_putchar(ID_GROUP);
	uartPC_putData(port, 2);
	uartPC_putData(ID_GATEWAY,2);
	uartPC_putData(PACKET_INDEX,2);
	uartPC_putchar(PROPERTY_PRESSURE);
	UART_rf.check_sum = CHECK_SUM0_PRESSURE + port;
	uartPC_putData(PRESSURE.value/10, 2);
	uartPC_putchar(UART_rf.check_sum);
}


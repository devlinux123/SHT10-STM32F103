#include "SHT1x.h"
#include "TIMER.h"
#include "UART.h"

RH_typedef HUMI =
{
	.Data_RH = 0,
	.Data_Temp = 0,
	.RH_Linear = 0.0f,	
	.RH_True = 0.0f,
	.Temp = 0.0f,
	.crc = 0,
	.crc_rh = 0,
	.crc_temp = 0,
	.crc_check = 0,
	.flag = FLAG_INACTIVE,
};



int16_t SHT1x_Read(uint8_t addr, uint8_t port) // dia chi cam bien, port cam bien
{
	uint8_t ack = INACTIVE;
	int16_t read_data = 0;
	uint32_t i;
	HUMI.crc = 0;
	
	SHT1x_StartCondition(port); // khoi tao cam bien
	for(i = 0; i < 8; i++)
	{
		if(((addr << i) & 0x80) == 0x80) Set_SDO(port);
		else Reset_SDO(port);
		Pulse_SCL(port, 1);
	}
	Reset_SDO(port);
	Pulse_SCL(port, 1);
	delay_us(1);
	Set_SDO(port);
	config_SDO_Input(port);
	for(i = 0; i < 2100000; i++)
	{
		if(State_SDO(port) == 0)
		{
			ack = ACTIVE;
			i = 2100000;
		}
	}
	if(ack == ACTIVE)
	{
		for(i = 0; i < 8; i++)
		{
			Set_SCL(port);
			read_data = read_data << 1;
			if(State_SDO(port) == 0)
			{
				read_data = read_data | 0x0000;
			}
			else
			{
				read_data = read_data | 0x0001;
			}
			Reset_SCL(port);
			delay_us(1);
		}
		SHT1x_ACK(port);
		for(i = 0; i < 8; i++)
		{
			Set_SCL(port);
			read_data = read_data << 1;
			if(State_SDO(port) == 0)
			{
				read_data = read_data | 0x0000;
			}
			else
			{
				read_data = read_data | 0x0001;
			}
			Reset_SCL(port);
		}
		SHT1x_ACK(port);
		for(i = 0; i < 8; i++)
		{
			Set_SCL(port);
			HUMI.crc = HUMI.crc >> 1;
			if(State_SDO(port) == 0)
			{
				HUMI.crc = HUMI.crc | 0x00;
			}
			else
			{
				HUMI.crc = HUMI.crc | 0x80;
			}
			Reset_SCL(port);
		}
		SHT1x_StopCondition(port);
		return read_data;
	}
	else
	{
		return -1;
	}
}




void SHT1x_StartCondition(uint8_t port) //Start I2C SHT1x__
{
	config_SDO_Output(port);// cai dat port SDO--> chan data la output (Port 1->10
	Set_SCL(port);	//Set port cho SCL len muc cao
	delay_us(1);
	Reset_SDO(port); // Reset port cho SDO xuong muc thap
	delay_us(1);
	Reset_SCL(port); //Reset port cho SCL xuong muc thap
	delay_us(1);
	Set_SCL(port);   //Set SCL port cho SCL len muc cao
	delay_us(1);
	Set_SDO(port);
	delay_us(1);
	Reset_SCL(port);
}
void SHT1x_StopCondition(uint8_t port)
{
	config_SDO_Output(port);
	Set_SDO(port);
	Pulse_SCL(port, 1);
}
void SHT1x_ACK(uint8_t port)
{
	config_SDO_Output(port);
	Reset_SDO(port);
	Pulse_SCL(port, 1);
	config_SDO_Input(port);
}
uint8_t SHT1x_CRC8_Check(uint32_t data, uint32_t addr, uint8_t polynomial)
{
	uint32_t divisor;
	uint8_t i;
	data = data*256 + addr;
	divisor = 0x80000000;
	divisor = divisor + (polynomial*8388608);
	for(i = 0; i < 24; i++)
	{
		if(((data << i) & 0x80000000) == 0x80000000)
		{
			data = data ^ divisor;
		}
		divisor = divisor >> 1;
	}
	return data;
}

void get_RH(uint16_t port)
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
	uartPC_putchar(PROPERTY_HUMI);
	UART_rf.check_sum = CHECK_SUM0_HUMI +  port;
	uartPC_putData(HUMI.RH[NUM_SAMP_RESPONSE], 2);
	uartPC_putchar(UART_rf.check_sum);
}



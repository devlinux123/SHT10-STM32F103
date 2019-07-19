#include "YGC-Series.h"
#include "TIMER.h"
#include "UART.h"
#include "FLASH.h"


data_wind_typedef WIND_SPEED =
{
	.flag = FLAG_INACTIVE,
	.value = 0,
	.flag_cmd = FLAG_INACTIVE,
	.flag_start = FLAG_ACTIVE,
};
data_wind_typedef WIND_DIRECT =
{
	.flag = FLAG_INACTIVE,
	.value = 0,
	.flag_cmd = FLAG_INACTIVE,
	.flag_start = FLAG_ACTIVE,
};




uint16_t Wind_CRC16(char* p, uint16_t datalen)
{
	uint16_t CRC16Lo = 0xFF, CRC16Hi = 0xFF, CL = 0x01, CH = 0xA0, SaveHi, SaveLo;
	uint8_t i, flag;
	for(i = 0;i < datalen; i++)
	{
		CRC16Lo = CRC16Lo ^ *(p+i);
		for(flag = 0; flag < 8; flag++)
		{
			SaveHi = CRC16Hi;
			SaveLo = CRC16Lo;
			CRC16Hi = CRC16Hi >> 1;
			CRC16Lo = CRC16Lo >> 1;
			if((SaveHi&0x01) == 0x01) CRC16Lo = CRC16Lo | 0x80;
			if((SaveLo&0x01) == 0x01)
			{
				CRC16Hi = CRC16Hi ^ CH;
				CRC16Lo = CRC16Lo ^ CL;
			}
		}
	}
	return (CRC16Hi << 8) | CRC16Lo;
}



void WIND_SPEED_Read(uint8_t port) //YGC-FS
{
	uint8_t buf[10], i, flag = FLAG_INACTIVE;
	uint32_t start_time, stop_time = 10;
	memset(WIND_SPEED.data, 0, 8);
	if(WIND_SPEED.flag_cmd == FLAG_ACTIVE)
	{
		WIND_SPEED.flag_cmd = FLAG_INACTIVE;
		for(i = 0; i < 8; i++)
		{
			Transmit_Cmd(port,WIND_SPEED.buff_cmd[i]);
		}
	}
	buf[0] = 0x00; //default ID = 0x00
	buf[1] = 0x03;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x01;
	buf[6] = 0x85; //CRC-LOW
	buf[7] = 0xDB; //CRC-HIGH
	
	Set_SCL(port);
	for(i = 0; i < 8; i++) Transmit_Cmd(port, buf[i]);
	Reset_SCL(port);
	start_time = System_GetTick();
	while(System_GetTick() - start_time < stop_time)
	{
		if(State_SDI(port) == 0)
		{
			flag = FLAG_ACTIVE;
			stop_time = 0;
		}
	}
	if(flag == FLAG_ACTIVE)
	{
		
		for(i = 0; i < 7; i++) {
			WIND_SPEED.data[i] = Receive_data(port, WIND_SPEED.flag_start);
		}
		WIND_SPEED.check_crc = Wind_CRC16((char*)WIND_SPEED.data, 5);
		if(WIND_SPEED.check_crc == ((uint16_t)WIND_SPEED.data[6] << 8 | WIND_SPEED.data[5]))
		{
			if(WIND_SPEED.flag == FLAG_INACTIVE)
				{
					WIND_SPEED.value = (uint16_t)WIND_SPEED.data[3]*256 + WIND_SPEED.data[4];
					WIND_SPEED.value = WIND_SPEED.value + WIND_SPEED.offset;
					if(WIND_SPEED.value < 3) WIND_SPEED.value = 0;
				}
				else if(WIND_SPEED.flag == FLAG_ACTIVE)
				{
					if(WIND_SPEED.check_crc == ((uint16_t)WIND_SPEED.data[6] << 8 | WIND_SPEED.data[5]))
					{
						WIND_SPEED.value = (uint16_t)WIND_SPEED.data[3]*256 + WIND_SPEED.data[4];
						WIND_SPEED.value = WIND_SPEED.value + WIND_SPEED.offset;
					}
					WIND_SPEED.offset += (int32_t)WIND_SPEED.base - WIND_SPEED.value;
					write_FLASH();
					WIND_SPEED.flag = FLAG_INACTIVE;
				}
		}
	}
}

void WIND_DIRECT_Read(uint8_t port) //YGC-FX
{
	uint8_t buf[10], i, flag = FLAG_INACTIVE;
	uint32_t start_time, stop_time = 10;
	memset(WIND_DIRECT.data, 0, 8);
	if(WIND_DIRECT.flag_cmd == FLAG_ACTIVE)
	{
		WIND_DIRECT.flag_cmd = FLAG_INACTIVE;
		for(i = 0; i < 8; i++)
		{
			Transmit_Cmd(port,WIND_DIRECT.buff_cmd[i]);
		}
	}
	buf[0] = 0x00; //default ID = 0x00
	buf[1] = 0x03;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x01;
	buf[6] = 0x85; //CRC-LOW
	buf[7] = 0xDB; //CRC-HIGH
	
	Set_SCL(port);
	for(i = 0; i < 8; i++) Transmit_Cmd(port, buf[i]);
	Reset_SCL(port);
	start_time = System_GetTick();
	while(System_GetTick() - start_time < stop_time)
	{
		if(State_SDI(port) == 0)
		{
			flag = FLAG_ACTIVE;
			stop_time = 0;
		}
	}
	if(flag == FLAG_ACTIVE)
	{
		for(i = 0; i < 7; i++) 
		{
			WIND_DIRECT.data[i] = Receive_data(port, WIND_DIRECT.flag_start);
		}
		WIND_DIRECT.check_crc = Wind_CRC16((char*)WIND_DIRECT.data, 5);
		if(WIND_DIRECT.check_crc == ((uint16_t)WIND_DIRECT.data[6] << 8 | WIND_DIRECT.data[5]))
		{
			if(WIND_DIRECT.flag == FLAG_INACTIVE)
				{
					WIND_DIRECT.degree = (uint16_t)WIND_DIRECT.data[3]*256 + WIND_DIRECT.data[4];
					WIND_DIRECT.degree = WIND_DIRECT.degree + WIND_DIRECT.offset;
					if(WIND_SPEED.value == 0) 
					{
						WIND_DIRECT.value = 0;
						WIND_DIRECT.degree = 0;
					}
					else
					{
						WIND_DIRECT.value = (WIND_DIRECT.degree + 11.25f)/22.5f;
						WIND_DIRECT.value = (WIND_DIRECT.value%16) + 1;
					}
				}
		else if(WIND_DIRECT.flag == FLAG_ACTIVE)
		{
			if(WIND_DIRECT.check_crc == ((uint16_t)WIND_DIRECT.data[6] << 8 | WIND_DIRECT.data[5]))
			{
				WIND_DIRECT.degree = (uint16_t)WIND_DIRECT.data[3]*256 + WIND_DIRECT.data[4];
				WIND_DIRECT.degree = WIND_DIRECT.degree + WIND_DIRECT.offset;
				WIND_DIRECT.value = (WIND_DIRECT.degree + 11.25f)/22.5f;
				WIND_DIRECT.value = (WIND_DIRECT.value%16) + 1;
			}
			WIND_DIRECT.offset += (int32_t)WIND_DIRECT.base - WIND_DIRECT.value;
			write_FLASH();
			WIND_DIRECT.flag = FLAG_INACTIVE;
		}
		}
	}
}

void get_Wind_Speed(uint16_t port)
{
	uartPC_putchar(SECURITY);
	uartPC_putchar(START);
	uartPC_putchar(SIZE_H);
	uartPC_putchar(SIZE_L);
	uartPC_putchar(STATUS);
	uartPC_putchar(ID_PAN);
	uartPC_putchar(ID_GROUP);
	uartPC_putData(port+1, 2);
	uartPC_putData(ID_GATEWAY,2);
	uartPC_putData(PACKET_INDEX,2);
	uartPC_putchar(PROPERTY_WIND_SPEED);
	UART_rf.check_sum = CHECK_SUM0_WIND_SPEED + port + 1;
	uartPC_putData(WIND_SPEED.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}

void get_Wind_Direct(uint16_t port)
{
	uartPC_putchar(SECURITY);
	uartPC_putchar(START);
	uartPC_putchar(SIZE_H);
	uartPC_putchar(SIZE_L_3B);
	uartPC_putchar(STATUS);
	uartPC_putchar(ID_PAN);
	uartPC_putchar(ID_GROUP);
	uartPC_putData(port+1, 2);
	uartPC_putData(ID_GATEWAY,2);
	uartPC_putData(PACKET_INDEX,2);
	uartPC_putchar(PROPERTY_WIND_DIRECT);
	UART_rf.check_sum = CHECK_SUM0_WIND_DIRECT + port + 1;
	uartPC_putData(WIND_DIRECT.value, 1);
	uartPC_putData(WIND_DIRECT.degree, 2);
	uartPC_putchar(UART_rf.check_sum);
}


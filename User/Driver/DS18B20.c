#include "DS18B20.h"
#include "UART.h"

data_temp_typedef TEMP =
{
	.check_data = 0,
	.flag = FLAG_INACTIVE,
};


uint8_t DS18B20_Read(uint8_t port)
{
	uint32_t i, j;
	uint8_t init_read, skip_rom, conversion_temp, scratchpad;
	for(i = 0; i < 9; i++) TEMP.Data_Temp[i] = 0;
	init_read = INACTIVE;
	skip_rom = 0xcc;
	conversion_temp = 0x44;
	scratchpad = 0xbe;
	config_SDO_Output(port);
	Reset_SDO(port);
	delay_us(690);
	config_SDO_Input(port);
	for(i = 0; i < 350; i++)  // >~60us
	{
		if(State_SDO(port) == 0)
		{
			for(i = 0; i < 1500; i++)
			{
				if(State_SDO(port) == 1)
				{
					init_read = ACTIVE;
					i = 6900;
				}
			}
		}
	}
	if(init_read == ACTIVE)
	{
		init_read = INACTIVE;
		config_SDO_Output(port);
		Set_SDO(port);
		for(i = 0; i < 8; i++)
		{
			Reset_SDO(port);
			if(((skip_rom >> i) & 0x01) == 0x01)
			{
				delay_us(2);
				Set_SDO(port);
			}
			delay_us(69);
			Set_SDO(port);
			delay_us(3);
		}
		for(i = 0; i < 8; i++)
		{
			Reset_SDO(port);
			if(((conversion_temp >> i) & 0x01) == 0x01)
			{
				delay_us(2);
				Set_SDO(port);
			}
			delay_us(69);
			Set_SDO(port);
			delay_us(3);
		}
		delay_ms(969);
		Reset_SDO(port);
		delay_us(690);
		config_SDO_Input(port);
		for(i = 0; i < 350; i++)  // >~60us
		{
			if(State_SDO(port) == 0)
			{
				for(i = 0; i < 1500; i++)
				{
					if(State_SDO(port) == 1)
					{
						init_read = ACTIVE;
						i = 6900;
					}
				}
			}
		}
		if(init_read == ACTIVE)
		{
			init_read = INACTIVE;
			config_SDO_Output(port);
			Set_SDO(port);
			for(i = 0; i < 8; i++)
			{
				Reset_SDO(port);
				if(((skip_rom >> i) & 0x01) == 0x01)
				{
					delay_us(2);
					Set_SDO(port);
				}
				delay_us(69);
				Set_SDO(port);
				delay_us(3);
			}
			for(i = 0; i < 8; i++)
			{
				Reset_SDO(port);
				if(((scratchpad >> i) & 0x01) == 0x01)
				{
					delay_us(2);
					Set_SDO(port);
				}
				delay_us(69);
				Set_SDO(port);
				delay_us(3);
			}
			for(j = 0; j < 9; j++)
			{
				for(i = 0 ; i < 8; i++)
				{
					config_SDO_Output(port);
					Reset_SDO(port);
					delay_us(2);
					config_SDO_Input(port);
					TEMP.Data_Temp[j] = TEMP.Data_Temp[j] >> 1;
					if(State_SDO(port) == 0)
					{
						TEMP.Data_Temp[j] = TEMP.Data_Temp[j] | 0x00;			
					}
					else {TEMP.Data_Temp[j] = TEMP.Data_Temp[j] | 0x80;}
					delay_us(69);
				}
			}
		}
	}
	if(TEMP.Data_Temp[7] == 16 & TEMP.Data_Temp[6] == 12 & TEMP.Data_Temp[5] == 255 
			& TEMP.Data_Temp[4] == 127 & TEMP.Data_Temp[3] == 70 & TEMP.Data_Temp[2] == 75)
	{
		return 1;
	}
	else return 0;
}


void get_Temp(uint16_t port)
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
	uartPC_putchar(PROPERTY_TEMP);
	UART_rf.check_sum = CHECK_SUM0_TEMP + port;
	uartPC_putData(TEMP.Temp[NUM_SAMP_RESPONSE], 2);
	uartPC_putchar(UART_rf.check_sum);
}



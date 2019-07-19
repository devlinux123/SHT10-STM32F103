#include "I2C.h"

i2c_typedef i2c;







uint16_t I2C_Read(uint8_t module_addr,uint8_t reg_addr, uint8_t port)
{
	uint8_t i, ack = INACTIVE, dataL = 0, dataH = 0;
	uint16_t data = 0;
	module_addr = module_addr*2;
	I2C_StartCondition(port);
	for(i = 0; i < 8; i++) //module_addr write
	{
		if(((module_addr << i) & 0x80) == 0x80) Set_SDO(port);
		else Reset_SDO(port);
		I2C_Pulse(port, 1);
	}
	config_SDO_Input(port);
	delay_us(5);
	Set_SCL(port);
	delay_us(5);
	for(i = 0; i < 210; i++)
	{
		if(State_SDO(port) == 0)
		{
			i = 210;
			ack = ACTIVE;
		}else ack = INACTIVE;
	}
	Reset_SCL(port);
	if(ack == ACTIVE)
	{
		ack = INACTIVE;
		Reset_SDO(port);
		config_SDO_Output(port);
		for(i = 0; i < 8; i++) //write reg_addr
		{
			if(((reg_addr << i) & 0x80) == 0x80) Set_SDO(port);
			else Reset_SDO(port);
			I2C_Pulse(port, 1);
		}
		config_SDO_Input(port);
		delay_us(5);
		Set_SCL(port);
		delay_us(5);
		for(i = 0; i < 210; i++)
		{
			if(State_SDO(port) == 0)
			{
				i = 210;
				ack = ACTIVE;
		}else ack = INACTIVE;
		}
		Reset_SCL(port);
		if(ack == ACTIVE)
		{
			ack = INACTIVE;
			module_addr = module_addr + 1;
			I2C_StartCondition(port);
			for(i = 0; i < 8; i++) //module_addr read
			{
				if(((module_addr << i) & 0x80) == 0x80) Set_SDO(port);
				else Reset_SDO(port);
				I2C_Pulse(port, 1);
			}
			config_SDO_Input(port);
			delay_us(5);
			Set_SCL(port);
			delay_us(5);
			for(i = 0; i < 210; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 210;
					ack = ACTIVE;
		}else ack = INACTIVE;
			}
			Reset_SCL(port);
			delay_us(5);
			if(ack == ACTIVE)
			{
				ack = INACTIVE;
				for(i = 0; i < 8; i++) // MSB
				{
					Set_SCL(port);
					delay_us(5);
					dataH = dataH << 1;
					if(State_SDO(port) == 1) dataH += 0x01;
					else dataH += 0x00;
					Reset_SCL(port);
					delay_us(5);
				}
				config_SDO_Output(port);
				Reset_SDO(port);
				I2C_Pulse(port, 1);
				config_SDO_Input(port);
				for(i = 0; i < 8; i++) // LSB
				{
					Set_SCL(port);
					delay_us(5);
					dataL = dataL << 1;
					if(State_SDO(port) == 1) dataL += 0x01;
					else dataL += 0x00;
					Reset_SCL(port);
					delay_us(5);
				}
				config_SDO_Output(port);
				Set_SDO(port);
				I2C_Pulse(port, 1);
				Reset_SDO(port);
				I2C_Pulse(port, 1);
				I2C_StopCondition(port);
			}
		}
	}
	data = (uint16_t)dataH << 8 | dataL;
	return data;
}

void I2C_ReadBuffer(uint8_t module_addr,uint8_t reg_addr, uint8_t port, uint8_t lenght)
{
	uint8_t i, j, ack = INACTIVE;
	module_addr = module_addr*2;
	I2C_StartCondition(port);
	for(i = 0; i < 8; i++) //module_addr write
	{
		if(((module_addr << i) & 0x80) == 0x80) Set_SDO(port);
		else Reset_SDO(port);
		I2C_Pulse(port, 1);
	}
	config_SDO_Input(port);
	delay_us(5);
	Set_SCL(port);
	delay_us(5);
	for(i = 0; i < 210; i++)
	{
		if(State_SDO(port) == 0)
		{
			i = 210;
			ack = ACTIVE;
		}else ack = INACTIVE;
	}
	Reset_SCL(port);
	if(ack == ACTIVE)
	{
		ack = INACTIVE;
		Reset_SDO(port);
		config_SDO_Output(port);
		for(i = 0; i < 8; i++) //write reg_addr
		{
			if(((reg_addr << i) & 0x80) == 0x80) Set_SDO(port);
			else Reset_SDO(port);
			I2C_Pulse(port, 1);
		}
		config_SDO_Input(port);
		delay_us(5);
		Set_SCL(port);
		delay_us(5);
		for(i = 0; i < 210; i++)
		{
			if(State_SDO(port) == 0)
			{
				i = 210;
				ack = ACTIVE;
		}else ack = INACTIVE;
		}
		Reset_SCL(port);
		if(ack == ACTIVE)
		{
			ack = INACTIVE;
			module_addr = module_addr + 1;
			I2C_StartCondition(port);
			for(i = 0; i < 8; i++) //module_addr read
			{
				if(((module_addr << i) & 0x80) == 0x80) Set_SDO(port);
				else Reset_SDO(port);
				I2C_Pulse(port, 1);
			}
			config_SDO_Input(port);
			delay_us(5);
			Set_SCL(port);
			delay_us(5);
			for(i = 0; i < 210; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 210;
					ack = ACTIVE;
		}else ack = INACTIVE;
			}
			Reset_SCL(port);
			delay_us(5);
			if(ack == ACTIVE)
			{
				ack = INACTIVE;
				for(j = 0; j < lenght - 1; j++)
				{
					for(i = 0; i < 8; i++)
					{
						Set_SCL(port);
						delay_us(5);
						i2c.data[j] = i2c.data[j] << 1;
						if(State_SDO(port) == 1) i2c.data[j] += 0x01;
						else i2c.data[j] += 0x00;
						Reset_SCL(port);
						delay_us(5);
					}
					config_SDO_Output(port);
					Reset_SDO(port);
					I2C_Pulse(port, 1);
					config_SDO_Input(port);
				}
				for(i = 0; i < 8; i++)
				{
					Set_SCL(port);
					delay_us(5);
					i2c.data[lenght - 1] = i2c.data[lenght - 1] << 1;
					if(State_SDO(port) == 1) i2c.data[lenght - 1] += 0x01;
					else i2c.data[lenght - 1] += 0x00;
					Reset_SCL(port);
					delay_us(5);
				}
				config_SDO_Output(port);
				Set_SDO(port);
				I2C_Pulse(port, 1);
				Reset_SDO(port);
				I2C_Pulse(port, 1);
				I2C_StopCondition(port);
			}
		}
	}
}

uint8_t I2C_Write(uint8_t module_addr,uint8_t reg_addr, uint8_t port,uint8_t data)
{
	uint8_t i, ack = INACTIVE;
	module_addr = module_addr*2;
	I2C_StartCondition(port);
	for(i = 0; i < 8; i++)
	{
		if(((module_addr << i) & 0x80) == 0x80) Set_SDO(port);
		else Reset_SDO(port);
		I2C_Pulse(port, 1);
	}
	config_SDO_Input(port);
	delay_us(5);
	Set_SCL(port);
	delay_us(5);
	for(i = 0; i < 210; i++)
	{
		if(State_SDO(port) == 0)
		{
			i = 210;
			ack = ACTIVE;
		}else ack = INACTIVE;
	}
	Reset_SCL(port);
	if(ack == ACTIVE)
	{
		ack = INACTIVE;
		Reset_SDO(port);
		config_SDO_Output(port);
		for(i = 0; i < 8; i++)
		{
			if(((reg_addr << i) & 0x80) == 0x80) Set_SDO(port);
			else Reset_SDO(port);
			I2C_Pulse(port, 1);
		}
		config_SDO_Input(port);
		delay_us(5);
		Set_SCL(port);
		delay_us(5);
		for(i = 0; i < 210; i++)
		{
			if(State_SDO(port) == 0)
			{
				i = 210;
				ack = ACTIVE;
		}else ack = INACTIVE;
		}
		Reset_SCL(port);
		if(ack == ACTIVE)
		{
			ack = INACTIVE;
			Reset_SDO(port);
			config_SDO_Output(port);
			for(i = 0; i < 8; i++)
			{
				if(((data << i) & 0x80) == 0x80) Set_SDO(port);
				else Reset_SDO(port);
				I2C_Pulse(port, 1);
			}
			config_SDO_Input(port);
			delay_us(5);
			Set_SCL(port);
			delay_us(5);
			for(i = 0; i < 210; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 210;
					ack = ACTIVE;
		}else ack = INACTIVE;
			}
			Reset_SCL(port);
			if(ack == ACTIVE)
			{
				ack = INACTIVE;
				config_SDO_Output(port);
				Set_SCL(port);
				delay_us(5);
				Set_SDO(port);
				return 1;
			}
		}
	}
	return 0;
}



void I2C_StartCondition(uint8_t port)
{
	config_SDO_Output(port);
	Set_SDO(port);
	delay_us(5);
	Set_SCL(port);
	delay_us(5);
	Reset_SDO(port);
	delay_us(5);
	Reset_SCL(port);
	delay_us(5);
}
void I2C_StopCondition(uint8_t port)
{
	Set_SCL(port);
	delay_us(5);
	Set_SDO(port);
	delay_us(5);
}
void I2C_Pulse(uint8_t port, uint8_t times)
{
	uint8_t i;
	for(i = 0; i < times; i++)
	{
		delay_us(5);
		Set_SCL(port);
		delay_us(5);
		Reset_SCL(port);
	}
}





#include "WinSen-Series.h"
#include "UART.h"
#include "FLASH.h"
#include "TIMER.h"

data_winsen_typedef CO2 =
{
	.flag = FLAG_INACTIVE,
	.value = 0,
	.count = 0,
	.flag_start = FLAG_ACTIVE,
};


void WinSen_UART_Read(uint8_t port, data_winsen_typedef *data)
{
	uint8_t buff[20], i;
	
	buff[0] = 0xFF;
	buff[1] = 0x01;
	buff[2] = 0x86;
	buff[3] = 0x00;
	buff[4] = 0x00;
	buff[5] = 0x00;
	buff[6] = 0x00;
	buff[7] = 0x00;
	buff[8] = 0x79;
	
	if(port == PORT2)
	{
		uart2_putData(buff, 9);	
		delay_ms(30);
		if(UART2_sensor.flag == FLAG_ACTIVE)
		{
			UART2_sensor.flag = FLAG_INACTIVE;
			UART2_sensor.check_sum =0;
			for(i = 1; i < 8; i++)
			{
				UART2_sensor.check_sum += UART2_sensor.cmd[i];
			}
			UART2_sensor.check_sum = ~UART2_sensor.check_sum + 1;
			if(data->flag == FLAG_INACTIVE)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					data->value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						data->value_samp[i] = data->value_samp[i+1];
						data->value += data->value_samp[i];
					}
					data->value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3];
					data->value += data->value_samp[NUM_SAMP_RESPONSE-1];
					data->value = data->value/NUM_SAMP_RESPONSE; 
					data->value = (int32_t)data->value + data->offset;
				}
			}
			else if(data->flag == FLAG_ACTIVE)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					data->value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						data->value_samp[i] = data->value_samp[i+1];
						data->value += data->value_samp[i];
					}
					data->value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3];
					data->value += data->value_samp[NUM_SAMP_RESPONSE-1];
					data->value = data->value/NUM_SAMP_RESPONSE; 
					data->value = (int32_t)data->value + data->offset;
				}
				data->offset += (int32_t)data->base - data->value;
				write_FLASH();
				data->flag = FLAG_INACTIVE;
			}
		}
	}
	else if(port == PORT3)
	{
		uart3_putData(buff, 9);	
		delay_ms(30);
		if(UART3_sensor.flag == FLAG_ACTIVE)
		{
			UART3_sensor.flag = FLAG_INACTIVE;
			UART3_sensor.check_sum =0;
			for(i = 1; i < 8; i++)
			{UART3_sensor.check_sum += UART3_sensor.cmd[i];}
			UART3_sensor.check_sum = ~UART3_sensor.check_sum + 1;
			
			if(UART3_sensor.check_sum == UART3_sensor.cmd[8])
			{
				if(data->flag == FLAG_INACTIVE)
				{
						data->value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							data->value_samp[i] = data->value_samp[i+1];
							data->value += data->value_samp[i];
						}
						data->value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3];
						data->value += data->value_samp[NUM_SAMP_RESPONSE-1];
						data->value = data->value/NUM_SAMP_RESPONSE; 
						data->value = (int32_t)data->value + data->offset;
				}
				else if(data->flag == FLAG_ACTIVE)
				{
					if(UART3_sensor.check_sum == UART3_sensor.cmd[8])
					{
						data->value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							data->value_samp[i] = data->value_samp[i+1];
							data->value += data->value_samp[i];
						}
						data->value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3];
						data->value += data->value_samp[NUM_SAMP_RESPONSE-1];
						data->value = data->value/NUM_SAMP_RESPONSE; 
						data->value = (int32_t)data->value + data->offset;
					}
					data->offset += (int32_t)data->base - data->value;
					write_FLASH();
					data->flag = FLAG_INACTIVE;
			 }
		 }
	 }
 }
}


void WinSen_DIGITAL_Read(uint8_t port, data_winsen_typedef *data)
{
	uint32_t start_time, stop_time = 10;
	uint8_t buff[9], flag = FLAG_INACTIVE, i;
	
	buff[0] = 0xFF;
	buff[1] = 0x01;
	buff[2] = 0x86;
	buff[3] = 0x00;
	buff[4] = 0x00;
	buff[5] = 0x00;
	buff[6] = 0x00;
	buff[7] = 0x00;
	buff[8] = 0x79;
	
	for(i = 0; i < 9; i++) Transmit_Cmd(port, buff[i]);
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
		flag = FLAG_INACTIVE;
		for(i = 0; i< 9; i++) data->data[i] = Receive_data(port, data->flag_start);
		data->check_sum = 0;
		for(i = 1; i < 8; i++) data->check_sum += data->data[i];
		data->check_sum = ~data->check_sum + 1;
		if(data->check_sum == data->data[8])
		{
			if(data->flag == FLAG_INACTIVE)
			{
				for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
				{
					data->value_samp[i] = data->value_samp[i+1];
					data->value += data->value_samp[i];
				}
				data->value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)data->data[2]*256 + data->data[3];;
				data->value += data->value_samp[NUM_SAMP_RESPONSE-1];
				data->value = data->value/NUM_SAMP_RESPONSE;
				data->value	= (int32_t)data->value + data->offset;	
			}
			else if(data->flag == FLAG_ACTIVE)
			{
				data->flag = FLAG_INACTIVE;
				data->offset += (int32_t)data->base - data->value;
				write_FLASH();
			}
		}
	}
}

void get_WINSEN(uint16_t port, uint8_t property, uint8_t checksum0, uint16_t data)
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
	uartPC_putchar(property);
	UART_rf.check_sum = checksum0 + port;
	uartPC_putData(data, 2);
	uartPC_putchar(UART_rf.check_sum);
}


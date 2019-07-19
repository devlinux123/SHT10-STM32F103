#include "ZE07-CO.h"
#include "UART.h"
#include "TIMER.h"
#include "FLASH.h"


data_gas_uart_typedef data_gas_uart;



void Gas_UART_Read(uint8_t port)
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
		if(UART2_sensor.flag == 1)
		{
			UART2_sensor.flag = 0;
			UART2_sensor.check_sum =0;
			for(i = 1; i < 8; i++)
			{
				UART2_sensor.check_sum += UART2_sensor.cmd[i];
			}
			UART2_sensor.check_sum = ~UART2_sensor.check_sum + 1;
			if(data_gas_uart.flag == 0)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					data_gas_uart.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						data_gas_uart.value_samp[i] = data_gas_uart.value_samp[i+1];
						data_gas_uart.value += data_gas_uart.value_samp[i];
					}
					data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3] + (uint16_t)UART2_sensor.cmd[4]*256 + UART2_sensor.cmd[5] + (uint16_t)UART2_sensor.cmd[6]*256 + UART2_sensor.cmd[7];
					data_gas_uart.value += data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1];
					data_gas_uart.value = data_gas_uart.value/NUM_SAMP_RESPONSE; 
					data_gas_uart.value = (int32_t)data_gas_uart.value + data_gas_uart.offset;
					data_gas_uart.value = data_gas_uart.value/10;
				}
			}
			else if(data_gas_uart.flag == 1)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					data_gas_uart.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						data_gas_uart.value_samp[i] = data_gas_uart.value_samp[i+1];
						data_gas_uart.value += data_gas_uart.value_samp[i];
					}
					data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3] + (uint16_t)UART2_sensor.cmd[4]*256 + UART2_sensor.cmd[5] + (uint16_t)UART2_sensor.cmd[6]*256 + UART2_sensor.cmd[7];
					data_gas_uart.value += data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1];
					data_gas_uart.value = data_gas_uart.value/NUM_SAMP_RESPONSE; 
					data_gas_uart.value = (int32_t)data_gas_uart.value + data_gas_uart.offset;
					data_gas_uart.value = data_gas_uart.value/10;
				}
				data_gas_uart.offset = (int32_t)data_gas_uart.base - data_gas_uart.value;
				write_FLASH();
				data_gas_uart.flag = 0;
			}
		}
	}
	else if(port == PORT3)
	{
		uart3_putData(buff, 9);	
		delay_ms(30);
		if(UART3_sensor.flag == 1)
		{
			UART3_sensor.flag = 0;
			UART3_sensor.check_sum =0;
			for(i = 1; i < 8; i++)
			{UART3_sensor.check_sum += UART3_sensor.cmd[i];}
			UART3_sensor.check_sum = ~UART3_sensor.check_sum + 1;
			
			if(UART3_sensor.check_sum == UART3_sensor.cmd[8])
			{
				if(data_gas_uart.flag == 0)
				{
						data_gas_uart.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							data_gas_uart.value_samp[i] = data_gas_uart.value_samp[i+1];
							data_gas_uart.value += data_gas_uart.value_samp[i];
						}
						data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3] + (uint16_t)UART3_sensor.cmd[4]*256 + UART3_sensor.cmd[5] + (uint16_t)UART3_sensor.cmd[6]*256 + UART3_sensor.cmd[7];
						data_gas_uart.value += data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1];
						data_gas_uart.value = data_gas_uart.value/NUM_SAMP_RESPONSE; 
						data_gas_uart.value = (int32_t)data_gas_uart.value + data_gas_uart.offset;
						data_gas_uart.value = data_gas_uart.value/10;
				}
				else if(data_gas_uart.flag == 1)
				{
					if(UART3_sensor.check_sum == UART3_sensor.cmd[8])
					{
						data_gas_uart.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							data_gas_uart.value_samp[i] = data_gas_uart.value_samp[i+1];
							data_gas_uart.value += data_gas_uart.value_samp[i];
						}
						data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3] + (uint16_t)UART3_sensor.cmd[4]*256 + UART3_sensor.cmd[5] + (uint16_t)UART3_sensor.cmd[6]*256 + UART3_sensor.cmd[7];
						data_gas_uart.value += data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1];
						data_gas_uart.value = data_gas_uart.value/NUM_SAMP_RESPONSE; 
						data_gas_uart.value = (int32_t)data_gas_uart.value + data_gas_uart.offset;
						data_gas_uart.value = data_gas_uart.value/10;
					}
					data_gas_uart.offset = (int32_t)data_gas_uart.base - data_gas_uart.value;
					write_FLASH();
					data_gas_uart.flag = 0;
			 }
		 }
	 }
 }
}

void Gas_DIGITAL_Read(uint8_t port)
{
	uint32_t start_time, stop_time = 10;
	uint8_t buff[9], flag = 0, i;
	
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
			flag = 1;
			stop_time = 0;
		}
	}
	if(flag == 1)
	{
		flag = 0;
		for(i = 0; i< 9; i++) data_gas_uart.data[i] = Receive_data(port, data_gas_uart.flag_start);
		data_gas_uart.check_sum = 0;
		for(i = 1; i < 8; i++) data_gas_uart.check_sum += data_gas_uart.data[i];
		data_gas_uart.check_sum = ~data_gas_uart.check_sum + 1;
		if(data_gas_uart.check_sum == data_gas_uart.data[8])
		{
			if(data_gas_uart.flag == 0)
			{
				for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
				{
					data_gas_uart.value_samp[i] = data_gas_uart.value_samp[i+1];
					data_gas_uart.value += data_gas_uart.value_samp[i];
				}
				data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)data_gas_uart.data[2]*256 + data_gas_uart.data[3] + (uint16_t)data_gas_uart.data[4]*256 + data_gas_uart.data[5] + (uint16_t)data_gas_uart.data[6]*256 + data_gas_uart.data[7];
				data_gas_uart.value += data_gas_uart.value_samp[NUM_SAMP_RESPONSE-1];
				data_gas_uart.value = data_gas_uart.value/NUM_SAMP_RESPONSE;
				data_gas_uart.value	= (int32_t)data_gas_uart.value + data_gas_uart.offset;	
//				printf("Dust = %d ug\r\n",data_gas_uart.value);				
				data_gas_uart.value = data_gas_uart.value/10;
			}
			else if(data_gas_uart.flag == 1)
			{
				data_gas_uart.flag = 0;
				data_gas_uart.offset = (int32_t)data_gas_uart.base - data_gas_uart.value;
				write_FLASH();
			}
		}
	}
}





#include "MH-Z19B.h"
#include "UART.h"
#include "FLASH.h"
#include "TIMER.h"

data_co2_typedef CO2;


void CO2_UART_Read(uint8_t port)
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
			if(CO2.flag == 0)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[UART2_sensor.len - 1])
				{
					CO2.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						CO2.value_samp[i] = CO2.value_samp[i+1];
						CO2.value += CO2.value_samp[i];
					}
					CO2.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3];
					CO2.value += CO2.value_samp[NUM_SAMP_RESPONSE-1];
					CO2.value = CO2.value/NUM_SAMP_RESPONSE; 
					CO2.value = (int32_t)CO2.value + CO2.offset;
				//	printf("CO2_Val = %d\r\n",CO2.Value);
				//	printf("CO2_Offset = %d\r\n",CO2.co2_offset);
				}
			}
			else if(CO2.flag == 1)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[UART2_sensor.len - 1])
				{
					CO2.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						CO2.value_samp[i] = CO2.value_samp[i+1];
						CO2.value += CO2.value_samp[i];
					}
					CO2.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3];
					CO2.value += CO2.value_samp[NUM_SAMP_RESPONSE-1];
					CO2.value = CO2.value/NUM_SAMP_RESPONSE; 
					CO2.value = (int32_t)CO2.value + CO2.offset;
				}
				CO2.offset = (int32_t)CO2.base - CO2.value;
				write_FLASH();
				CO2.flag = 0;
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
			
			if(UART3_sensor.check_sum == UART3_sensor.cmd[UART3_sensor.len - 1])
			{
				if(CO2.flag == 0)
				{

						CO2.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							CO2.value_samp[i] = CO2.value_samp[i+1];
							CO2.value += CO2.value_samp[i];
						}
						CO2.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3];
						CO2.value += CO2.value_samp[NUM_SAMP_RESPONSE-1];
						CO2.value = CO2.value/NUM_SAMP_RESPONSE; 
						CO2.value = (int32_t)CO2.value + CO2.offset;
					//	printf("CO2_Val = %d\r\n",CO2.Value);
					//	printf("CO2_Offset = %d\r\n",CO2.co2_offset);
				}
				else if(CO2.flag == 1)
				{
					if(UART3_sensor.check_sum == UART3_sensor.cmd[UART3_sensor.len - 1])
					{
						CO2.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							CO2.value_samp[i] = CO2.value_samp[i+1];
							CO2.value += CO2.value_samp[i];
						}
						CO2.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3];
						CO2.value += CO2.value_samp[NUM_SAMP_RESPONSE-1];
						CO2.value = CO2.value/NUM_SAMP_RESPONSE; 
						CO2.value = (int32_t)CO2.value + CO2.offset;
					}
					CO2.offset = (int32_t)CO2.base - CO2.value;
					write_FLASH();
					CO2.flag = 0;
			 }
		 }
	 }
 }
}
void CO2_DIGITAL_Read(uint8_t port)
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
		for(i = 0; i< 9; i++) CO2.data[i] = Receive_data(port, CO2.flag_start);
		CO2.check_sum = 0;
		for(i = 1; i < 8; i++) CO2.check_sum += CO2.data[i];
		CO2.check_sum = ~CO2.check_sum + 1;
		if(CO2.check_sum == CO2.data[8])
		{
			if(CO2.flag == 0)
			{
				CO2.value = 0;
				for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
				{
					CO2.value_samp[i] = CO2.value_samp[i+1];
					CO2.value += CO2.value_samp[i];
				}
				CO2.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)CO2.data[2]*256 + CO2.data[3];
				CO2.value += CO2.value_samp[NUM_SAMP_RESPONSE-1];
				CO2.value = CO2.value/NUM_SAMP_RESPONSE;
				CO2.value = (int32_t)CO2.value + CO2.offset;				
//				printf("CO2 = %d ppm\r\n",CO2.value);
			}
			else if(CO2.flag == 1)
			{
				CO2.offset = (int32_t)CO2.base - CO2.value;
				write_FLASH();
				CO2.flag = 0;
			}
		}
	}
}

void get_CO2(uint16_t port)
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
	uartPC_putchar(PROPERTY_CO2);
	UART_rf.check_sum = CHECK_SUM0_CO2 +  port + 1;
	uartPC_putData(CO2.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}



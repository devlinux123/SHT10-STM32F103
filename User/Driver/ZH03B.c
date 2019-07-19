#include "ZH03B.h"
#include "UART.h"
#include "FLASH.h"
#include "TIMER.h"

data_dust_uart_typedef DUST =
{
	.flag = FLAG_INACTIVE,
	.flag_start = FLAG_ACTIVE,
};

void Dust_UART_Read(uint8_t port)
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
			if(DUST.flag == FLAG_INACTIVE)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					DUST.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						DUST.value_samp[i] = DUST.value_samp[i+1];
						DUST.value += DUST.value_samp[i];
					}
					DUST.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3] + (uint16_t)UART2_sensor.cmd[4]*256 + UART2_sensor.cmd[5] + (uint16_t)UART2_sensor.cmd[6]*256 + UART2_sensor.cmd[7];
					DUST.value += DUST.value_samp[NUM_SAMP_RESPONSE-1];
					DUST.value = DUST.value/NUM_SAMP_RESPONSE; 
					DUST.value = (int32_t)DUST.value + DUST.offset;
					DUST.value = DUST.value/10;
				}
			}
			else if(DUST.flag == FLAG_ACTIVE)
			{
				if(UART2_sensor.check_sum == UART2_sensor.cmd[8])
				{
					DUST.value = 0;
					for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
					{
						DUST.value_samp[i] = DUST.value_samp[i+1];
						DUST.value += DUST.value_samp[i];
					}
					DUST.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART2_sensor.cmd[2]*256 + UART2_sensor.cmd[3] + (uint16_t)UART2_sensor.cmd[4]*256 + UART2_sensor.cmd[5] + (uint16_t)UART2_sensor.cmd[6]*256 + UART2_sensor.cmd[7];
					DUST.value += DUST.value_samp[NUM_SAMP_RESPONSE-1];
					DUST.value = DUST.value/NUM_SAMP_RESPONSE; 
					DUST.value = (int32_t)DUST.value + DUST.offset;
					DUST.value = DUST.value/10;
				}
				DUST.offset += (int32_t)DUST.base - DUST.value;
				write_FLASH();
				DUST.flag = FLAG_INACTIVE;
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
				if(DUST.flag == FLAG_INACTIVE)
				{
						DUST.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							DUST.value_samp[i] = DUST.value_samp[i+1];
							DUST.value += DUST.value_samp[i];
						}
						DUST.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3] + (uint16_t)UART3_sensor.cmd[4]*256 + UART3_sensor.cmd[5] + (uint16_t)UART3_sensor.cmd[6]*256 + UART3_sensor.cmd[7];
						DUST.value += DUST.value_samp[NUM_SAMP_RESPONSE-1];
						DUST.value = DUST.value/NUM_SAMP_RESPONSE; 
						DUST.value = (int32_t)DUST.value + DUST.offset;
						DUST.value = DUST.value/10;
				}
				else if(DUST.flag == FLAG_ACTIVE)
				{
					if(UART3_sensor.check_sum == UART3_sensor.cmd[8])
					{
						DUST.value = 0;
						for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
						{
							DUST.value_samp[i] = DUST.value_samp[i+1];
							DUST.value += DUST.value_samp[i];
						}
						DUST.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)UART3_sensor.cmd[2]*256 + UART3_sensor.cmd[3] + (uint16_t)UART3_sensor.cmd[4]*256 + UART3_sensor.cmd[5] + (uint16_t)UART3_sensor.cmd[6]*256 + UART3_sensor.cmd[7];
						DUST.value += DUST.value_samp[NUM_SAMP_RESPONSE-1];
						DUST.value = DUST.value/NUM_SAMP_RESPONSE; 
						DUST.value = (int32_t)DUST.value + DUST.offset;
						DUST.value = DUST.value/10;
					}
					DUST.offset += (int32_t)DUST.base - DUST.value;
					write_FLASH();
					DUST.flag = FLAG_INACTIVE;
			 }
		 }
	 }
 }
}

void Dust_DIGITAL_Read(uint8_t port)
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
			flag = FLAG_ACTIVE;
			stop_time = 0;
		}
	}
	if(flag == FLAG_ACTIVE)
	{
		flag = FLAG_INACTIVE;
		for(i = 0; i< 9; i++) DUST.data[i] = Receive_data(port, DUST.flag_start);
		DUST.check_sum = 0;
		for(i = 1; i < 8; i++) DUST.check_sum += DUST.data[i];
		DUST.check_sum = ~DUST.check_sum + 1;
		if(DUST.check_sum == DUST.data[8])
		{
			if(DUST.flag == FLAG_INACTIVE)
			{
				for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
				{
					DUST.value_samp[i] = DUST.value_samp[i+1];
					DUST.value += DUST.value_samp[i];
				}
				DUST.value_samp[NUM_SAMP_RESPONSE-1] = (uint16_t)DUST.data[2]*256 + DUST.data[3] + (uint16_t)DUST.data[4]*256 + DUST.data[5] + (uint16_t)DUST.data[6]*256 + DUST.data[7];
				DUST.value += DUST.value_samp[NUM_SAMP_RESPONSE-1];
				DUST.value = DUST.value/NUM_SAMP_RESPONSE;
				DUST.value	= (int32_t)DUST.value + DUST.offset;	
//				printf("Dust = %d ug\r\n",DUST.value);				
				DUST.value = DUST.value/10;
			}
			else if(DUST.flag == FLAG_ACTIVE)
			{
				DUST.flag = FLAG_INACTIVE;
				DUST.offset += (int32_t)DUST.base - DUST.value;
				write_FLASH();
			}
		}
	}
}

void get_Dust(uint16_t port)
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
	uartPC_putchar(PROPERTY_DUST);
	UART_rf.check_sum = CHECK_SUM0_DUST +  port;
	uartPC_putData(DUST.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}





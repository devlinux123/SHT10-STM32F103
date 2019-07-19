#include "MQ-Series.h"
#include "SHT1x.h"
#include "DS18B20.h"
#include "ADC.h"
#include "FLASH.h"
#include "UART.h"

data_mq_typedef CO =
{
	.flag = FLAG_INACTIVE,
	.flag_temp = FLAG_INACTIVE,
	.flag_humi = FLAG_INACTIVE,
	.Voltage = 0,
	.Ratio =0,
	.Rs = 0,
	.value = 0,
};
data_mq_typedef H2 =
{
	.flag = FLAG_INACTIVE,
	.flag_temp = FLAG_INACTIVE,
	.flag_humi = FLAG_INACTIVE,
	.Voltage = 0,
	.Ratio =0,
	.Rs = 0,
	.value = 0,
};
data_mq_typedef GAS =
{
	.flag = FLAG_INACTIVE,
	.flag_temp = FLAG_INACTIVE,
	.flag_humi = FLAG_INACTIVE,
	.Voltage = 0,
	.Ratio =0,
	.Rs = 0,
	.value = 0,
};


void Gas_Read(uint8_t port) //MQ-135
{
	uint8_t i;
	GAS.Voltage = 0;
	for(i = 0; i < NUM_SAMP_ADC; i++)
	{
		if(port == PORT8)
		{
			GAS.Voltage += (uint32_t)adc_value.port[0]*6600/4095;
		}
		else if(port == PORT9)
		{
			GAS.Voltage += (uint32_t)adc_value.port[1]*6600/4095;
		}
		else if(port == PORT10)
		{
			GAS.Voltage += (uint32_t)adc_value.port[2]*6600/4095;
		}
	}
	GAS.Voltage = GAS.Voltage/NUM_SAMP_ADC;
	GAS.Rs = (uint32_t)((5000-GAS.Voltage)*930/GAS.Voltage);
	if(GAS.flag == FLAG_INACTIVE & GAS.flag_humi == FLAG_ACTIVE & GAS.flag_temp == FLAG_ACTIVE)
	{
		GAS.Ratio = (double_t)GAS.Rs/GAS.Ro;
		GAS.ratio_humi =  1.055522496f - 0.000170537f*HUMI.RH[NUM_SAMP_RESPONSE];
		GAS.Ratio = GAS.Ratio*0.9446744f/GAS.ratio_humi;
		if(TEMP.Temp[NUM_SAMP_RESPONSE] < 250)
		{
			GAS.value = 0;
			for(i = 0; i < NUM_SAMP_RESPONSE*5 - 1; i++)
			{
				GAS.value_samp[i] = GAS.value_samp[i+1];
				GAS.value += GAS.value_samp[i];
			}
			GAS.ratio_temp = 0.00013409f*pow((TEMP.Temp[NUM_SAMP_RESPONSE]*0.18f + 32), 2) - 0.023334318f*(TEMP.Temp[NUM_SAMP_RESPONSE]*0.18f + 32) + 1.90922906f;
			GAS.Ratio = GAS.Ratio*GAS.ratio_temp;
			GAS.value_samp[NUM_SAMP_RESPONSE*5 - 1] = (uint16_t)(pow(10, 2.032321737f - (log10(GAS.Ratio)*2.467308167f)));
			GAS.value += GAS.value_samp[NUM_SAMP_RESPONSE*5 - 1];
			GAS.value = GAS.value/(NUM_SAMP_RESPONSE*5);
		}
		else if(TEMP.Temp[NUM_SAMP_RESPONSE] >= 250)
		{
			GAS.value = 0;
			for(i = 0; i < NUM_SAMP_RESPONSE*5 - 1; i++)
			{
				GAS.value_samp[i] = GAS.value_samp[i+1];
				GAS.value += GAS.value_samp[i];
			}
			GAS.ratio_temp = 1.016461124f - 0.001362084f*(TEMP.Temp[NUM_SAMP_RESPONSE]*0.18f + 32);
			GAS.Ratio = GAS.Ratio*GAS.ratio_temp;
			GAS.value_samp[NUM_SAMP_RESPONSE*5 - 1] = (uint16_t)(pow(10, 2.032321737f - (log10(GAS.Ratio)*2.467308167f)));
			GAS.value += GAS.value_samp[NUM_SAMP_RESPONSE*5 - 1];
			GAS.value = GAS.value/(NUM_SAMP_RESPONSE*5);
		}
		if(GAS.value < 20)
		{
			GAS.value = 1;
		}
	}
//	else if(GAS.flag == 1)
//	{
//		GAS.flag = 0;
//		GAS.Ro = GAS.Rs/3.63f;
//		write_FLASH();
//	}
	else if(GAS.flag == FLAG_ACTIVE)
	{
		GAS.flag = FLAG_INACTIVE;
		GAS.Ratio =(double_t)pow(10, 0.8237f - (log10(GAS.base)*0.4053f));
		GAS.Ro = GAS.Rs/GAS.Ratio;
		write_FLASH();
		printf("Base = %d\r\n", GAS.base);
	}
}

void CO_Read(uint8_t port) //MQ-7
{
	uint8_t i;
	CO.Voltage = 0;
	for(i = 0; i < NUM_SAMP_ADC; i++)
	{
		if(port == PORT8)
		{
			CO.Voltage += (uint32_t)adc_value.port[0]*6600/4095;
		}
		else if(port == PORT9)
		{
			CO.Voltage += (uint32_t)adc_value.port[1]*6600/4095;
		}
		else if(port == PORT10)
		{
			CO.Voltage += (uint32_t)adc_value.port[2]*6600/4095;
		}
	}
	CO.Voltage = CO.Voltage/NUM_SAMP_ADC;
	CO.Rs = (uint32_t)((5000-CO.Voltage)*963/CO.Voltage);
	if(CO.flag == FLAG_INACTIVE & CO.flag_humi == FLAG_ACTIVE & CO.flag_temp == FLAG_ACTIVE)
	{
		CO.Ratio = (double_t)CO.Rs/CO.Ro;
		CO.ratio_humi =  1.088341969f - 0.0002677029f*HUMI.RH[NUM_SAMP_RESPONSE];
		CO.Ratio = CO.Ratio*0.91433506f/CO.ratio_humi;
		if(TEMP.Temp[NUM_SAMP_RESPONSE] > -100)
		{
			CO.ratio_temp = 1.879249761f - 0.5234580647*log10(TEMP.Temp[NUM_SAMP_RESPONSE]*0.18 + 32);
		}
		CO.value = 0;
		for(i = 0; i < NUM_SAMP_RESPONSE*5 - 1; i++)
		{
			CO.value_samp[i] = CO.value_samp[i+1];
			CO.value += CO.value_samp[i];
		}
		CO.Ratio = CO.Ratio*CO.ratio_temp;			
		CO.value_samp[NUM_SAMP_RESPONSE*5 - 1] = (uint16_t)(pow(10, 2.008473294f - (log10(CO.Ratio)*1.513088213f)));
		CO.value += CO.value_samp[NUM_SAMP_RESPONSE*5 - 1];
		CO.value = CO.value/(NUM_SAMP_RESPONSE*5);
		if(CO.value < 20)
		{
			CO.value = 1;
		}
	}
//	else if(CO.flag == 1)
//	{
//		CO.flag = 0;
//		CO.Ro = CO.Rs/11.648f;
//		write_FLASH();
//	}
	else if(CO.flag == FLAG_ACTIVE)
	{
		CO.flag = FLAG_INACTIVE;
		CO.Ratio =(double_t)pow(10, 1.3274f - (log10(CO.base)*0.6609f));
		CO.Ro = CO.Rs/CO.Ratio;
		write_FLASH();
		printf("Base = %d\r\n", CO.base);
	}
}
void H2_Read(uint8_t port) //MQ-2
{
	uint8_t i;
	H2.Voltage = 0;
	for(i = 0; i < NUM_SAMP_ADC; i++)
	{
		if(port == PORT8)
		{
			H2.Voltage = (uint32_t)adc_value.port[0]*6600/4095;
		}
		else if(port == PORT9)
		{
			H2.Voltage = (uint32_t)adc_value.port[1]*6600/4095;
		}
		else if(port == PORT10)
		{
			H2.Voltage = (uint32_t)adc_value.port[2]*6600/4095;
		}
	}
	H2.Voltage = H2.Voltage/NUM_SAMP_ADC;
	H2.Rs = (uint32_t)((5000-H2.Voltage)*971/H2.Voltage);
	if(H2.flag == FLAG_INACTIVE & H2.flag_humi == FLAG_ACTIVE & H2.flag_temp == FLAG_ACTIVE)
	{
		H2.Ratio = (double_t)H2.Rs/H2.Ro;
		H2.ratio_humi = 1.4084f - 0.000568f*HUMI.RH[NUM_SAMP_RESPONSE];
		H2.Ratio = H2.Ratio*1.0392f/H2.ratio_humi;
		if(TEMP.Temp[NUM_SAMP_RESPONSE] > -100)
		{
			H2.ratio_temp = 1.58774759f*pow(2.718281828f,-0.00626410f*(TEMP.Temp[NUM_SAMP_RESPONSE]*0.18f + 32));
		}
		H2.value = 0;
		for(i = 0; i < NUM_SAMP_RESPONSE*5 - 1; i++)
		{
			H2.value_samp[i] = H2.value_samp[i+1];
			H2.value += H2.value_samp[i];
		}
		H2.Ratio = H2.Ratio*H2.ratio_temp;
		H2.value_samp[NUM_SAMP_RESPONSE*5 - 1] =(uint16_t)(pow(10, 3.009502169f - (log10(H2.Ratio)*2.065688907f)));
		H2.value += H2.value_samp[NUM_SAMP_RESPONSE*5 - 1];
		H2.value = H2.value/(NUM_SAMP_RESPONSE*5);
		if(H2.value < 20)
		{
			H2.value = 1;
		}

	}
//	else if(H2.flag == 1)
//	{
//		H2.flag = 0;
//		H2.Ro = H2.Rs/9.577f;
//		write_FLASH();
//	}
	else if(H2.flag == FLAG_ACTIVE)
	{
		H2.flag = FLAG_INACTIVE;
		H2.Ratio =(double_t)pow(10, 1.4569f - (log10(H2.base)*0.4841f));
		H2.Ro = H2.Rs/H2.Ratio;
		write_FLASH();
		printf("Base = %d\r\n", H2.base);
	}
	
}



void get_H2(uint16_t port)
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
	uartPC_putchar(PROPERTY_H2);
	UART_rf.check_sum = CHECK_SUM0_H2 +  port;
	uartPC_putData(H2.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}
void get_CO(uint16_t port)
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
	uartPC_putchar(PROPERTY_CO);
	UART_rf.check_sum = CHECK_SUM0_CO +  port;
	uartPC_putData(CO.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}
void get_GAS(uint16_t port)
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
	uartPC_putchar(PROPERTY_GAS);
	UART_rf.check_sum = CHECK_SUM0_GAS +  port;
	uartPC_putData(GAS.value, 2);
	uartPC_putchar(UART_rf.check_sum);
}



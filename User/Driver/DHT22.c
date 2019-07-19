#include "DHT22.h"
#include "TIMER.h"

dht22_typedef dht22;




void DHT22_Read(uint8_t port)
{
	uint8_t read_ready = 0;
	uint32_t i, j, counter = 0;
	
	for(i = 0; i < 16; i++)
	{
		dht22.buff_chekcsum[i] = 0;
		dht22.buff_rh[i] = 0;
		dht22.buff_temp[i] = 0;
	}
	dht22.rh_raw= 0;
	dht22.temp_raw = 0;
	
	config_SDO_Output(port);
	Reset_SDO(port);
	delay_ms(1);
	Set_SDO(port);
	config_SDO_Input(port);
	for(i = 0; i < 350; i++) //40~60us
	{
		if(State_SDO(port) == 0)
		{
			delay_us(150);
			for(i = 0; i < 200; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 1000;
					read_ready = 1;
				}
			}
		}
	}
	if(read_ready == 1)
	{
		read_ready = 0;
		for(j = 0; j < 16; j++)
		{
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 1)
				{
					i = 1000;
				}
			}
			TIM_SetCounter(TIM3, 0);
			while(State_SDO(port) == 1){}
			counter = TIM_GetCounter(TIM3);
			if(counter < 50) dht22.buff_rh[j] = 0;
			else dht22.buff_rh[j] = 1;
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 1000;
				}
			}
		}
		for(j = 0; j < 16; j++)
		{
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 1)
				{
					i = 1000;
				}
			}
			TIM_SetCounter(TIM3, 0);
			while(State_SDO(port) == 1){}
			counter = TIM_GetCounter(TIM3);
			if(counter < 50) dht22.buff_temp[j] = 0;
			else dht22.buff_temp[j] = 1;
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 1000;
				}
			}
		}
		for(j = 0; j < 8; j++)
		{
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 1)
				{
					i = 1000;
				}
			}
			TIM_SetCounter(TIM3, 0);
			while(State_SDO(port) == 1){}
			counter = TIM_GetCounter(TIM3);
			if(counter < 50) dht22.buff_chekcsum[j] = 0;
			else dht22.buff_chekcsum[j] = 1;
			for(i = 0;i < 500; i++)
			{
				if(State_SDO(port) == 0)
				{
					i = 1000;
				}
			}
		}
		dht22.check_sum = dht22.buff_chekcsum[7] + dht22.buff_chekcsum[6]*2 + dht22.buff_chekcsum[5]*4+ dht22.buff_chekcsum[4]*8 + dht22.buff_chekcsum[3]*16 + dht22.buff_chekcsum[2]*32 + dht22.buff_chekcsum[1]*64 +dht22.buff_chekcsum[0]*128;
		dht22.temp_raw = dht22.buff_temp[15] + dht22.buff_temp[14]*2 + dht22.buff_temp[13]*4 + dht22.buff_temp[12]*8 + dht22.buff_temp[11]*16 + dht22.buff_temp[10]*32 + dht22.buff_temp[9]*64 + dht22.buff_temp[8]*128 + dht22.buff_temp[7]*256 + dht22.buff_temp[6]*512 + dht22.buff_temp[5]*1024 + dht22.buff_temp[4]*2048 + dht22.buff_temp[3]*4096 + dht22.buff_temp[2]*8192 + dht22.buff_temp[1]*16384 + dht22.buff_temp[0]*32768;
		dht22.rh_raw = dht22.buff_rh[15] + dht22.buff_rh[14]*2 + dht22.buff_rh[13]*4 + dht22.buff_rh[12]*8 + dht22.buff_rh[11]*16 + dht22.buff_rh[10]*32 + dht22.buff_rh[9]*64 + dht22.buff_rh[8]*128 + dht22.buff_rh[7]*256 + dht22.buff_rh[6]*512 + dht22.buff_rh[5]*1024 + dht22.buff_rh[4]*2048 + dht22.buff_rh[3]*4096 + dht22.buff_rh[2]*8192 + dht22.buff_rh[1]*16384 + dht22.buff_rh[0]*32768;
		dht22.check = dht22.rh_raw/256 + dht22.rh_raw%256 + dht22.temp_raw/256 + dht22.temp_raw%256;
//		printf("Check = %d\r\n", check);
	}
}

#include "Loadcell.h"
#include "FLASH.h"



data_lc_typedef data_lc;


void HX711_Read(uint8_t port)
{
	int32_t data = 0;
	int32_t sum = 0;
	int16_t i, j;
	config_SDO_Input(port);
	for(j = 0; j < 20; j++)
	{
		data = 0;
		if(State_SDO(port) == 0)
		{
			for (i = 0; i< 24; i++)
			{
				Set_SCL(port);
				data = data << 1;
				if(State_SDO(port) == 1)
				{
					data++;
				}
				Reset_SCL(port);
			}
			Pulse_SCL(port, 1);
			if(data > 8388607)
			{
					data = data | 0xFF000000;
					sum += data;
			}
			else
			{
				sum += data;
			}
		}
	}
	sum =  sum  / 20;
	if(data_lc.flag == 0)
	{
		data_lc.lc_value = (sum - data_lc.lc_offset)*1000/data_lc.lc_ratio;
	}
	else if(data_lc.flag == 1)
	{
		data_lc.lc_offset = sum;
		write_FLASH();
		data_lc.flag = 0;
	}
	else if(data_lc.flag == 2)
	{
		data_lc.flag = 0;
		data_lc.lc_ratio = (sum - data_lc.lc_offset)*1000/data_lc.lc_base;
		write_FLASH();
	}
}



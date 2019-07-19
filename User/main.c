#include "main.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
PUTCHAR_PROTOTYPE
{
	 //Place your implementation of fputc here 
	 //e.g. write a character to the USART 
	USART_SendData(USART1, (uint8_t) ch); 
	 //Loop until the end of transmission 
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
	return ch;
}
 



int main(void)
{
	uint8_t led_run_state = 0, samp_response, count_property;
	uint32_t i, counter_blink_led;
	system_init();
	start_value();
	counter_blink_led = System_GetTick();
	while(1)
	{
		if((System_GetTick() - counter_blink_led) > 1000)
		{
			counter_blink_led = System_GetTick();
			if(led_run_state == 0)
			{
				led_run_state = 1;
				LED_Run_ON;
			}
			else if(led_run_state == 1)
			{
				led_run_state = 0;
				LED_Run_OFF;
			}
	  CO2.count++;
		}
		if(CO2.count > 60)
		{
			CO2.count = 60;
		}
		
		
		
		for(count_property = 0; count_property < 10; count_property++)
		{
			if(flash.property_buff[count_property] != 0)
			{
				switch(flash.property_buff[count_property])
				{
					case PROPERTY_HUMI: 
								if(flash.interface_buff[count_property] == INTF_DIGITAL) 
								{
									HUMI.Data_Temp = SHT1x_Read(ADDR_SHT10TEMP, count_property); // count_property dung de set port cho cam bien//
									HUMI.crc_temp  = HUMI.crc;
									HUMI.crc_check = SHT1x_CRC8_Check(HUMI.Data_Temp, 50331648, 49); // Chech data CRC HUMI
									if(HUMI.crc_check == HUMI.crc_temp && HUMI.Data_Temp >= 0)
									{
										HUMI.Data_RH   = SHT1x_Read(ADDR_SHT10RH, count_property);
										HUMI.crc_rh    = HUMI.crc;
										HUMI.crc_check = SHT1x_CRC8_Check(HUMI.Data_RH, 83886080, 49);
										if(HUMI.crc_check == HUMI.crc_rh & HUMI.Data_RH >= 0)
										{
											if(HUMI.flag == FLAG_INACTIVE)
											{
												HUMI.RH[NUM_SAMP_RESPONSE] = 0;
												for(samp_response = 0; samp_response < 	NUM_SAMP_RESPONSE - 1; samp_response++)
												{
													HUMI.RH[samp_response]      = HUMI.RH[samp_response+1];
													HUMI.RH[NUM_SAMP_RESPONSE] += HUMI.RH[samp_response];
												}
												HUMI.Temp      = SHT10_d1 + (SHT10_d2*HUMI.Data_Temp);
												HUMI.RH_Linear = SHT10_c1 + (SHT10_c2 * HUMI.Data_RH) + (SHT10_c3 * HUMI.Data_RH * HUMI.Data_RH / 1000000);
												HUMI.RH_True   = (HUMI.Temp - 25) * (SHT10_t1 + (SHT10_t2 * HUMI.Data_RH)) + HUMI.RH_Linear;
												if(HUMI.RH_True > 100)    HUMI.RH_True = 100;
												else if(HUMI.RH_True < 0) HUMI.RH_True = 0;
												HUMI.RH[NUM_SAMP_RESPONSE - 1] = HUMI.RH_True*10;
												HUMI.RH[NUM_SAMP_RESPONSE]    += HUMI.RH[NUM_SAMP_RESPONSE - 1];
												HUMI.RH[NUM_SAMP_RESPONSE]     = HUMI.RH[NUM_SAMP_RESPONSE]/NUM_SAMP_RESPONSE;
												HUMI.RH[NUM_SAMP_RESPONSE]     = HUMI.RH[NUM_SAMP_RESPONSE] + HUMI.Offset_RH;
//												printf("Offset = %d\r\n",data_rh.Offset_RH);
												printf("HUMI_Value = %.1f %%\r\n",(double)HUMI.RH[NUM_SAMP_RESPONSE]/10);
												
												//active read mq sensor  
												CO.flag_humi = FLAG_ACTIVE; // Cong thuc tinh co lien quan toi do am cua HUMI
												H2.flag_humi = FLAG_ACTIVE;
												GAS.flag_humi = FLAG_ACTIVE;
												get_RH(count_property);
												delay_ms(500);
												counter_blink_led += 1000;
											}
											else if(HUMI.flag == FLAG_ACTIVE)
											{
												if(HUMI.crc_check == HUMI.crc_rh & HUMI.Data_RH >= 0)
												{
													HUMI.RH[NUM_SAMP_RESPONSE] = 0;
													for(samp_response = 0; samp_response < 	NUM_SAMP_RESPONSE - 1; samp_response++)
													{
														HUMI.RH[samp_response] = HUMI.RH[samp_response+1];
														HUMI.RH[NUM_SAMP_RESPONSE] += HUMI.RH[samp_response];
													}
													HUMI.Temp = SHT10_d1 + (SHT10_d2*HUMI.Data_Temp);
													HUMI.RH_Linear = SHT10_c1 + (SHT10_c2 * HUMI.Data_RH) + (SHT10_c3 * HUMI.Data_RH * HUMI.Data_RH / 1000000);
													HUMI.RH_True = (HUMI.Temp - 25) * (SHT10_t1 + (SHT10_t2 * HUMI.Data_RH)) + HUMI.RH_Linear;
													if(HUMI.RH_True > 100) HUMI.RH_True = 100;
													else if(HUMI.RH_True < 0) HUMI.RH_True = 0;
													HUMI.RH[NUM_SAMP_RESPONSE - 1] = HUMI.RH_True*10;
													HUMI.RH[NUM_SAMP_RESPONSE] += HUMI.RH[NUM_SAMP_RESPONSE - 1];
													HUMI.RH[NUM_SAMP_RESPONSE] = HUMI.RH[NUM_SAMP_RESPONSE]/NUM_SAMP_RESPONSE;
													HUMI.RH[NUM_SAMP_RESPONSE] = HUMI.RH[NUM_SAMP_RESPONSE] + HUMI.Offset_RH;
													
//													printf("HUMI_Value = %.1f\r\n",(double)data_rh.RH[NUM_SAMP_RESPONSE]/10);
													
													//active read mq sensor
													CO.flag_humi = FLAG_ACTIVE;
													H2.flag_humi = FLAG_ACTIVE;
													GAS.flag_humi = FLAG_ACTIVE;
													get_RH(count_property);
													delay_ms(500);
													counter_blink_led += 1000;
												}
												HUMI.flag = FLAG_INACTIVE;
												HUMI.Offset_RH += HUMI.Base_RH - (int16_t)HUMI.RH[NUM_SAMP_RESPONSE];
												write_FLASH();
											}
										}
										else
										{
											CO.flag_humi  = FLAG_INACTIVE;
											H2.flag_humi  = FLAG_INACTIVE;
											GAS.flag_humi = FLAG_INACTIVE;
										}
										counter_blink_led += 1000;
									}
									else
									{
										CO.flag_humi   = FLAG_INACTIVE;
										H2.flag_humi   = FLAG_INACTIVE;
										GAS.flag_humi  = FLAG_INACTIVE; 
										counter_blink_led += 1000;
									}
								}
								else
								{
									CO.flag_humi   = FLAG_INACTIVE;
									H2.flag_humi   = FLAG_INACTIVE;
									GAS.flag_humi  = FLAG_INACTIVE;
									flash.interface_buff[count_property] = INTF_DIGITAL; 
									/*Gan gia tri INTF_DIGITAL = 1 vao flash.interface_buff[0]--> countproperty = 0 */
									// cai dat ngo vao cua Port la digital
									write_FLASH();                                       
									// Write gia tri flash.interface_buff //
									printf("Int humi\r\n");
									config_port(count_property);// config_port(count_property = 0) --> config(Port1)
								}
								break;
						case PROPERTY_TEMP:
								if(flash.interface_buff[count_property] == INTF_DIGITAL)
								{
									TEMP.check_data = DS18B20_Read(count_property);
									if(TEMP.check_data == 1)
									{
										if(TEMP.flag == FLAG_INACTIVE)
										{
											TEMP.Temp[NUM_SAMP_RESPONSE] = 0;
											for(samp_response = 0; samp_response < NUM_SAMP_RESPONSE-1; samp_response++)
											{
												TEMP.Temp[samp_response] = TEMP.Temp[samp_response+1];
												TEMP.Temp[NUM_SAMP_RESPONSE] += TEMP.Temp[samp_response];
											}
											TEMP.Temp[NUM_SAMP_RESPONSE-1] = (int16_t)TEMP.Data_Temp[1] << 8 | TEMP.Data_Temp[0];
											TEMP.Temp[NUM_SAMP_RESPONSE-1] = TEMP.Temp[NUM_SAMP_RESPONSE-1]*10/16;
											TEMP.Temp[NUM_SAMP_RESPONSE] += TEMP.Temp[NUM_SAMP_RESPONSE-1];
											TEMP.Temp[NUM_SAMP_RESPONSE] = TEMP.Temp[NUM_SAMP_RESPONSE]/NUM_SAMP_RESPONSE;
											TEMP.Temp[NUM_SAMP_RESPONSE] = TEMP.Temp[NUM_SAMP_RESPONSE] + TEMP.Offset_Temp;
//											printf("Temp_DS18B20 = %.1f °C\r\n",(double)TEMP.Temp[NUM_SAMP_RESPONSE]/10);
											//active read mq sensor
											CO.flag_temp = FLAG_ACTIVE;
											H2.flag_temp = FLAG_ACTIVE;
											GAS.flag_temp = FLAG_ACTIVE;
											
											get_Temp(count_property);
											delay_ms(500);
											counter_blink_led += 1000;
										
										}
										else if(TEMP.flag == FLAG_ACTIVE)
										{
											if(TEMP.check_data == 1)
											{
												TEMP.Temp[NUM_SAMP_RESPONSE] = 0;
												for(samp_response = 0; samp_response < NUM_SAMP_RESPONSE-1; samp_response++)
												{
													TEMP.Temp[samp_response] = TEMP.Temp[samp_response+1];
													TEMP.Temp[NUM_SAMP_RESPONSE] += TEMP.Temp[samp_response];
												}
												TEMP.Temp[NUM_SAMP_RESPONSE-1] = (int16_t)TEMP.Data_Temp[1] << 8 | TEMP.Data_Temp[0];
												TEMP.Temp[NUM_SAMP_RESPONSE-1] = TEMP.Temp[NUM_SAMP_RESPONSE-1]*10/16;
												TEMP.Temp[NUM_SAMP_RESPONSE] += TEMP.Temp[NUM_SAMP_RESPONSE-1];
												TEMP.Temp[NUM_SAMP_RESPONSE] = TEMP.Temp[NUM_SAMP_RESPONSE]/NUM_SAMP_RESPONSE;
												TEMP.Temp[NUM_SAMP_RESPONSE] = TEMP.Temp[NUM_SAMP_RESPONSE] + TEMP.Offset_Temp;
												//active read mq sensor
												CO.flag_temp = FLAG_ACTIVE;
												H2.flag_temp = FLAG_ACTIVE;
												GAS.flag_temp = FLAG_ACTIVE;
												
												get_Temp(count_property);
												delay_ms(500);
												counter_blink_led += 1000;
											}
											TEMP.flag = FLAG_INACTIVE;
											TEMP.Offset_Temp += TEMP.Base_Temp - TEMP.Temp[NUM_SAMP_RESPONSE];
											write_FLASH();
										}
									}
									else
									{
										CO.flag_temp = FLAG_INACTIVE;
										H2.flag_temp = FLAG_INACTIVE;
										GAS.flag_temp = FLAG_INACTIVE;
									}
									counter_blink_led += 1000;
								}
								else
								{
									CO.flag_temp = FLAG_INACTIVE;
									H2.flag_temp = FLAG_INACTIVE;
									GAS.flag_temp = FLAG_INACTIVE;
									flash.interface_buff[count_property] = INTF_DIGITAL;
									write_FLASH();
									printf("Int temp\r\n");
									config_port(count_property);
								}
								break; 
					case PROPERTY_DUST:
								if(count_property == PORT2 || count_property == PORT3)
								{
									if(flash.interface_buff[count_property] == INTF_UART)
									{
										Dust_UART_Read(count_property);
//										printf("Dust = %.2f mg\r\n", (double)DUST.value/100);
										get_Dust(count_property);
										delay_ms(500);
										counter_blink_led += 1000;
									}
									else
									{
										flash.interface_buff[count_property] = INTF_UART;
										write_FLASH();
										printf("Int dust\r\n");
										config_port(count_property);
									}
								}
								else
								{
									if(flash.interface_buff[count_property] == INTF_DIGITAL)
									{
										Dust_DIGITAL_Read(count_property);
//										printf("Dust = %.2f ug\r\n", (double)DUST.value/100);
										get_Dust(count_property);
										delay_ms(500);
										counter_blink_led += 1000;
									}
									else
									{
										flash.interface_buff[count_property] = INTF_DIGITAL;
										write_FLASH();
										printf("Int dust\r\n");
										config_port(count_property);
									}
								}
								break;
					case PROPERTY_CO2:
								if(count_property == PORT2 || count_property == PORT3)
								{
									if(flash.interface_buff[count_property] == INTF_UART)
									{
										if(CO2.count == 60)
										{	
											WinSen_UART_Read(count_property, &CO2);
											get_WINSEN(count_property, PROPERTY_CO2, CHECK_SUM0_CO2, CO2.value);
//											printf("CO2 = %d ppm\r\n", CO2.value);
											delay_ms(500);
											counter_blink_led += 1000;
										}
										else if(CO2.count < 60)
										{
											CO2.value = 1;
											get_WINSEN(count_property, PROPERTY_CO2, CHECK_SUM0_CO2, CO2.value);
//											printf("CO2 = %d ppm\r\n", CO2.value);
											delay_ms(500);
											counter_blink_led += 1000;
										}
									}
									else
									{
										flash.interface_buff[count_property] = INTF_UART;
										write_FLASH();
										printf("Int co2\r\n");
										config_port(count_property);
									}
								}
								else
								{
									if(flash.interface_buff[count_property] == INTF_DIGITAL)
									{
										if(CO2.count == 60)
										{	
											WinSen_DIGITAL_Read(count_property, &CO2);
											get_WINSEN(count_property, PROPERTY_CO2, CHECK_SUM0_CO2, CO2.value);
//											printf("CO2 = %d ppm\r\n", CO2.value);
											delay_ms(500);
											counter_blink_led += 1000;
										}
										else if(CO2.count < 60)
										{
											CO2.value = 1;
											get_WINSEN(count_property, PROPERTY_CO2, CHECK_SUM0_CO2, CO2.value);
//											printf("CO2 = %d ppm\r\n", CO2.value);
											delay_ms(500);
											counter_blink_led += 1000;
										}
									}
									else
									{
										flash.interface_buff[count_property] = INTF_DIGITAL;
										write_FLASH();
										printf("Int co2\r\n");
										config_port(count_property);
									}
								}
								break;
					case PROPERTY_GAS:
								if(flash.interface_buff[count_property] == INTF_ADC)
								{
									Gas_Read(count_property);
//									printf("Gas = %d ppm\r\n", GAS.value);
									get_GAS(count_property);
									delay_ms(500);
									counter_blink_led += 1000;
								}
								else
								{
									flash.interface_buff[count_property] = INTF_ADC;
									write_FLASH();
									printf("Int gas\r\n");
									config_port(count_property);
								}
								break;
					case PROPERTY_CO:
								if(flash.interface_buff[count_property] == INTF_ADC)
								{
									CO_Read(count_property);
//									printf("CO = %d ppm\r\n", CO.value);
									get_CO(count_property);
									delay_ms(500);
									counter_blink_led += 1000;
								}
								else
								{
									flash.interface_buff[count_property] = INTF_ADC;
									write_FLASH();
									printf("Int co\r\n");
									config_port(count_property);
								}
								break;
					case PROPERTY_H2:
								if(flash.interface_buff[count_property] == INTF_ADC)
								{
									H2_Read(count_property);
//									printf("H2 = %d ppm\r\n", H2.value);
									get_H2(count_property);
									delay_ms(500);
									counter_blink_led += 1000;
								}
								else
								{
									flash.interface_buff[count_property] = INTF_ADC;
									write_FLASH();
									printf("Int h2\r\n");
									config_port(count_property);
								}
								break;
					case PROPERTY_PRESSURE:
								if(flash.interface_buff[count_property] == INTF_DIGITAL)
								{
									BMP180_ReadCalib(BMP180_MODULE_ADDR,BMP180_CALIB, count_property);
									if(PRESSURE.flag == FLAG_INACTIVE)
									{
										PRESSURE.value = 0;
										for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
										{
											PRESSURE.value_samp[i] = PRESSURE.value_samp[i+1];
											PRESSURE.value += PRESSURE.value_samp[i];
										}
										PRESSURE.temp = BMP180_ReadTemp(count_property);
										PRESSURE.value_samp[NUM_SAMP_RESPONSE-1] = BMP180_ReadPressure(count_property);
										PRESSURE.value +=PRESSURE.value_samp[NUM_SAMP_RESPONSE-1];
										PRESSURE.value = (PRESSURE.value/NUM_SAMP_RESPONSE)/10 + PRESSURE.Offset_value;
//										data_pressure.altitude = 44330*(1 - pow((data_pressure.value/10132.5f),0.1902949572f));
//										printf("Temp = %d °C\r\n",data_pressure.temp);
//										printf("Pressure = %.1f hPa\r\n",(double)PRESSURE.value/10);
//										printf("Altitude = %d m\r\n",data_pressure.altitude);
										get_Pressure(count_property);
										delay_ms(300);
										counter_blink_led += 1000;
									}
									else if(PRESSURE.flag == FLAG_ACTIVE)
									{
										PRESSURE.value = 0;
										for(i = 0; i < NUM_SAMP_RESPONSE-1; i++)
										{
											PRESSURE.value_samp[i] = PRESSURE.value_samp[i+1];
											PRESSURE.value += PRESSURE.value_samp[i];
										}
										PRESSURE.temp = BMP180_ReadTemp(count_property);
										PRESSURE.value_samp[NUM_SAMP_RESPONSE-1] = BMP180_ReadPressure(count_property);
										PRESSURE.value +=PRESSURE.value_samp[NUM_SAMP_RESPONSE-1];
										PRESSURE.value = (PRESSURE.value/NUM_SAMP_RESPONSE)/100 + PRESSURE.Offset_value;
//										data_pressure.altitude = 44330*(1 - pow((data_pressure.value/1013.25f),0.1902949572f));
//										printf("Temp = %.1f °C\r\n",(double)data_pressure.temp/10);
//										printf("Pressure = %.1f hPa\r\n",(double)data_pressure.value/10);
//										printf("Altitude = %d m\r\n",data_pressure.altitude);
										get_Pressure(count_property);
										delay_ms(500);
										counter_blink_led += 1000;
										PRESSURE.flag = FLAG_INACTIVE;
										PRESSURE.Offset_value += (int32_t)PRESSURE.Base_value - PRESSURE.value;
										write_FLASH();
									}
								}
								else
								{
									flash.interface_buff[count_property] = INTF_DIGITAL;
									write_FLASH();
									printf("Int pressure\r\n");
									config_port(count_property);
								}
								break;
					case PROPERTY_WIND_SPEED:
								if(flash.interface_buff[count_property] == INTF_DIGITAL)
								{
									WIND_SPEED_Read(count_property);
									get_Wind_Speed(count_property);
//									printf("Speed = %.1f m/s\r\n", (double)data_wind_speed.value/10);
									delay_ms(300);
									counter_blink_led += 1000;
								}
								else
								{
									flash.interface_buff[count_property] = INTF_DIGITAL;
									write_FLASH();
									printf("Int wind speed\r\n");
									config_port(count_property);
								}
								break;
					case PROPERTY_WIND_DIRECT:
								if(flash.interface_buff[count_property] == INTF_DIGITAL)
								{
									WIND_DIRECT_Read(count_property);
//									printf("Direct = %d\r\n", data_wind_direct.degree);
									get_Wind_Direct(count_property);
									delay_ms(300);
									counter_blink_led += 1000;
								}
								else
								{
									flash.interface_buff[count_property] = INTF_DIGITAL;
									write_FLASH();
									printf("Int wind direct\r\n");
									config_port(count_property);
								}
								break;
					default: break;
				}
			}//============//
		}
		if(UART_rf.flag == FLAG_ACTIVE)
		{
			UART_rf.flag = FLAG_INACTIVE;
			analyze_Packet(UART_rf.cmd, UART_rf.len);
			if(PACKET.start_code != START_FAILE)
			{
				switch(PACKET.value[0])
				{
					case INFORMATION_DUST: 				DUST.base = (uint16_t)(PACKET.value[1]*256 + PACKET.value[2]);
																				DUST.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_MULTISENSOR:	if(PACKET.value[1] > 0 & PACKET.value[1] < 11) flash.property_buff[PACKET.value[1] - 1] = PACKET.value[2];
																				write_FLASH();
																				break;
					case INFORMATION_CO2:					CO2.base = (uint16_t)PACKET.value[1]*256 + PACKET.value[2];
																				if(CO2.base <= 5000 & CO2.base > 0)
																				{
																					CO2.flag = FLAG_ACTIVE;
																				}
																				break;
					case INFORMATION_H2:					H2.base = (uint16_t)PACKET.value[1]*256 + PACKET.value[2];
																				if(H2.base <= 10000 & H2.base >= 5) H2.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_CO:					CO.base = (uint16_t)PACKET.value[1]*256 + PACKET.value[2];
																				if(CO.base <= 2000 & CO.base >= 5) CO.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_GAS:					GAS.base = (uint16_t)PACKET.value[1]*256 + PACKET.value[2];
																				if(GAS.base <= 300 & GAS.base >= 5) GAS.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_HUMI:  			HUMI.Base_RH = (uint16_t)(PACKET.value[1]*256 + PACKET.value[2]);
																				HUMI.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_TEMP:  			TEMP.Base_Temp = (int16_t)(PACKET.value[1]*256 + PACKET.value[2]);
																				TEMP.flag = FLAG_ACTIVE;
																				break;
					case INFORMATION_PRESSURE: 		PRESSURE.Base_value = (uint16_t)(PACKET.value[1]*256 + PACKET.value[2]);
																				PRESSURE.flag = FLAG_ACTIVE;
																				break;
					default: break;
				}
			}
		}
	}

}
void start_value(void)
{
	uint8_t i;
	for(i = 0; i < 100; i++)
	{
		UART_rf.cmd[i] = 0;
		UART2_sensor.cmd[i] = 0;
		UART3_sensor.cmd[i] = 0;
	}
	for(i = 0; i < NUM_SAMP_RESPONSE + 1; i++)
	{
		TEMP.Temp[i] = 0;
		HUMI.RH[i] = 0;
	}
	for(i =0 ; i < 9; i++)
	{
		TEMP.Data_Temp[i] = 0;
	}
	delay_us(100);
}

void system_init(void)
{
	uint8_t counter_interface;
	GPIO_init();
	UART_init();
	TIMER_init();
	Systick_init();
	FLASH_update_information();
	for(counter_interface = 0; counter_interface < 10; counter_interface++)
	{
		if(flash.interface_buff[9 - counter_interface] != 0) config_port(9 - counter_interface);
	}
}



#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
	while (1)
	{
	}
}
#endif



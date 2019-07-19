#include "GPIO.h"
#include "FLASH.h"
#include "ADC.h"
#include "UART.h"

GPIO_InitTypeDef		     GPIO_InitStructure;
USART_InitTypeDef 	     USART_InitStructure;
NVIC_InitTypeDef		     NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
DMA_InitTypeDef 		     DMA_InitStructure;
ADC_InitTypeDef 		     ADC_InitStructure;




uint8_t adc_config_flag = FLAG_ACTIVE;

void GPIO_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED_Run_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_Run_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = UART_RF_Tx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART_RF_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = UART_RF_Rx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART_RF_GPIO, &GPIO_InitStructure);
	

}

void config_port(uint8_t port)
{	
	if(flash.interface_buff[port] == INTF_DIGITAL) 
	{
		config_DIGITAL(port);
	}
	else if(flash.interface_buff[port] == INTF_ADC)
	{
		if(adc_config_flag == FLAG_ACTIVE)
		{
			adc_config_flag = FLAG_INACTIVE;
			config_ADC(port);
		}
	}
	else if(flash.interface_buff[port] == INTF_UART)
	{
		config_UART(port, 9600);
	}
}

void config_DIGITAL(uint8_t port)
{
	switch(port)
	{
		case PORT1: // GPIOB
			          GPIO_InitStructure.GPIO_Pin = PORT1_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT1_GPIO, &GPIO_InitStructure);// Khai bao GPIOB pin7 la Output
								GPIO_WriteBit(PORT1_GPIO, PORT1_PIN1, Bit_SET); 
		
								GPIO_InitStructure.GPIO_Pin = PORT1_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT1_GPIO, &GPIO_InitStructure);// Khai bao GPIOB pin6 la Output
								GPIO_WriteBit(PORT1_GPIO, PORT1_PIN2, Bit_SET);
		
								GPIO_InitStructure.GPIO_Pin = PORT1_PIN3;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT1_GPIO, &GPIO_InitStructure);// Khai bao GPIOB pin5 la Input
								GPIO_WriteBit(PORT1_GPIO, PORT1_PIN3, Bit_SET);
		
								break;
		case PORT2: // GPIOA
		            GPIO_InitStructure.GPIO_Pin = PORT2_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT2_GPIO, &GPIO_InitStructure);// config GPIOA pin2 ->Output
								GPIO_WriteBit(PORT2_GPIO, PORT2_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT2_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT2_GPIO, &GPIO_InitStructure);// Config GPIOA pin3 ->Output
								GPIO_WriteBit(PORT2_GPIO, PORT2_PIN2, Bit_RESET);
								
								break;
		case PORT3: // GPIOB
			          GPIO_InitStructure.GPIO_Pin = PORT3_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT3_GPIO, &GPIO_InitStructure);//Config GPIOB pin10 ->Output
								GPIO_WriteBit(PORT3_GPIO, PORT3_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT2_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT3_GPIO, &GPIO_InitStructure);// Config GPIOB pin3 -> Output
								GPIO_WriteBit(PORT3_GPIO, PORT3_PIN2, Bit_RESET);
								
								break;
		case PORT4: // GPIOB
			          GPIO_InitStructure.GPIO_Pin = PORT4_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT4_GPIO, &GPIO_InitStructure);//GPIOB pin15->Out
								GPIO_WriteBit(PORT4_GPIO, PORT4_PIN1, Bit_SET);

								GPIO_InitStructure.GPIO_Pin = PORT4_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT4_GPIO, &GPIO_InitStructure);//GPIOB pin14->Out
								GPIO_WriteBit(PORT4_GPIO, PORT4_PIN2, Bit_SET);

								GPIO_InitStructure.GPIO_Pin = PORT4_PIN3;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT4_GPIO, &GPIO_InitStructure);//GPIOB pin3 ->Input
								GPIO_WriteBit(PORT4_GPIO, PORT4_PIN3, Bit_SET);

								break;
		case PORT5: // Port 5A -> GPIOA, Port 5D -> GPIOB
		            GPIO_InitStructure.GPIO_Pin = PORT5_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT5_A_GPIO, &GPIO_InitStructure);//GPIOA pin0 ->output
								GPIO_WriteBit(PORT5_A_GPIO, PORT5_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT5_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT5_D_GPIO, &GPIO_InitStructure);//GPIOB pin8 ->OUT
								GPIO_WriteBit(PORT5_D_GPIO, PORT5_PIN2, Bit_RESET);
								
								break;
		case PORT6: //GPIOA
								GPIO_InitStructure.GPIO_Pin = PORT6_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT6_GPIO, &GPIO_InitStructure);//GPIOA pin1 ->Out
								GPIO_WriteBit(PORT6_GPIO, PORT6_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT6_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT6_GPIO, &GPIO_InitStructure);//GPIOA pin12 ->OUT
								GPIO_WriteBit(PORT6_GPIO, PORT6_PIN2, Bit_RESET);
								
								break;
		case PORT7: //GPIOA
								GPIO_InitStructure.GPIO_Pin = PORT7_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT7_GPIO, &GPIO_InitStructure);//GPIOA pin5->OUT
								GPIO_WriteBit(PORT7_GPIO, PORT7_PIN1, Bit_SET);

								GPIO_InitStructure.GPIO_Pin = PORT7_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT7_GPIO, &GPIO_InitStructure);//GPIOA pin6->OUT
								GPIO_WriteBit(PORT7_GPIO, PORT7_PIN2, Bit_SET);

								GPIO_InitStructure.GPIO_Pin = PORT7_PIN3;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT7_GPIO, &GPIO_InitStructure);//GPIOA pin7->INPUT
								GPIO_WriteBit(PORT7_GPIO, PORT7_PIN3, Bit_SET);

								break;
		case PORT8: //GPIOA
								GPIO_InitStructure.GPIO_Pin = PORT8_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);// GPIOA pin4->OUT
								GPIO_WriteBit(PORT8_GPIO, PORT8_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT8_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);// GPIOA pin11->OUT
								GPIO_WriteBit(PORT8_GPIO, PORT8_PIN2, Bit_RESET);
								
								break;
		case PORT9: // Port 9D-> GPIOA, Port 9A->GPIOB
			          GPIO_InitStructure.GPIO_Pin = PORT9_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT9_A_GPIO, &GPIO_InitStructure);// GPIOB pin0->OUT
								GPIO_WriteBit(PORT9_A_GPIO, PORT9_PIN1, Bit_SET);
		
								GPIO_InitStructure.GPIO_Pin = PORT9_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT9_D_GPIO, &GPIO_InitStructure);//GPIOA pin8->OUT
								GPIO_WriteBit(PORT9_D_GPIO, PORT9_PIN2, Bit_SET);
								
								break;
		case PORT10: //GPIOB
           			GPIO_InitStructure.GPIO_Pin = PORT10_PIN1;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT10_GPIO, &GPIO_InitStructure);// GPIOB pin1->OUT
								GPIO_WriteBit(PORT10_GPIO, PORT10_PIN1, Bit_RESET);
		
								GPIO_InitStructure.GPIO_Pin = PORT10_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT10_GPIO, &GPIO_InitStructure);// GPIOB pin12->OUT
								GPIO_WriteBit(PORT10_GPIO, PORT10_PIN2, Bit_RESET);
								
								break;
		default: break;
	}
}

void config_SDO_Output(uint8_t port)
{
	switch(port)
	{
		case PORT1: // GPIOB pin6
			          GPIO_InitStructure.GPIO_Pin = PORT1_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT1_GPIO, &GPIO_InitStructure);
								break;
		case PORT2: // GPIOA pin3
			          GPIO_InitStructure.GPIO_Pin = PORT2_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT2_GPIO, &GPIO_InitStructure);
								break;
		case PORT3: // GPIOB pin11
			          GPIO_InitStructure.GPIO_Pin = PORT3_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT3_GPIO, &GPIO_InitStructure);
								break;
		case PORT4: // GPIOB pin14
			          GPIO_InitStructure.GPIO_Pin = PORT4_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT4_GPIO, &GPIO_InitStructure);
								break;
		case PORT5: // GPIOB pin8
			          GPIO_InitStructure.GPIO_Pin = PORT5_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT5_D_GPIO, &GPIO_InitStructure);
								break;
		case PORT6: //GPIOA pin12
			          GPIO_InitStructure.GPIO_Pin = PORT6_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT6_GPIO, &GPIO_InitStructure);
								break;
		case PORT7: //GPIOA pin6
			          GPIO_InitStructure.GPIO_Pin = PORT7_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT7_GPIO, &GPIO_InitStructure);
								break;
	  case PORT8: //GPIOA pin11
			          GPIO_InitStructure.GPIO_Pin = PORT8_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);
								break;
		case PORT9: //GPIOB pin8
			          GPIO_InitStructure.GPIO_Pin = PORT9_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT9_A_GPIO, &GPIO_InitStructure);
								break;
		case PORT10: //GPIOB pin12
			          GPIO_InitStructure.GPIO_Pin = PORT10_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
								GPIO_Init(PORT10_GPIO, &GPIO_InitStructure);
								break;
	}
}
void config_SDO_Input(uint8_t port)
{
	switch(port)
	{
		case PORT1: //GPIOB pin6
			          GPIO_InitStructure.GPIO_Pin = PORT1_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT1_GPIO, &GPIO_InitStructure);
								break;
		case PORT2: // GPIOA pin3
			          GPIO_InitStructure.GPIO_Pin = PORT2_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT2_GPIO, &GPIO_InitStructure);
								break;
		case PORT3: 
			          GPIO_InitStructure.GPIO_Pin = PORT3_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT3_GPIO, &GPIO_InitStructure);
								break;
		case PORT4: // GPIOB pin11
			          GPIO_InitStructure.GPIO_Pin = PORT4_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT4_GPIO, &GPIO_InitStructure);
								break;
		case PORT5: // GPIOB pin8
			          GPIO_InitStructure.GPIO_Pin = PORT5_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT5_D_GPIO, &GPIO_InitStructure);
								break;
		case PORT6:  //GPIOA pin12
			          GPIO_InitStructure.GPIO_Pin = PORT6_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT6_GPIO, &GPIO_InitStructure);
								break;
		case PORT7: //GPIOA pin11
			          GPIO_InitStructure.GPIO_Pin = PORT7_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT7_GPIO, &GPIO_InitStructure);
								break;
	  case PORT8: //GPIOA pin11
			          GPIO_InitStructure.GPIO_Pin = PORT8_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT8_GPIO, &GPIO_InitStructure);
								break;
		case PORT9: //GPIOB pin8
			          GPIO_InitStructure.GPIO_Pin = PORT9_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT9_A_GPIO, &GPIO_InitStructure);
								break;
		case PORT10: //GPIOB pin12
			          GPIO_InitStructure.GPIO_Pin = PORT10_PIN2;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(PORT10_GPIO, &GPIO_InitStructure);
								break;
	}
}

void Set_SCL(uint8_t port)
{
	     if(port == PORT1)  GPIO_WriteBit(PORT1_GPIO,   PORT1_PIN1,  Bit_SET); //GPIOB         pin 7
	else if(port == PORT2)  GPIO_WriteBit(PORT2_GPIO,   PORT2_PIN1,  Bit_SET); //GPIOA         pin 2
	else if(port == PORT3)  GPIO_WriteBit(PORT3_GPIO,   PORT3_PIN1,  Bit_SET); //GPIOB         pin 10
	else if(port == PORT4)  GPIO_WriteBit(PORT4_GPIO,   PORT4_PIN1,  Bit_SET); //GPIOB         pin 15
	else if(port == PORT5)  GPIO_WriteBit(PORT5_A_GPIO, PORT5_PIN1,  Bit_SET); //GPIOA PORT5_A pin 0
	else if(port == PORT6)  GPIO_WriteBit(PORT6_GPIO,   PORT6_PIN1,  Bit_SET); //GPIOA         pin 1
	else if(port == PORT7)  GPIO_WriteBit(PORT7_GPIO,   PORT7_PIN1,  Bit_SET); //GPIOA         pin 5
	else if(port == PORT8)  GPIO_WriteBit(PORT8_GPIO,   PORT8_PIN1,  Bit_SET); //GPIOA         pin 4
	else if(port == PORT9)  GPIO_WriteBit(PORT9_D_GPIO, PORT9_PIN1,  Bit_SET); //GPIOA PORT9_D pin 0
	else if(port == PORT10) GPIO_WriteBit(PORT10_GPIO,  PORT10_PIN1, Bit_SET); //GPIOB         pin 1
}

void Reset_SCL(uint8_t port)
{ 
	     if(port == PORT1) GPIO_WriteBit(PORT1_GPIO,   PORT1_PIN1,  Bit_RESET); //GPIOB        pin 7
	else if(port == PORT2) GPIO_WriteBit(PORT2_GPIO,   PORT2_PIN1,  Bit_RESET); //GPIOA        pin 2
	else if(port == PORT3) GPIO_WriteBit(PORT3_GPIO,   PORT3_PIN1,  Bit_RESET); //GPIOB        pin 10
	else if(port == PORT4) GPIO_WriteBit(PORT4_GPIO,   PORT4_PIN1,  Bit_RESET); //GPIOB        pin 15
	else if(port == PORT5) GPIO_WriteBit(PORT5_A_GPIO, PORT5_PIN1,  Bit_RESET); //GPIOA        pin 0
	else if(port == PORT6) GPIO_WriteBit(PORT6_GPIO,   PORT6_PIN1,  Bit_RESET); //GPIOA        pin 1
	else if(port == PORT7) GPIO_WriteBit(PORT7_GPIO,   PORT7_PIN1,  Bit_RESET); //GPIOA        pin 5
	else if(port == PORT8) GPIO_WriteBit(PORT8_GPIO,   PORT8_PIN1,  Bit_RESET); //GPIOA        pin 4
	else if(port == PORT9) GPIO_WriteBit(PORT9_D_GPIO, PORT9_PIN1,  Bit_RESET); //GPIOA        pin 0
	else if(port == PORT10) GPIO_WriteBit(PORT10_GPIO, PORT10_PIN1, Bit_RESET); //GPIOB        pin 1
}

uint8_t State_SDO(uint8_t port)
{
	uint8_t state;
	     if(port == PORT1)  state = GPIO_ReadInputDataBit(PORT1_GPIO,   PORT1_PIN2); //GPIOB         pin 6
	else if(port == PORT2)  state = GPIO_ReadInputDataBit(PORT2_GPIO,   PORT2_PIN2); //GPIOA         pin 3
	else if(port == PORT3)  state = GPIO_ReadInputDataBit(PORT3_GPIO,   PORT3_PIN2); //GPIOB         pin 11
	else if(port == PORT4)  state = GPIO_ReadInputDataBit(PORT4_GPIO,   PORT4_PIN2); //GPIOB         pin 14
	else if(port == PORT5)  state = GPIO_ReadInputDataBit(PORT5_D_GPIO, PORT5_PIN2); //PORT5_D GPIOB pin 8
	else if(port == PORT6)  state = GPIO_ReadInputDataBit(PORT6_GPIO,   PORT6_PIN2); //GPIOA         pin 12
	else if(port == PORT7)  state = GPIO_ReadInputDataBit(PORT7_GPIO,   PORT7_PIN2); //GPIOA         pin 6
	else if(port == PORT8)  state = GPIO_ReadInputDataBit(PORT8_GPIO,   PORT8_PIN2); //GPIOA         pin 11
	else if(port == PORT9)  state = GPIO_ReadInputDataBit(PORT9_A_GPIO, PORT9_PIN2); //PORT9_A GPIOB pin 8
	else if(port == PORT10) state = GPIO_ReadInputDataBit(PORT10_GPIO,  PORT10_PIN2);//GPIOB         pin 12
	return state;
}
uint8_t State_SDI(uint8_t port)
{
	uint8_t state;
	     if(port == PORT1) state = GPIO_ReadInputDataBit(PORT1_GPIO, PORT1_PIN3); //GPIOB pin 5
	else if(port == PORT4) state = GPIO_ReadInputDataBit(PORT4_GPIO, PORT4_PIN3); //GPIOB pin 13
	else if(port == PORT7) state = GPIO_ReadInputDataBit(PORT7_GPIO, PORT7_PIN3); //GPIOA pin 7
	return state;
}
void Pulse_SCL(uint8_t port, uint8_t times)
{
	uint8_t i;
	for(i = 0; i < times; i++)
	{
		delay_us(1);
		Set_SCL(port);
		delay_us(1);
		Reset_SCL(port);
		delay_us(1);
	}
}

void Set_SDO(uint8_t port)
{
	     if(port == PORT1)  GPIO_WriteBit(PORT1_GPIO,   PORT1_PIN2, Bit_SET); //GPIOB  pin 6
	else if(port == PORT2)  GPIO_WriteBit(PORT2_GPIO,   PORT2_PIN2, Bit_SET); //GPIOA         pin 3
	else if(port == PORT3)  GPIO_WriteBit(PORT3_GPIO,   PORT3_PIN2, Bit_SET); //GPIOB         pin 11
	else if(port == PORT4)  GPIO_WriteBit(PORT4_GPIO,   PORT4_PIN2, Bit_SET); //GPIOB         pin 14
	else if(port == PORT5)  GPIO_WriteBit(PORT5_D_GPIO, PORT5_PIN2, Bit_SET); //PORT5_D GPIOB pin 8
	else if(port == PORT6)  GPIO_WriteBit(PORT6_GPIO,   PORT6_PIN2, Bit_SET); //GPIOA         pin 12
	else if(port == PORT7)  GPIO_WriteBit(PORT7_GPIO,   PORT7_PIN2, Bit_SET); //GPIOA         pin 6
	else if(port == PORT8)  GPIO_WriteBit(PORT8_GPIO,   PORT8_PIN2, Bit_SET); //GPIOA         pin 11
	else if(port == PORT9)  GPIO_WriteBit(PORT9_A_GPIO, PORT9_PIN2, Bit_SET); //PORT9_A GPIOB pin 8
	else if(port == PORT10) GPIO_WriteBit(PORT10_GPIO, PORT10_PIN2, Bit_SET); //GPIOB         pin 12
}

void Reset_SDO(uint8_t port)
{
	     if(port == PORT1)  GPIO_WriteBit(PORT1_GPIO,   PORT1_PIN2, Bit_RESET); //GPIOB  pin 6
	else if(port == PORT2)  GPIO_WriteBit(PORT2_GPIO,   PORT2_PIN2, Bit_RESET); //GPIOA         pin 3
	else if(port == PORT3)  GPIO_WriteBit(PORT3_GPIO,   PORT3_PIN2, Bit_RESET); //GPIOB         pin 11
	else if(port == PORT4)  GPIO_WriteBit(PORT4_GPIO,   PORT4_PIN2, Bit_RESET); //GPIOB         pin 14
	else if(port == PORT5)  GPIO_WriteBit(PORT5_D_GPIO, PORT5_PIN2, Bit_RESET); //PORT5_D GPIOB pin 8
	else if(port == PORT6)  GPIO_WriteBit(PORT6_GPIO,   PORT6_PIN2, Bit_RESET); //GPIOA         pin 12
	else if(port == PORT7)  GPIO_WriteBit(PORT7_GPIO,   PORT7_PIN2, Bit_RESET); //GPIOA         pin 6
	else if(port == PORT8)  GPIO_WriteBit(PORT8_GPIO,   PORT8_PIN2, Bit_RESET); //GPIOA         pin 11
	else if(port == PORT9)  GPIO_WriteBit(PORT9_A_GPIO, PORT9_PIN2, Bit_RESET); //PORT9_A GPIOB pin 8
	else if(port == PORT10) GPIO_WriteBit(PORT10_GPIO, PORT10_PIN2, Bit_RESET); //GPIOB         pin 12
}

void delay_us(__IO uint32_t num)
{
	uint32_t index;
	for(index = 0; index < 7*num; index++);
}

void delay_ms(__IO uint32_t num)
{
	uint32_t index;
	for(index = 0; index < 6000*num; index++);
}




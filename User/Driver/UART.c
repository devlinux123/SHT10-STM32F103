#include "UART.h"
#include "SHT1x.h"
#include "ADC.h"
#include "DHT22.h"
#include "TIMER.h"

UART_typedef UART_rf =
{
	.counter = 0,
	.len = 0,
	.flag = FLAG_INACTIVE,
	.check_sum = 0,
	.time_out = 0,
};

UART_typedef UART2_sensor =
{
	.counter = 0,
	.len = 0,
	.flag = FLAG_INACTIVE,
	.check_sum = 0,
	.time_out = 0,
};

UART_typedef UART3_sensor =
{
	.counter = 0,
	.len = 0,
	.flag = FLAG_INACTIVE,
	.check_sum = 0,
	.time_out = 0,
};

packet_typedef PACKET;


//-----------UART-SOFT-9600---------------------//
void Transmit_Cmd(uint8_t port, uint8_t data)
{
	int8_t j;
	Reset_SDO(port);
	delay_us(104);
	for(j = 7; j >= 0; j--)
	{
		if(((data <<  j) & 0x80) == 0x80){Set_SDO(port);}
		else {Reset_SDO(port);}
		delay_us(104);
	}
	Set_SDO(port);
	delay_us(120);
}

uint8_t Receive_data(uint8_t port, uint8_t flag_start)
{
	uint8_t j, data = 0;
	uint8_t data_bit;
	uint32_t start_time, stop_time = 10;
	start_time = System_GetTick();
	while(System_GetTick() - start_time < stop_time)
	{
		if(State_SDI(port) == 0)
		{
			flag_start = FLAG_INACTIVE;
			stop_time = 0;
		}
	}
	if(flag_start == FLAG_ACTIVE)
	{
		return 0;
	}
	delay_us(52);
	for(j = 0; j < 8; j++)
	{
		delay_us(104);
		data_bit = State_SDI(port);
		data = data | (data_bit << j);
	}
	delay_us(104); //dieu chinh delay stopbit 88
	flag_start = FLAG_ACTIVE;
	return data;
}



void UART_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART_RF, &USART_InitStructure);
	USART_Cmd(UART_RF, ENABLE);
	USART_ClearFlag(UART_RF, USART_FLAG_RXNE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ClearFlag(UART_RF, USART_IT_RXNE);
	USART_ITConfig(UART_RF, USART_IT_RXNE, ENABLE);
}

void config_UART(uint8_t port,uint32_t baud)
{
	switch(port)
	{
		case PORT2: 
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

								GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(GPIOA, &GPIO_InitStructure);

								GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(GPIOA, &GPIO_InitStructure);

								USART_InitStructure.USART_BaudRate = baud;
								USART_InitStructure.USART_WordLength=USART_WordLength_8b;
								USART_InitStructure.USART_StopBits=USART_StopBits_1;
								USART_InitStructure.USART_Parity=USART_Parity_No;
								USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
								USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	
								USART_Init(USART2, &USART_InitStructure);
								USART_Cmd(USART2, ENABLE);
								USART_ClearFlag(USART2, USART_FLAG_RXNE);
							
								NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
								NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
								NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
								NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
								NVIC_Init(&NVIC_InitStructure);
								USART_ClearFlag(USART2, USART_IT_RXNE);
								USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//cho phep ngat nhan
								

								break;
		case PORT3: 
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

								GPIO_InitStructure.GPIO_Pin = PORT3_PIN1; 
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(GPIOB, &GPIO_InitStructure);

								GPIO_InitStructure.GPIO_Pin = PORT3_PIN2; 
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
								GPIO_Init(GPIOB, &GPIO_InitStructure);

								USART_InitStructure.USART_BaudRate = baud;
								USART_InitStructure.USART_WordLength=USART_WordLength_8b;
								USART_InitStructure.USART_StopBits=USART_StopBits_1;
								USART_InitStructure.USART_Parity=USART_Parity_No;
								USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
								USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	
								USART_Init(USART3, &USART_InitStructure);
								USART_Cmd(USART3, ENABLE);
								USART_ClearFlag(USART3, USART_FLAG_RXNE);
							
								NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
								NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
								NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
								NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
								NVIC_Init(&NVIC_InitStructure);
								USART_ClearFlag(USART3, USART_IT_RXNE);
								USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//cho phep ngat nhan
								

								break;
		default: break;
	}
}







//-------------Transmit-------------//
void uartPC_putchar(uint8_t ch)
{
	USART_SendData(USART1, (uint8_t) ch); 
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}
void uartPC_putData(uint32_t data, uint8_t num_byte)
{
	int8_t i;
	for(i = num_byte - 1; i >= 0; i--)
	{
		uartPC_putchar((data >> i*8));
		UART_rf.check_sum += (uint8_t)(data >> i*8);
	}
}

void uart_putchar(uint8_t ch)
{
	USART_SendData(USART1, (uint8_t) ch); 
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}
void uart_putData(uint8_t *data, uint8_t num_byte)
{
	uint8_t i;
	for(i = 0; i < num_byte; i++)
	{
		uart_putchar(data[i]);
	}
}
void uart2_putchar(uint8_t ch)
{
	USART_SendData(USART2, (uint8_t) ch); 
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}
void uart2_putData(uint8_t *data, uint8_t num_byte)
{
	uint8_t i;
	for(i = 0; i < num_byte; i++)
	{
		uart2_putchar(data[i]);
	}
}

void uart3_putchar(uint8_t ch)
{
	USART_SendData(USART3, (uint8_t) ch); 
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}
void uart3_putData(uint8_t *data, uint8_t num_byte)
{
	uint8_t i;
	for(i = 0; i < num_byte; i++)
	{
		uart3_putchar(data[i]);
	}
}

//----------------Analyze-Packet--------------------//
void analyze_Packet(uint8_t *buff, uint8_t len)
{
	if(get_Checksum(&buff[1], len-2) != buff[buff[3]-1])
	{
		PACKET.start_code = START_FAILE;
		return;
	}
	PACKET.security = buff[0];
	PACKET.start_code = buff[1];
	PACKET.size = (uint16_t)buff[2] << 8 | buff[3]; // lay gia tri kich thuoc cua chuoi luu vao bien PACKET.size
	PACKET.status = buff[4];
	PACKET.id_pan = buff[5];
	PACKET.id_group = buff[6];
	PACKET.id_node = (uint16_t)buff[7] << 8 | buff[8];
	PACKET.level = buff[9];
	PACKET.len_value = PACKET.size - 14;
	memcpy(PACKET.value, &buff[13], PACKET.len_value);
	// void *memcpy(void *str1, const void *str2, size_t n) sao chép n ký tu tu str2 toi str1.//
}

uint8_t get_Checksum(uint8_t *buff, uint8_t len)
{
	uint8_t i, checksum = 0;
	for(i = 0; i < len; i++)
	{
		checksum += buff[i];
	}
	return checksum;
}
/*
 checksum = byte[start]+  . . .  + byte[value]
 lay 1byte cuoi sosanh
*/








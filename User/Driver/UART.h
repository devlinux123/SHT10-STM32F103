#include "GPIO.h"


#define FLAG_INACTIVE												0x00
#define FLAG_ACTIVE													0x01
#define START_FAILE													0xFF


#define UART_RF						USART1

#define SECURITY							(uint8_t)0xF0
#define START									(uint8_t)0x11
#define SIZE_H								(uint8_t)0x00
#define SIZE_L								(uint8_t)0x11
#define SIZE_L_3B							(uint8_t)0x12
#define STATUS								(uint8_t)0xFE
#define ID_PAN								(uint8_t)0xFF
#define ID_GROUP							(uint8_t)0xFF
#define PORT									(uint8_t)0x0007
#define ID_GATEWAY						(uint8_t)0x0000
#define PACKET_INDEX					(uint8_t)0x0000

#define CHECK_SUM0_TEMP				(uint8_t)0x22
#define CHECK_SUM0_HUMI				(uint8_t)0x25
#define	CHECK_SUM0_DUST				(uint8_t)0x2B
#define	CHECK_SUM0_CO2				(uint8_t)0x2E 
#define CHECK_SUM0_H2					(uint8_t)0x2F 
#define	CHECK_SUM0_CO					(uint8_t)0x30 
#define	CHECK_SUM0_GAS				(uint8_t)0x31
#define CHECK_SUM0_PRESSURE		(uint8_t)0x32
#define CHECK_SUM0_WIND_SPEED	(uint8_t)0x33
#define CHECK_SUM0_WIND_DIRECT (uint8_t)0x35

#define PROPERTY_TEMP					(uint8_t)0x04   //->4
#define PROPERTY_HUMI					(uint8_t)0x07   //->7
#define PROPERTY_DUST					(uint8_t)0x0D   //->13
#define PROPERTY_CO2					(uint8_t)0x10   //->16
#define PROPERTY_H2						(uint8_t)0x11   //->17
#define PROPERTY_CO						(uint8_t)0x12   //->18
#define PROPERTY_GAS					(uint8_t)0x13   //->19
#define	PROPERTY_PRESSURE			(uint8_t)0x14	  //->20
#define PROPERTY_WIND_SPEED		(uint8_t)0x15   //->21
#define PROPERTY_WIND_DIRECT	(uint8_t)0x16   //->22

#define INFORMATION_DUST						(uint8_t)0x20
#define INFORMATION_MULTISENSOR			(uint8_t)0x23
#define INFORMATION_CO2							(uint8_t)0x24
#define INFORMATION_H2							(uint8_t)0x25
#define INFORMATION_CO							(uint8_t)0x26
#define INFORMATION_GAS							(uint8_t)0x27
#define INFORMATION_WIND_SPEED			(uint8_t)0x28
#define INFORMATION_WIND_DIRECT			(uint8_t)0x29
#define INFORMATION_HUMI						(uint8_t)0x2A
#define INFORMATION_TEMP						(uint8_t)0x2B
#define INFORMATION_PRESSURE				(uint8_t)0x2E


typedef struct
{
	uint16_t counter;
	uint8_t len;
	uint8_t cmd[100];
	uint8_t flag;
	uint8_t check_sum;
	uint32_t time_out;
	
}UART_typedef;

typedef struct
{
	uint8_t security;
	uint8_t start_code;
	uint16_t size;
	uint8_t status;
	uint8_t id_pan;
	uint8_t id_group;
	uint16_t id_node;
	uint8_t level;
	uint8_t value[50];
	uint8_t len_value;
	uint8_t checksum;
	uint8_t property;
}packet_typedef;


extern UART_typedef UART_rf;
extern UART_typedef UART2_sensor;
extern UART_typedef UART3_sensor;

extern packet_typedef PACKET;

void Transmit_Cmd(uint8_t port, uint8_t data);
uint8_t Receive_data(uint8_t port, uint8_t flag_start);

void config_UART(uint8_t port,uint32_t baud);
void UART_init(void);

void uartPC_putchar(uint8_t ch);
void uartPC_putData(uint32_t data, uint8_t num_byte);
void uart_putchar(uint8_t ch);
void uart_putData(uint8_t *data, uint8_t num_byte);
void uart2_putchar(uint8_t ch);
void uart2_putData(uint8_t *data, uint8_t num_byte);
void uart3_putchar(uint8_t ch);
void uart3_putData(uint8_t *data, uint8_t num_byte);

void analyze_Packet(uint8_t *buff, uint8_t len);
uint8_t get_Checksum(uint8_t *buff, uint8_t len);


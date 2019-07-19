#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"

#define NUM_SAMP_RESPONSE		(uint8_t)3

/******* SENSOR GPIO ********************************************/

#define PORT1_GPIO			GPIOB
#define	PORT2_GPIO			GPIOA
#define	PORT3_GPIO			GPIOB
#define	PORT4_GPIO			GPIOB
#define	PORT5_A_GPIO		GPIOA // PORT5_A
#define	PORT5_D_GPIO		GPIOB // PORT5_D
#define PORT6_GPIO			GPIOA
#define	PORT7_GPIO			GPIOA
#define PORT8_GPIO			GPIOA
#define	PORT9_D_GPIO		GPIOA // PORT9_D
#define	PORT9_A_GPIO		GPIOB // PORT9_A
#define	PORT10_GPIO			GPIOB

/******* SENSOR PIN ********************************************/

#define PORT1_PIN1			GPIO_Pin_7   
#define PORT1_PIN2			GPIO_Pin_6   
#define PORT1_PIN3			GPIO_Pin_5   

#define PORT2_PIN1			GPIO_Pin_2  
#define PORT2_PIN2			GPIO_Pin_3  

#define PORT3_PIN1			GPIO_Pin_10  
#define PORT3_PIN2			GPIO_Pin_11 

#define PORT4_PIN1			GPIO_Pin_15 
#define PORT4_PIN2			GPIO_Pin_14 
#define PORT4_PIN3			GPIO_Pin_13 

#define PORT5_PIN1			GPIO_Pin_0  
#define PORT5_PIN2			GPIO_Pin_8

#define PORT6_PIN1			GPIO_Pin_1  
#define PORT6_PIN2			GPIO_Pin_12 

#define PORT7_PIN1			GPIO_Pin_5  
#define PORT7_PIN2			GPIO_Pin_6 
#define PORT7_PIN3			GPIO_Pin_7  

#define PORT8_PIN1			GPIO_Pin_4  
#define PORT8_PIN2			GPIO_Pin_11 

#define PORT9_PIN1			GPIO_Pin_0
#define PORT9_PIN2			GPIO_Pin_8

#define PORT10_PIN1			GPIO_Pin_1  
#define PORT10_PIN2			GPIO_Pin_12 

#define	PORT1						0
#define	PORT2						1
#define	PORT3						2
#define	PORT4						3
#define	PORT5						4
#define	PORT6						5
#define	PORT7						6
#define	PORT8						7
#define	PORT9						8
#define	PORT10					9

#define	INTF_DIGITAL		1	
#define INTF_UART				2
#define	INTF_ADC				3
#define	INTF_EXTI				4

#define LED_Run_GPIO					GPIOB
#define LED_Run_Pin						GPIO_Pin_9
#define LED_Run_ON						GPIO_WriteBit(LED_Run_GPIO, LED_Run_Pin, Bit_RESET)
#define LED_Run_OFF						GPIO_WriteBit(LED_Run_GPIO, LED_Run_Pin, Bit_SET)


#define UART_RF_GPIO					GPIOA
#define UART_RF_Tx						GPIO_Pin_9
#define UART_RF_Rx						GPIO_Pin_10





extern GPIO_InitTypeDef		GPIO_InitStructure;
extern USART_InitTypeDef 	USART_InitStructure;
extern NVIC_InitTypeDef		NVIC_InitStructure;
extern TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
extern DMA_InitTypeDef DMA_InitStructure;
extern ADC_InitTypeDef ADC_InitStructure;

void config_DIGITAL(uint8_t port);


void GPIO_init(void);

void config_SDO_Output(uint8_t port);
void config_SDO_Input(uint8_t port);
uint8_t State_SDO(uint8_t port);
uint8_t State_SDI(uint8_t port);
void Set_SCL(uint8_t port);
void Reset_SCL(uint8_t port);
void Pulse_SCL(uint8_t port, uint8_t times);
void Set_SDO(uint8_t port);
void Reset_SDO(uint8_t port);

void config_port(uint8_t port);

void delay_us(__IO uint32_t num);
void delay_ms(__IO uint32_t num);


#include "GPIO.h"


typedef struct
{
	uint32_t SysTick_Counter;
	
}SysTick_typedef;


extern SysTick_typedef	systick;

void TIMER_init(void);
void Systick_init(void);
uint32_t System_GetTick(void);
void delay_us(__IO uint32_t num);
void delay_ms(__IO uint32_t num);


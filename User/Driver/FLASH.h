#include "GPIO.h"



#define FLASH_ADDR											((uint32_t)0x0800E000)
#define FLASH_SIZE											((uint16_t) 50)

#define FLASH_CHECK											0x69696969
#define ADDR_CHECK											0
#define	ADDR_PROPERTY										ADDR_CHECK+1
#define ADDR_INTERFACE									ADDR_PROPERTY+10
#define ADDR_RH_OFFSET									ADDR_INTERFACE+10
#define ADDR_TEMP_OFFSET								ADDR_RH_OFFSET+1
#define ADDR_CO_OFFSET									ADDR_TEMP_OFFSET+1    //4byte
#define ADDR_CO2_OFFSET									ADDR_CO_OFFSET+1
#define	ADDR_GAS_OFFSET									ADDR_CO2_OFFSET+1
#define	ADDR_H2_OFFSET									ADDR_GAS_OFFSET+1
#define ADDR_WIND_SPEED_OFFSET					ADDR_H2_OFFSET+1
#define ADDR_WIND_DIRECT_OFFSET					ADDR_WIND_SPEED_OFFSET+1
#define ADDR_PRESSURE_OFFSET						ADDR_WIND_DIRECT_OFFSET+1
#define	ADDR_DUST_OFFSET								ADDR_PRESSURE_OFFSET+1

// Setting value offset cho sensor //
#define RH_OFFSET_DEFAULT		0         //===== SHT1x.h =====//  
#define TEMP_OFFSET_DEFAULT	0         //=== DS18B20.h ===//
#define	DUST_OFFSET_DEFAULT	00        //=== ZH03B.h ===//
#define CO_RO_DEFAULT				3000      //=== MQ-Series.h ===//
#define CO2_OFFSET_DEFAULT  0         //=== WinSen-Series.h ===//
#define GAS_RO_DEFAULT			3000      //=== MQ-Series.h ===//
#define H2_RO_DEFAULT				300000    //=== MQ-Series.h ===//
#define WIND_SPEED_OFFSET_DEFAULT	0   //=== YGC-Series.h ===//
#define WIND_DIRECT_OFFSET_DEFAULT	0 //=== YGC-Series.h ===//
#define PRESSURE_DEFAULT 0            // BMP180.h //








typedef struct
{
	uint32_t buff[FLASH_SIZE];
	uint32_t	property_buff[10];
	uint32_t	interface_buff[10];
	
}flash_typedef;

extern flash_typedef flash;


void FLASH_update_information(void);
void read_FLASH(void);
void write_FLASH(void);
void default_value(void);


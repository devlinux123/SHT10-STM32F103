#include "GPIO.h"

#define INACTIVE		0x00
#define ACTIVE			0x01



//--------------- CMD SHT10 ------------------------------//
#define ADDR_SHT10TEMP			((uint8_t)0x03)
#define ADDR_SHT10RH				((uint8_t)0x05)
#define ADDR_SHT10WSR				((uint8_t)0x06)	
#define ADDR_SHT10RSR				((uint8_t)0x07)
#define ADDR_SHT10SR				((uint8_t)0x1E)

//-------------- PARAMETER SHT10 -------------------------//
#define SHT10_c1		((double_t) -2.0468f)
#define SHT10_c2		((double_t) 0.0367f)
#define SHT10_c3		((double_t) -1.5955f)
#define SHT10_t1		((double_t) 0.01f)
#define SHT10_t2		((double_t) 0.00008f)
#define SHT10_d1		((double_t) -39.7f)
#define SHT10_d2		((double_t) 0.01f)

typedef struct
{
	double_t RH_Linear;
	double_t RH_True;
	uint16_t RH[NUM_SAMP_RESPONSE+1];
	double_t Temp;
	int16_t Data_RH;
	int16_t Data_Temp;
	int16_t Base_RH;
	int16_t Offset_RH;
	uint8_t flag;
	uint8_t crc;
	uint8_t crc_temp;
	uint8_t crc_rh;
	uint8_t crc_check;
	
}RH_typedef;



extern RH_typedef HUMI;


void SHT1x_StartCondition(uint8_t port);
void SHT1x_StopCondition(uint8_t port);
void SHT1x_ACK(uint8_t port);
uint8_t SHT1x_CRC8_Check(uint32_t data, uint32_t addr, uint8_t polynomial);
int16_t SHT1x_Read(uint8_t addr, uint8_t port);
void get_RH(uint16_t port);



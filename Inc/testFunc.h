#include "stm32f4xx_hal.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "ade7953_reg.h"
#include "math.h"

#define		IConst						3.9/1808378
#define 	UConst						234.0/3220000
#define		ApparentConstMin	100.0/37402
#define		ApparentConst			((3.9*234.0)/346015)
#define		ReactiveConstMax	((20*230)/(310))
#define		ReactiveConstMin	((-0.39*231.0)/(310))
#define   ActiveConstMin		100.0/37348
#define		ActiveConst				((3.9*234.0)/343678)
#define		PowerFConst				1.0/32768
#define 	AngleConst				4.47/1000000

#define		ActiveEConst			(233*3.92)/(290*3600)

extern uint8_t signFlag;

void ADE7953_CS_LOW(void);
void ADE7953_CS_HIGH(void);
void ADE7953_RES_LOW(void);
void ADE7953_RES_HIGH(void);
void ADE7953_reset(void);
void ADE7953_init(void);
void ADE7953_SetGain(uint8_t gain);
void SpiTest(void);
void sortFrame(uint8_t rw, uint32_t reg, uint8_t *lit_int);
void sortFrameWrite(uint8_t rw, uint32_t reg, uint32_t value, uint8_t *lit_int);
void sortFrameWrite8(uint8_t rw, uint16_t reg, uint8_t value, uint8_t *lit_int);
void sortFrameWrite16(uint8_t rw, uint16_t reg, uint16_t value, uint8_t *lit_int);
void sortFrameWrite16Signed(uint8_t rw, uint16_t reg, int16_t value, int8_t *lit_int);
void sortFrameWrite32(uint8_t rw, uint16_t reg, uint32_t value, uint8_t *lit_int);
void UartADE(void);
void checkRegValue(void);
void checkPrintRegValue(uint16_t reg, char *string);
void checkPrintRegValueSigned(uint16_t reg, char *string);
void checkPrintRegValue16(uint16_t reg, char *string, uint8_t sign);
void checkAvgPrintRegValue(uint16_t reg, char *string);
float calculateRealValue(uint16_t reg, char *string, char *string2, uint8_t print);
float calculateRealValue16(uint16_t reg, char *string, char *string2, uint8_t print);

float ReadAngle(uint16_t reg);

void startUartADE(void);
void stopUartADE(void);

uint16_t ADE7953_Read(uint16_t Reg);
uint8_t ADE7953_Read8(uint16_t Reg);
int16_t ADE7953_Read16(uint16_t Reg);
uint32_t ADE7953_Read32(uint32_t Reg);
uint32_t ADE7953_Read32Signed(uint32_t Reg);

void ADE7953_Write(uint16_t Reg, uint32_t Value);
void ADE7953_Write8(uint16_t Reg, uint8_t Value);
void ADE7953_Write16(uint16_t Reg, uint16_t Value);
void ADE7953_Write16Test(uint16_t Reg, int16_t Value);
void ADE7953_Write32(uint16_t Reg, uint32_t Value);

uint8_t ADE7953_SPI_Read(uint8_t data);
uint8_t ADE7953_SPI_Read8(uint16_t Reg);
uint16_t ADE7953_SPI_Read16(uint16_t Reg);
uint32_t ADE7953_SPI_Read32(uint16_t Reg);
uint32_t ADE7953_SPI_Read32_Signed(uint16_t Reg);

void ADE7953_SPI_Write8(uint16_t Reg, uint8_t Value);
void ADE7953_SPI_Write16(uint16_t Reg, uint16_t Value);
void ADE7953_SPI_Write32(uint16_t Reg, uint32_t Value);

void sortFrameReadSPI(uint8_t rw, uint32_t reg, uint8_t *lit_int);
void sortFrameWriteSPI_8(uint8_t rw, uint32_t reg, uint8_t value, uint8_t *lit_int); 
void sortFrameWriteSPI_16(uint8_t rw, uint32_t reg, uint16_t value, uint8_t *lit_int); 
void sortFrameWriteSPI_32(uint8_t rw, uint32_t reg, uint32_t value, uint8_t *lit_int); 

void checkPrintRegValueSigned_SPI(uint16_t reg, char *string);

uint8_t ADE7953_RegisterValue8(uint16_t reg, char *string, uint8_t print);
uint16_t ADE7953_RegisterValue16(uint16_t reg, char *string, uint8_t print);
int16_t ADE7953_RegisterValue16_Signed(uint16_t reg, char *string, uint8_t print);
uint32_t ADE7953_RegisterValue32(uint16_t reg, char *string, uint8_t print);
int32_t ADE7953_RegisterValue32_Signed(uint16_t reg, char *string, uint8_t print);

float ADE7953_CalculateRegisterValue16_Signed(uint16_t reg, char *string, uint8_t print);
float ADE7953_CalculateRegisterValue32(uint16_t reg, char *string, char *string2, uint8_t print);
float ADE7953_CalculateRegisterValue32_Signed(uint16_t reg, char *string, char *string2, uint8_t print);

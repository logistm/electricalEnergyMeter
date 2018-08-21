
#include "testFunc.h"

uint8_t ADE7953_Read8(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer = 0;
		
	sortFrame(READ_UART, Reg, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);	
	HAL_UART_Receive(&huart1, &rxBuffer, sizeof(rxBuffer), 15);
	
	return rxBuffer;
}

int16_t ADE7953_Read16(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[2] = {0, 0};
	uint16_t returnBuffer = 0;
	
	sortFrame(READ_UART, Reg, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);	
	HAL_UART_Receive(&huart1, rxBuffer, sizeof(rxBuffer), 15);
	
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8);	
	
	return returnBuffer;
}

uint32_t ADE7953_Read32(uint32_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[4] = {0, 0, 0, 0};
	uint32_t returnBuffer = 0;
	
	sortFrame(READ_UART, Reg, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);	
	HAL_UART_Receive(&huart1, rxBuffer, sizeof(rxBuffer), 15);
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8) | (rxBuffer[2] << 16) | (rxBuffer[3] << 24);
	
	return returnBuffer;
}

uint32_t ADE7953_Read32Signed(uint32_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[4] = {0, 0, 0, 0};
	uint32_t returnBuffer = 0;
	
	sortFrame(READ_UART, Reg, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);	
	HAL_UART_Receive(&huart1, rxBuffer, sizeof(rxBuffer), 15);
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8) /*| (rxBuffer[2] << 16) | (rxBuffer[3] << 24)*/;
	
	if(rxBuffer[2] == 0xFF && rxBuffer[3] == 0xFF) signFlag = 1;
	else signFlag = 0;
		
	return returnBuffer;
}

void ADE7953_Write8(uint16_t Reg, uint8_t Value)
{
	uint8_t txBuffer[4] = {0, 0, 0, 0};
	
	sortFrameWrite8(WRITE_UART, Reg, Value, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[3], sizeof(txBuffer[3]), 5);
	HAL_Delay(5);
}

void ADE7953_Write16(uint16_t Reg, uint16_t Value)
{
	uint8_t txBuffer[5] = {0, 0, 0, 0, 0};
	
	sortFrameWrite16(WRITE_UART, Reg, Value, txBuffer);

	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[3], sizeof(txBuffer[3]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[4], sizeof(txBuffer[4]), 5);
	HAL_Delay(5);
}

void ADE7953_Write32(uint16_t Reg, uint32_t Value)
{
	uint8_t txBuffer[7] = {0, 0, 0, 0, 0, 0, 0};
	
	sortFrameWrite32(WRITE_UART, Reg, Value, txBuffer);
	HAL_Delay(5);					
	HAL_UART_Transmit(&huart1, &txBuffer[0], sizeof(txBuffer[0]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[1], sizeof(txBuffer[1]), 5);
	HAL_Delay(1);	
	HAL_UART_Transmit(&huart1, &txBuffer[2], sizeof(txBuffer[2]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[3], sizeof(txBuffer[3]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[4], sizeof(txBuffer[4]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[5], sizeof(txBuffer[5]), 5);
	HAL_Delay(1);		
	HAL_UART_Transmit(&huart1, &txBuffer[6], sizeof(txBuffer[6]), 5);
	HAL_Delay(5);
}

void sortFrame(uint8_t rw, uint32_t reg, uint8_t *lit_int) 
{
	lit_int[2] = (uint8_t)(reg >>  0);
  lit_int[1] = (uint8_t)(reg >>  8);
  lit_int[0] = (uint8_t)(rw);
}

void sortFrameReadSPI(uint8_t rw, uint32_t reg, uint8_t *lit_int) 
{
	lit_int[2] = (uint8_t)(rw);
	lit_int[1] = (uint8_t)(reg >> 0);
  lit_int[0] = (uint8_t)(reg >> 8);  
}

void sortFrameWriteSPI_8(uint8_t rw, uint32_t reg, uint8_t value, uint8_t *lit_int) 
{	
	lit_int[3] = (uint8_t)(value);
	lit_int[2] = (uint8_t)(rw);
	lit_int[1] = (uint8_t)(reg >> 0);
  lit_int[0] = (uint8_t)(reg >> 8);  
}

void sortFrameWriteSPI_16(uint8_t rw, uint32_t reg, uint16_t value, uint8_t *lit_int)
{
	lit_int[4] = (uint8_t)(value >> 0);
	lit_int[3] = (uint8_t)(value >> 8 );
	lit_int[2] = (uint8_t)(rw);
	lit_int[1] = (uint8_t)(reg >> 0);
  lit_int[0] = (uint8_t)(reg >> 8);  	
}

void sortFrameWriteSPI_32(uint8_t rw, uint32_t reg, uint32_t value, uint8_t *lit_int)
{	
	lit_int[6] = (uint8_t)(value >> 0);
	lit_int[5] = (uint8_t)(value >> 8);
	lit_int[4] = (uint8_t)(value >> 16);
	lit_int[3] = (uint8_t)(value >> 24);
	lit_int[2] = (uint8_t)(rw);
	lit_int[1] = (uint8_t)(reg >> 0);
  lit_int[0] = (uint8_t)(reg >> 8);
}

void sortFrameWrite(uint8_t rw, uint32_t reg, uint32_t value, uint8_t *lit_int) 
{
	lit_int[4] = (uint8_t)(value >>  8);
	lit_int[3] = (uint8_t)(value >>  0);
	lit_int[2] = (uint8_t)(reg >>  0);
	lit_int[1] = (uint8_t)(reg >>  8);
  lit_int[0] = (uint8_t)(rw);
}

void sortFrameWrite8(uint8_t rw, uint16_t reg, uint8_t value, uint8_t *lit_int)
{
	lit_int[3] = (uint8_t)(value);
	lit_int[2] = (uint8_t)(reg >>  0);
	lit_int[1] = (uint8_t)(reg >>  8);
  lit_int[0] = (uint8_t)(rw);
}

void sortFrameWrite16(uint8_t rw, uint16_t reg, uint16_t value, uint8_t *lit_int)
{
	lit_int[4] = (uint8_t)(value >>  8);
	lit_int[3] = (uint8_t)(value >>  0);
	lit_int[2] = (uint8_t)(reg >>  0);
	lit_int[1] = (uint8_t)(reg >>  8);
  lit_int[0] = (uint8_t)(rw);
}

void sortFrameWrite16Signed(uint8_t rw, uint16_t reg, int16_t value, int8_t *lit_int)
{
	lit_int[4] = (int8_t)(value >>  8);
	lit_int[3] = (int8_t)(value >>  0);
	lit_int[2] = (int8_t)(reg >>  0);
	lit_int[1] = (int8_t)(reg >>  8);
  lit_int[0] = (int8_t)(rw);
}

void sortFrameWrite32(uint8_t rw, uint16_t reg, uint32_t value, uint8_t *lit_int)
{
	lit_int[6] = (uint8_t)(value >>  24);
	lit_int[5] = (uint8_t)(value >>  16);
	lit_int[4] = (uint8_t)(value >>  8);
	lit_int[3] = (uint8_t)(value >>  0);
	lit_int[2] = (uint8_t)(reg >>  0);
	lit_int[1] = (uint8_t)(reg >>  8);
  lit_int[0] = (uint8_t)(rw);
}

void startUartADE()
{
	HAL_GPIO_WritePin(SS_ADE_GPIO_Port, SS_ADE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CLK_ADE_GPIO_Port, CLK_ADE_Pin, GPIO_PIN_RESET);
}

void stopUartADE()
{
	HAL_GPIO_WritePin(SS_ADE_GPIO_Port, SS_ADE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CLK_ADE_GPIO_Port, CLK_ADE_Pin, GPIO_PIN_SET);
}


void ADE7953_init()
{
	ADE7953_SPI_Write32(0x00FE, 0xAD);	// write according to datasheet
	ADE7953_SPI_Write16(0x120, 0x30);		// write according to datasheet
	ADE7953_SPI_Write16(CONFIG, 0x4);		// lock communication to SPI
	
	ADE7953_RegisterValue16(LINECYC, "LINECYC: ", 1);
	ADE7953_SPI_Write16(LINECYC, 100);
	ADE7953_RegisterValue16(LINECYC, "LINECYC: ", 1);			/*acc mode*/

	ADE7953_RegisterValue8(LCYCMODE, "LCYCMODE: ", 1);
	ADE7953_SPI_Write8(LCYCMODE, 85);
	ADE7953_RegisterValue8(LCYCMODE, "LCYCMODE: ", 1);
	
	ADE7953_SetGain(0);

//	
//	ADE7953_RegisterValue32(IRQENA_32, "IRQENA: ", 1);	/*enable an interrupt when new waveform data is acquired*/
//	ADE7953_RegisterValue32(IRQSTATA_32, "IRQSTATA: ", 1);
//	ADE7953_SPI_Write32(IRQENA_32, 2228224);
//	ADE7953_RegisterValue32(IRQENA_32, "IRQENA: ", 1);
		
}

// 1 -> 2x | 2 -> 4x | 3 -> 8x | 4 -> 16x | 5 -> 22x
void ADE7953_SetGain(uint8_t gain)
{
	ADE7953_RegisterValue8(PGA_IA, "PGA_IA: ", 1);
	ADE7953_SPI_Write8(PGA_IA, gain);
	ADE7953_RegisterValue8(PGA_IA, "PGA_IA: ", 1);
}

void ADE7953_reset()
{
	ADE7953_RES_LOW();
	HAL_Delay(20);
	ADE7953_RES_HIGH();
	HAL_Delay(20);
}

void ADE7953_RES_HIGH()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}

void ADE7953_RES_LOW()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
}

void ADE7953_CS_LOW()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
}

void ADE7953_CS_HIGH()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
}

void checkPrintRegValue(uint16_t reg, char *string)
{
	uint32_t buf32u;
	char stringValue[50];

	buf32u = ADE7953_Read32(reg);	
	sprintf(stringValue, "%d", buf32u);		
 
	USART_Puts(USART6, string);
	USART_Puts(USART6, stringValue);
	USART_Puts(USART6, "\n");
	
}

void checkPrintRegValueSigned(uint16_t reg, char *string)
{

	int32_t buf32;
	char stringValue[50];


	buf32 = ADE7953_Read32Signed(reg);	
	if(signFlag == 1) buf32 = (~buf32)+1;
	sprintf(stringValue, "%d", buf32);
		 
	USART_Puts(USART6, string);
	USART_Puts(USART6, stringValue);
	USART_Puts(USART6, "\n");
	
}


void checkPrintRegValue16(uint16_t reg, char *string, uint8_t sign)
{
	uint16_t buf16u;
	int16_t buf16, buf16Real;
	char stringValue[50];

	if(sign == 1) 	/*signed value*/
	{
		buf16 = ADE7953_Read16(reg);
		UsartInteger(USART6, buf16);
		buf16Real = buf16 & 0x7FFF;
		UsartInteger(USART6, buf16Real);
		
		if((buf16 & 0x8000) == 1) buf16Real = (~buf16Real)+1;
//		else if((buf16 & 0x8000) == 0) buf16Sign = 0;
		UsartInteger(USART6, buf16Real);
		
		sprintf(stringValue, "%d", buf16Real);		
	}
	
	else						/*unsigned value*/
	{
		buf16u = ADE7953_Read16(reg);
		sprintf(stringValue, "%d", buf16u);
	}
		 
	USART_Puts(USART6, string);
	USART_Puts(USART6, stringValue);
	USART_Puts(USART6, "\n");
	
}

void checkAvgPrintRegValue(uint16_t reg, char *string)
{
	uint32_t buf32;
//	uint32_t acc = 0;
	char stringValue[50];
		
//	for(int i = 0; i<=50; i++)
//	{
		buf32 = ADE7953_Read32(reg);
//		acc = acc + buf32;			
//	}	
//	
//	acc = acc / 50.0;
	
	sprintf(stringValue, "%d", buf32); 
	USART_Puts(USART6, "Average:\n");
	USART_Puts(USART6, string);
	USART_Puts(USART6, stringValue);
	USART_Puts(USART6, "\n");
}

float calculateRealValue(uint16_t reg, char *string, char *string2, uint8_t print)
{
	float value, constFactor;
	int32_t buf32;
	char stringValue[50];
	
//	for(uint8_t i=0; i<50; i++)
//	{
	
	buf32 = ADE7953_Read32(reg);
//		sum = sum + buf32;
//	}
//	
//	sum = sum/50.0;
	
	if (reg == IRMSA_32) 	constFactor = IConst;
	else if (reg == VRMS_32) constFactor = UConst;
	else if ( reg == AVA_32 ) constFactor = ApparentConst;
	else if (reg == AVAR_32 && buf32 > 0) constFactor = ReactiveConstMax * sin((3.14/180.0)*calculateRealValue16(ANGLE_A, "", "", 0));
	else if (reg == AVAR_32 && buf32 < 0) constFactor = ReactiveConstMin * sin((3.14/180.0)*calculateRealValue16(ANGLE_A, "", "", 0));
	else if (reg == AWATT_32) constFactor = ActiveConst * calculateRealValue16(PFA, "", "", 0);
	
	value = buf32 * constFactor;
	
	if(print == 1)
	{
		sprintf(stringValue, "%f", value);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, string2);
		USART_Puts(USART6, "\n");
	}
	
	return value;
}

float calculateRealValue16(uint16_t reg, char *string, char *string2, uint8_t print)
{
	float value, constFactor;
	int16_t buf16;
	char stringValue[50];
	
//	for(uint8_t i=0; i<50; i++)
//	{
		buf16 = ADE7953_Read16(reg);
	
	if(reg == PFA)
	{
		sprintf(stringValue, "%d", buf16);
		USART_Puts(USART6, "prvi:");
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	
		buf16 = (~buf16)+1;
	
		sprintf(stringValue, "%d", buf16);
		USART_Puts(USART6, "drugi:");
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
//		sum = sum + buf16;
//	}
//	
//	sum = sum/50.0;
	
	if (reg == PFA) 	constFactor = PowerFConst;
	else if (reg == ANGLE_A) constFactor = AngleConst;
	
	value = buf16 * constFactor;
	
	if(print == 1){
		sprintf(stringValue, "%f", value);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, string2);
		USART_Puts(USART6, "\n");
	}
	
	return value;
}

float ReadAngle(uint16_t reg)
{
	float angle, sum=0;	
	int16_t angleRaw = ADE7953_Read16 (reg);
	
	for(uint8_t i=0; i<20; i++)
	{
		angle = (angleRaw * ((360.0 * 50.0) / 223750.0));
		sum = angle + sum;
	}
	
	sum = sum/20.0;
	
	return sum;
}

/*-------------------------------------------  SPI  -----------------------------------*/	

uint8_t ADE7953_SPI_Read(uint8_t data)
{

	SPI1->DR = data; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_FLAG_RXNE) ); // wait until receive complete
	while( SPI1->SR & SPI_FLAG_BSY ); // wait until SPI is not busy anymore
	return SPI1->DR; // return received data from SPI data register
}

uint8_t ADE7953_SPI_Read8(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer = 0;
		
	sortFrameReadSPI(READ_SPI, Reg, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	
	rxBuffer = ADE7953_SPI_Read(0x00);
	ADE7953_CS_HIGH();
	
	return rxBuffer;
}

uint16_t ADE7953_SPI_Read16(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[2] = {0, 0};
	uint16_t returnBuffer = 0;	
	
	sortFrameReadSPI(READ_SPI, Reg, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	
	rxBuffer[1] = ADE7953_SPI_Read(0x00);
	rxBuffer[0] = ADE7953_SPI_Read(0x00);
	ADE7953_CS_HIGH();
	
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8);
	
	return returnBuffer;
}

uint32_t ADE7953_SPI_Read32(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[4] = {0, 0, 0, 0};
	uint32_t returnBuffer = 0;	
	
	sortFrameReadSPI(READ_SPI, Reg, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	
	rxBuffer[3] = ADE7953_SPI_Read(0x00);
	rxBuffer[2] = ADE7953_SPI_Read(0x00);	
	rxBuffer[1] = ADE7953_SPI_Read(0x00);
	rxBuffer[0] = ADE7953_SPI_Read(0x00);
	ADE7953_CS_HIGH();
	
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8) | (rxBuffer[2] << 16) | (rxBuffer[3] << 24);
	
	return returnBuffer;	
}

uint32_t ADE7953_SPI_Read32_Signed(uint16_t Reg)
{
	uint8_t txBuffer[3] = {0, 0, 0};	
	uint8_t rxBuffer[4] = {0, 0, 0, 0};
	uint32_t returnBuffer = 0;	
	
	sortFrameReadSPI(READ_SPI, Reg, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	
	rxBuffer[3] = ADE7953_SPI_Read(0x00);
	rxBuffer[2] = ADE7953_SPI_Read(0x00);	
	rxBuffer[1] = ADE7953_SPI_Read(0x00);
	rxBuffer[0] = ADE7953_SPI_Read(0x00);
	ADE7953_CS_HIGH();
	
	returnBuffer = rxBuffer[0] | (rxBuffer[1] << 8) | (rxBuffer[2] << 16);
	
	if(rxBuffer[3] == 0xFF) signFlag = 1;
	else if (rxBuffer[3] == 0x00) signFlag = 0;
	
	return returnBuffer;
}

void ADE7953_SPI_Write8(uint16_t Reg, uint8_t Value)
{
	uint8_t txBuffer[4] = {0, 0, 0, 0};
	
	sortFrameWriteSPI_8(WRITE_SPI, Reg, Value, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	ADE7953_SPI_Read(txBuffer[3]);
	ADE7953_CS_HIGH();
}

void ADE7953_SPI_Write16(uint16_t Reg, uint16_t Value)
{
	uint8_t txBuffer[5] = {0, 0, 0, 0, 0};
	
	sortFrameWriteSPI_16(WRITE_SPI, Reg, Value, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	ADE7953_SPI_Read(txBuffer[3]);
	ADE7953_SPI_Read(txBuffer[4]);
	ADE7953_CS_HIGH();
}

void ADE7953_SPI_Write32(uint16_t Reg, uint32_t Value)
{
	uint8_t txBuffer[7] = {0, 0, 0, 0, 0, 0, 0};
	
	sortFrameWriteSPI_32(WRITE_SPI, Reg, Value, txBuffer);
	
	ADE7953_CS_LOW();	
	ADE7953_SPI_Read(txBuffer[0]);
	ADE7953_SPI_Read(txBuffer[1]);
	ADE7953_SPI_Read(txBuffer[2]);
	ADE7953_SPI_Read(txBuffer[3]);
	ADE7953_SPI_Read(txBuffer[4]);
	ADE7953_SPI_Read(txBuffer[5]);
	ADE7953_SPI_Read(txBuffer[6]);
	ADE7953_CS_HIGH();
}

//	return raw value of signed register
int32_t ADE7953_RegisterValue32_Signed(uint16_t reg, char *string, uint8_t print)
{
	int32_t buf32, sum=0;
	char stringValue[50];

	for(uint8_t i=0; i<50; i++)
	{	
		buf32 = ADE7953_SPI_Read32_Signed(reg);	
		if(signFlag == 1) buf32 = (~buf32)+1;
		
		sum = sum + buf32;
	}

	sum = sum/50.0;
	
	if(print == 1)
	{
		sprintf(stringValue, "%d", sum);	
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return sum;	
}

// return calculated value of 32-bit signed register
float ADE7953_CalculateRegisterValue32_Signed(uint16_t reg, char *string, char *string2, uint8_t print)
{
	int32_t buf32 = 0;
	float value = 0, constFactor = 0;
	char stringValue[50];
	
	buf32 = ADE7953_RegisterValue32_Signed(reg, "", 0);
		
	if ( reg == AVA_32 && buf32 > 70000 )
	{
		if(buf32 < 500) buf32 = 0;
		constFactor = ApparentConst;
	}
	
	else if ( reg == AVA_32 && buf32 < 70000 )
	{
		if(buf32 < 500) buf32 = 0;
		constFactor = ApparentConstMin;
	}
	
	else if (reg == AENERGYA_32)
	{
		USART_Puts(USART6, "AENERGYA: ");
		UsartInteger(USART6, buf32);
		USART_Puts(USART6, "\n");
		constFactor = ActiveEConst;	
	}
	else if (reg == AWATT_32 && buf32 < 70000) 
	{
		if(buf32 < 20) buf32 = 0;
		constFactor = ActiveConstMin; // * ADE7953_CalculateRegisterValue16_Signed(PFA, "cosFi", 0);
	}
	
	else if (reg == AWATT_32 && buf32 > 70000) 
	{
		if(buf32 < 20) buf32 = 0;
		constFactor = ActiveConst;// * ADE7953_CalculateRegisterValue16_Signed(PFA, "cosFi", 0);
	}
	
	else if (reg == AVAR_32)
	{
		if(buf32 <= -167000) buf32 = 0;
		constFactor = ReactiveConstMax * sin((3.14/180.0)*ADE7953_CalculateRegisterValue16_Signed(ANGLE_A, "", 0));
	}
		
	value = buf32 * constFactor;
		
	if(print == 1)
	{
		sprintf(stringValue, "%.3f", value);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, string2);
		USART_Puts(USART6, "\n");
	}
	
	return value;
}

// return raw value of 32-bit unsigned register
uint32_t ADE7953_RegisterValue32(uint16_t reg, char *string, uint8_t print)
{
	uint32_t buf32 = 0, sum=0;
	char stringValue[50];
	
	for(uint8_t i=0; i<50; i++)
	{
	
	buf32 = ADE7953_SPI_Read32(reg);
		sum = sum + buf32;
	}
	
	sum = sum/50.0;
		
	if(print == 1)
	{
		sprintf(stringValue, "%d", sum);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return sum;
}

// return calculated value of 32-bit unsigned register
float ADE7953_CalculateRegisterValue32(uint16_t reg, char *string, char *string2, uint8_t print)
{
	float value = 0, constFactor = 0;
	uint32_t buf32 = 0;
	char stringValue[50];
		
	buf32 = ADE7953_RegisterValue32(reg, "", 0);
	
	if (reg == IRMSA_32)
	{
		if (buf32 < 2600) buf32 = 0;
		constFactor = IConst;
	}	
	
	else if (reg == VRMS_32) 
	{
		if(buf32 < 2600) buf32 = 0;
		constFactor = UConst;
	}
	
	value = buf32 * constFactor;
	
	if(print == 1)
	{
		sprintf(stringValue, "%.2f", value);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, string2);
		USART_Puts(USART6, "\n");
	}
	
	return value;
}

// return raw value of 8-bit unsigned register
uint8_t ADE7953_RegisterValue8(uint16_t reg, char *string, uint8_t print)
{
	uint8_t buf8u;
	char stringValue[50];

	buf8u = ADE7953_SPI_Read8(reg);
	
	if(print == 1)
	{
		sprintf(stringValue, "%d", buf8u);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return buf8u;
}

// return raw value of 16-bit unsigned register
uint16_t ADE7953_RegisterValue16(uint16_t reg, char *string, uint8_t print)
{
	uint16_t buf16u;
	char stringValue[50];

	buf16u = ADE7953_SPI_Read16(reg);
	
	if(print == 1)
	{
		sprintf(stringValue, "%d", buf16u);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return buf16u;
}

// return raw value of 16-bit signed register
int16_t ADE7953_RegisterValue16_Signed(uint16_t reg, char *string, uint8_t print)
{
	int16_t buf16, buf16Real;
	char stringValue[50];
	
	buf16 = ADE7953_SPI_Read16(reg);
		
	if((buf16 & 0x8000) == 1) buf16Real = (~buf16)+1;
	else buf16Real = buf16;
	
	if (print == 1)
	{
		sprintf(stringValue, "%d", buf16Real);	
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return buf16Real;
}

// return calculated value of 16-bit signed register
float ADE7953_CalculateRegisterValue16_Signed(uint16_t reg, char *string, uint8_t print)
{
	int16_t buf16;
	float value = 0, constFactor = 0;
	char stringValue[50];
	
	buf16 = ADE7953_RegisterValue16_Signed(reg, "", 0);
	
	if(reg == PFA) constFactor = PowerFConst;
	else if (reg == ANGLE_A) constFactor = AngleConst;
		
	value = buf16 * constFactor;
	
	if(reg == PFA && value < 0) value = value * (-1);
		
	if(print == 1)
	{
		sprintf(stringValue, "%.2f", value);
		USART_Puts(USART6, string);
		USART_Puts(USART6, stringValue);
		USART_Puts(USART6, "\n");
	}
	
	return value;
}

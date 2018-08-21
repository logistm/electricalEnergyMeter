#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "ade7953_reg.h"
#include <string.h>

void EspSendToEmoncms(char *string, float value);
void EspSendJson(float Current, float Voltage);
void EspSendCSVToEmoncms(float voltage, float current, float activeP, float apparentP, 
												 float powerF, float wh, float sumWh, float sumBill);
void EspUpdateTime(void);
void EspChechTime(void);
void espCheckConnection(void);

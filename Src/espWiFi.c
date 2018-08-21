#include "espWiFi.h"

// send value to emoncms
void EspSendToEmoncms(char *string, float value)
{
	
	char cmd[150];
	char buff1[10];
	
	sprintf(buff1, "%.2f", value);
	
	USART_Puts(USART2, "AT+CIPSTART=\"TCP\",\"80.243.190.58\",80\r\n");
	HAL_Delay(20);
	USART_Puts(USART2,"AT+CIPSEND=90\r\n");
	HAL_Delay(20);
	
	strcpy(cmd, "GET /emoncms/input/post.json?json={");	
	strcat(cmd, string);
	strcat(cmd, ":");
	strcat(cmd, buff1);
	strcat(cmd, "}&apikey=aa134bf0257f5326d3fc2e689f27575e");
	strcat(cmd, "\r\n\r\n");
	
	USART_Puts(USART2, cmd);
	HAL_Delay(250);
	
//	USART_Puts(USART2, "AT+CIPCLOSE\r\n");
	
}

// send CSV format value to emoncms

void EspSendCSVToEmoncms(float voltage, float current, float activeP, float apparentP, 
												 float powerF, float wh, float sumWh, float sumBill)
{
	char cmd[200];
	char buff1[10], buff2[10], buff3[10], buff4[10], buff5[10], buff6[10], buff7[10], buff8[10];
	
	sprintf(buff1, "%.2f", voltage);
	sprintf(buff2, "%.2f", current);
	sprintf(buff3, "%.2f", activeP);
	sprintf(buff4, "%.2f", apparentP);
	sprintf(buff5, "%.2f", powerF);
	sprintf(buff6, "%.2f", wh);
	sprintf(buff7, "%.2f", sumWh);
	sprintf(buff8, "%.2f", sumBill);
	
	USART_Puts(USART2, "AT+CIPSTART=\"TCP\",\"80.243.190.58\",80\r\n");
	HAL_Delay(20);
	USART_Puts(USART2,"AT+CIPSEND=200\r\n");
	HAL_Delay(20);
	
	strcpy(cmd, "GET /input/post.json?csv=");	
	strcat(cmd, buff1);
	strcat(cmd, ",");
	strcat(cmd, buff2);
	strcat(cmd, ",");
	strcat(cmd, buff3);
	strcat(cmd, ",");
	strcat(cmd, buff4);
	strcat(cmd, ",");
	strcat(cmd, buff5);
	strcat(cmd, ",");
	strcat(cmd, buff6);
	strcat(cmd, ",");
	strcat(cmd, buff7);
	strcat(cmd, ",");
	strcat(cmd, buff8);
	strcat(cmd, "&apikey=aa134bf0257f5326d3fc2e689f27575e");
	strcat(cmd, " HTTP/1.1\r\n");
	strcat(cmd, "Host: emoncms.org\r\n");
	strcat(cmd, "Connection: close\r\n\r\n");
	strcat(cmd, "\r\n\r\n");
	
	USART_Puts(USART2, cmd);
	HAL_Delay(250);
	
}

void EspSendJson(float Current, float Voltage)
{
	char cmd[200];
	char buff1[10];
	char buff2[10];
	
	sprintf(buff1, "%.2f", Current);
	sprintf(buff2, "%.2f", Voltage);
	
	USART_Puts(USART2, "AT+CIPSTART=\"TCP\",\"80.243.190.58\",80\r\n");
	HAL_Delay(20);
	USART_Puts(USART2,"AT+CIPSEND=200\r\n");
	HAL_Delay(20);
	
	strcpy(cmd, "GET /input/post.json?csv=");	
	strcat(cmd, buff1);
	strcat(cmd, ",");
	strcat(cmd, buff2);
	strcat(cmd, "&apikey=aa134bf0257f5326d3fc2e689f27575e");
	strcat(cmd, " HTTP/1.1\r\n");
	strcat(cmd, "Host: emoncms.org\r\n");
	strcat(cmd, "Connection: close\r\n\r\n");
	strcat(cmd, "\r\n\r\n");
	
	USART_Puts(USART2, cmd);
	HAL_Delay(1000);
}
													 
													 

// enable SNTP and configure UTC+2 time zone
void EspUpdateTime()
{
	uint8_t buffer[100];
	
	USART_Puts(USART6, "EspUpdateTime\n");
	USART_Puts(USART2, "AT+CIPSNTPCFG=1,2\r\n"); 
	
	HAL_UART_Receive(&huart2, buffer, sizeof(buffer), 100);
	
	USART_Puts(USART6, (char*)buffer);
}

// check SNTP time
void EspChechTime()
{
	uint8_t buffer[100];
	char ref[] = {"AT+CIPSNTPTIME?\r\n+CIPSNTPTIME:Thu Jan 01 00:00:00 1970\n\r\nOK\r\n"};
	
	USART_Puts(USART2, "AT+CIPSNTPTIME?\r\n");
	HAL_UART_Receive(&huart2, buffer, sizeof(buffer), 100);

	if(strncmp(ref, (char*)buffer, 55) == 0) EspUpdateTime();
	
	else
	{
		USART_Puts(USART6, "EspChechTime\n");
		USART_Puts(USART6, (char*)buffer);
	}
	
}

// check esp connection status
void espCheckConnection()
{
	char ref[] = {"STATUS:2"};
	uint8_t buffer[100];
	
	USART_Puts(USART2, "AT+CIPSTATUS\r\n");
	HAL_UART_Receive(&huart2, buffer, sizeof(buffer), 100);
	
	USART_Puts(USART6, (char*)buffer);
	
	if(strncmp((char*)buffer, ref, 8) == 0) USART_Puts(USART6, "\nESP connected!\n");
	else USART_Puts(USART6, "\nESP not connected!\n");
}


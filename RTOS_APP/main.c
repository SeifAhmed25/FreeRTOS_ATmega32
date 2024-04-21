#ifndef F_CPU

#define F_CPU 16000000UL // clock speed is 16MHz

#endif
#include "uart.h"
#include "LCD.h"
#include "board.h"
#include "Keypad.h"
#include "ADC.h"
#include <util/delay.h> 
/********************************		FreeRTOS Files Inclusion	**********************************/
#include "FreeRTOS.h" 
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

void system_init(void){
	Leds_AllInit();
	LCD_Init();
	LCD_DispStrXY(1,1,(u8*)"Res App: ");
	Key_Init();
	Uart_Init(9600);
	Uart_SendStr("Res App: ");
}
void T_T1(void* pvParam);
void T_T2(void* pvParam);
void T_T3(void* pvParam);

xSemaphoreHandle mResourceAvailability = NULL;
int main(void)
{
	system_init();
	mResourceAvailability = xSemaphoreCreateMutex();
	xTaskCreate(T_T1, NULL, 100, NULL, 1, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 2, NULL);
	/* xTaskCreate(T_T3, NULL, 100, NULL, 3, NULL); */ 
	vTaskStartScheduler();
	return 0;
}
void T_T1(void* pvParam){
	u8 key = 0; 
	while (1){
		if (xSemaphoreTake(mResourceAvailability,1000)){
			Uart_SendStr("AT+SMS\r\n");
			Uart_SendStr("AT+SMS\r\n");
			xSemaphoreGive(mResourceAvailability);
		}
	}
}
void T_T2(void* pvParam){
	while (1){ 
		if (xSemaphoreTake(mResourceAvailability,1000)){
			Uart_SendStr("AT+Server1\r\n");
			Uart_SendStr("AT+Server2\r\n");	
			xSemaphoreGive(mResourceAvailability); 
		}
		vTaskDelay(5);
	}
}
void T_T3(void* pvParam){
	while (1){

	}
}
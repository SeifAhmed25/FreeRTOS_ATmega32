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
	LCD_DispStrXY(1,1,(u8*)"System Initiated");
	Key_Init();
}
void T_T1(void* pvParam);
void T_T2(void* pvParam);
void T_T3(void* pvParam);

int main(void)
{
	system_init();
	xTaskCreate(T_T1, NULL, 100, NULL, 1, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 2, NULL);
	xTaskCreate(T_T3, NULL, 100, NULL, 3, NULL);
	vTaskStartScheduler();
	return 0;
}
void T_T1(void* pvParam){
	while (1){
		Led_Toggle(LED_YELLOW);
		vTaskDelay(1000);
	}
}
void T_T2(void* pvParam){
	while (1){
		Led_Toggle(LED_BLUE);
		vTaskDelay(1000);
	}
}
void T_T3(void* pvParam){
	while (1){
		Led_Toggle(LED_GREEN);
		vTaskDelay(1000);
	}
}
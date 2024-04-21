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

xSemaphoreHandle bsEventKeyPressed = NULL;
int main(void)
{
	system_init();
	bsEventKeyPressed = xSemaphoreCreateBinary();
	xTaskCreate(T_T1, NULL, 100, NULL, 2, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 3, NULL);
	xTaskCreate(T_T3, NULL, 100, NULL, 1, NULL); 
	vTaskStartScheduler();
	return 0;
}
void T_T1(void* pvParam){
	u8 key = 0; 
	while (1){
		key = Key_GetKey();
		if (key){
			xSemaphoreGive(bsEventKeyPressed);
		}
		vTaskDelay(50);
	}
}
void T_T2(void* pvParam){
	while (1){
		if (xSemaphoreTake(bsEventKeyPressed,1000)){;
			Led_Toggle(LED_BLUE);
		}
	}
}
void T_T3(void* pvParam){
	while (1){
		Led_Toggle(LED_GREEN);
		vTaskDelay(300);
	}
}
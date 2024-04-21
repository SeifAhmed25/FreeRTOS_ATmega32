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

QueueHandle_t mqUart = NULL; 
int main(void)
{
	system_init();
	mqUart = xQueueCreate(5, 11);  /*Queue Length and Max item size*/
	xTaskCreate(T_T1, NULL, 100, NULL, 1, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 2, NULL); 
	vTaskStartScheduler();
	return 0;
}
void T_T1(void* pvParam){
	u8 u8Data = 0; 
	u8 u8Ind = 0;
	u8 txMsg[11]; 
	while (1){
		if (Uart_ReceiveByte_unblock(&u8Data)){ /*End of Receiving*/
			if (u8Data == 0){
				txMsg[u8Ind] = 0;  
				u8Ind = 0; 
				xQueueSend (mqUart, txMsg, portMAX_DELAY); 
			}
			else{ /*Still receiving bytes*/
				txMsg [u8Ind] = u8Data; 
				u8Ind++;	
			}
		}
	}
}
void T_T2(void* pvParam){ 
	u8 rxMsg[11]; 
	while (1){ 
		if (xQueueReceive(mqUart, rxMsg, portMAX_DELAY)){
			Uart_SendStr(rxMsg);
		}
	}
}
void T_T3(void* pvParam){
	while (1){

	}
}
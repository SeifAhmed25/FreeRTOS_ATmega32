#ifndef F_CPU
#define F_CPU 16000000UL // Clock speed is 16MHz
#endif

#include "uart.h"
#include "LCD.h"
#include "board.h"
#include "Keypad.h"
#include "ADC.h"
#include <util/delay.h>

/******************************** FreeRTOS Files Inclusion **********************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

// Function prototypes
void system_init(void);
void T_T1(void* pvParam);
void T_T2(void* pvParam);
void T_T3(void* pvParam);


QueueHandle_t mqUart = NULL;	/*Declare a variable of Queue Type and initialize with null*/
#define MaxQueueLength		5
#define MaxItemSize			11  /* In Bytes */

int main(void)
{
	system_init();
	mqUart = xQueueCreate(MaxQueueLength,MaxItemSize);
	xTaskCreate(T_T1, NULL, 100, NULL, 1, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 2, NULL);
	vTaskStartScheduler();
	return 0;
}

void system_init(void)
{
	Leds_AllInit();
	LCD_Init();
	LCD_DispStrXY(1, 1, (u8*)"Res App: ");
	Key_Init();
	Uart_Init(9600);
	Uart_SendStr("Res App: ");
}

/*****************************		Task to recieve string and push it to queue		*************************/
void T_T1(void* pvParam)
{
	u8 u8Data = 0; /* receive data in from UART data register */
	u8 u8Ind = 0;  /* keep track of array index */
	u8 txMsg[11];  /* array to store receiving message */
	while (1)
	{
		if (Uart_ReceiveByte_unblock(&u8Data)) 
		{
			if (u8Data == NULL)/* Receiving a Null Data Represents the end of Receiving */ 
			{	
				txMsg[u8Ind] = 0;
				u8Ind = 0;
				xQueueSend(mqUart, txMsg, portMAX_DELAY);
			}
			else /* Still receiving data */
			{
				txMsg[u8Ind] = u8Data;
				u8Ind++;
			}
		}
	}
}

/******************		Task to Read Data from Queue and send it by UART	***************/
void T_T2(void* pvParam)
{
	u8 rxMsg[11]; /* Array to store data from Queue */
	while (1)
	{
		if (xQueueReceive(mqUart, rxMsg, portMAX_DELAY))
		{
			Uart_SendStr(rxMsg);
		}
	}
}

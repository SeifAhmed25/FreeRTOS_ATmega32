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

int main(void)
{
	// Initialize system components
	system_init();

	// Create tasks
	xTaskCreate(T_T1, NULL, 100, NULL, 1, NULL);
	xTaskCreate(T_T2, NULL, 100, NULL, 2, NULL);
	xTaskCreate(T_T3, NULL, 100, NULL, 3, NULL);

	// Start the FreeRTOS scheduler
	vTaskStartScheduler();

	return 0;
}

// System initialization function
void system_init(void)
{
	Leds_AllInit(); // Initialize LEDs
	LCD_Init();     // Initialize LCD
	LCD_DispStrXY(1, 1, (u8*)"System Initiated"); // Display initialization message on LCD
	Key_Init();     // Initialize Keypad
}

// Task T_T1 function
void T_T1(void* pvParam)
{
	while (1)
	{
		Led_Toggle(LED_YELLOW); // Toggle Yellow LED
		vTaskDelay(1000);       // Delay for 1000 milliseconds (1 second)
	}
}

// Task T_T2 function
void T_T2(void* pvParam)
{
	while (1)
	{
		Led_Toggle(LED_BLUE);   // Toggle Blue LED
		vTaskDelay(1000);       // Delay for 1000 milliseconds (1 second)
	}
}

// Task T_T3 function
void T_T3(void* pvParam)
{
	while (1)
	{
		Led_Toggle(LED_GREEN);  // Toggle Green LED
		vTaskDelay(1000);       // Delay for 1000 milliseconds (1 second)
	}
}

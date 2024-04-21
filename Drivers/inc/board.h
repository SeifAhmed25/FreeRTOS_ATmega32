/*
 * board.h
 *
 * Created: 8/10/2021 1:31:39 PM
 *  Author: MahmoudH
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#include "includes.h"

/* CFG Area - LEDs*/
#define LEDS_PORT			PORTA
#define LEDS_DDR			DDRA
#define LEDS_MSK			0x70

/* CFG Area - Buzzer*/
#define BUZ_PORT			PORTC
#define BUZ_DDR				DDRC
#define BUZ_PIN				PC6


typedef enum{
	LED_GREEN = 4, LED_BLUE, LED_YELLOW
}Led_Num;

/* Led */
void Led_Init(Led_Num ledNo);
void Led_On(Led_Num ledNo);
void Led_Off(Led_Num ledNo);
void Led_Toggle(Led_Num ledNo);

/* Leds */
void Leds_Init(u8 ledMask);
void Leds_On(u8 ledMask);
void Leds_Off(u8 ledMask);
void Leds_Toggle(u8 ledMask);

/* All leds */
void Leds_AllInit(void);
void Leds_AllOn(void);
void Leds_AllOff(void);
void Leds_AllToggle(void);

/* Buzzer */
void Buz_Init(void);
void Buz_On(void);
void Buz_Off(void);
void Buz_Toggle(void);

#endif /* BOARD_H_ */

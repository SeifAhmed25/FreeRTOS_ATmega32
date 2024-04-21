/*
* board.c
*
* Created: 8/10/2021 1:33:35 PM
*  Author: MahmoudH
*/
#include "board.h"

/* Led */
void Led_Init(Led_Num ledNo){
	setBit(LEDS_DDR,ledNo);
	Led_Off(ledNo);
}
void Led_On(Led_Num ledNo){
	setBit(LEDS_PORT,ledNo);
}
void Led_Off(Led_Num ledNo){
	clearBit(LEDS_PORT,ledNo);
}
void Led_Toggle(Led_Num ledNo){
	toggleBit(LEDS_PORT,ledNo);
}

/* Leds */
void Leds_Init(u8 ledMask){
	setBits(LEDS_DDR,ledMask);
	Leds_Off(ledMask);
}
void Leds_On(u8 ledMask){
	setBits(LEDS_PORT,ledMask);
}
void Leds_Off(u8 ledMask){
	clearBits(LEDS_PORT,ledMask);
}
void Leds_Toggle(u8 ledMask){
	toggleBits(LEDS_PORT,ledMask);
}

/* All leds */
void Leds_AllInit(void){
	Leds_Init(LEDS_MSK);
	Leds_AllOff();
}
void Leds_AllOn(void){
	Leds_On(LEDS_MSK);
}
void Leds_AllOff(void){
	Leds_Off(LEDS_MSK);
}
void Leds_AllToggle(void){
	Leds_Toggle(LEDS_MSK);
}

/* Buzzer */
void Buz_Init(void){
	setBit(BUZ_DDR, BUZ_PIN);
	Buz_Off();
}
void Buz_On(void){
	setBit(BUZ_PORT, BUZ_PIN);
}
void Buz_Off(void){
	clearBit(BUZ_PORT, BUZ_PIN);
}
void Buz_Toggle(void){
	toggleBit(BUZ_PORT, BUZ_PIN);
}

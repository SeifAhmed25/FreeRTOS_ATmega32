/*
 * Keypad.h
 *
 * Created: 8/12/2021 10:44:04 AM
 *  Author: MahmoudH
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "includes.h"

/* CFG */
#define KEY_ROW_PORT		PORTC
#define KEY_ROW_DDR			DDRC
#define KEY_ROW_INR			PINC

#define KEY_COL_PORT		PORTD
#define KEY_COL_DDR			DDRD
#define KEY_COL_PINR		PIND

#define KEY_ROWS_MSK	0x1C
#define KEY_COLS_MSK	0xE0

#define KEY_ROWS_NUM	3
#define KEY_COLS_NUM	3

/* Routines */
void	Key_Init(void);
u8		Key_GetKey(void);
u16		Key_Scan(void);


#endif /* KEYPAD_H_ */

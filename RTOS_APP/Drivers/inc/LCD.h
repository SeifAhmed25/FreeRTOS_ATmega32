/*
 * LCD.h
 *
 * Created: 8/15/2021 12:18:58 PM
 *  Author: MahmoudH
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "includes.h"
#include "stdio.h"
/* CFG */
#define	LCD_DATA_PORT			PORTB
#define LCD_DATA_DDR			DDRB

#define	LCD_CTRL_PORT			PORTA
#define LCD_CTRL_DDR			DDRA

#define LCD_DATA_MSK1	0x07
#define LCD_DATA_MSK2	0x10
#define LCD_CTRL_MSK	0x0C

#define LCD_CTRL_RS		PA3
#define LCD_CTRL_EN		PA2
 
/* CMDs */
#define CMD_CLEAR		0x01
#define CMD_RET_HOME	0x02
#define CMD_ENTRY_MODE	0x06
#define CMD_DISP_ON		0x0C
#define CMD_FUN_SET		0x28

#define CMD_SET_CGRAM_ADD_MSK		0x40 // add address
#define CMD_SET_DDRAM_ADD_MSK		0x80 // add address

/* Routines */


void LCD_RetHome(void);
void LCD_Clear(void);
void LCD_Init(void);

void LCD_DispChar(u8 data);
void LCD_DispCharXY(u8 row, u8 col, u8 data);
void LCD_DispStr(u8* str);
void LCD_DispStrXY(u8 row, u8 col, u8* str);

void LCD_DispInt(u32 intValue);
void LCD_DispIntXY(u8 row, u8 col, u32 intValue);

void LCD_DispHex(u32 intValue);
void LCD_DispHexXY(u8 row, u8 col, u32 intValue);

#endif /* LCD_H_ */

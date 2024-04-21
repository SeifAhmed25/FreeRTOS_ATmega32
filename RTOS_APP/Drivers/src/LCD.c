/*
 * LCD.h
 *
 * Created: 8/15/2021 12:19:19 PM
 *  Author: MahmoudH
 */ 
#include "LCD.h"

static void LCD_SendCMD(u8 cmd);
static void LCD_SendData(u8 data);
static void LCD_GotoXY(u8 row, u8 col);
static void LCD_Latch(void);

static void LCD_Latch(void){
	/* set and clear EN */
	setBit(LCD_CTRL_PORT,LCD_CTRL_EN);
	_delay_us(1);
	clearBit(LCD_CTRL_PORT,LCD_CTRL_EN);
}

static void LCD_SendCMD(u8 cmd){
	clearBit(LCD_CTRL_PORT,LCD_CTRL_RS); /* select instruction mode */
	/* send high N -> set most 4 bit and (set and clear enable) */
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK1);
	setBits(LCD_DATA_PORT, ((cmd>>4)&LCD_DATA_MSK1));
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK2);
	setBits(LCD_DATA_PORT, (((cmd>>4)<<1)&LCD_DATA_MSK2));
	LCD_Latch();
	/* send low N -> set least 4 bit and (set and clear enable) */
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK1);
	setBits(LCD_DATA_PORT, ((cmd)&LCD_DATA_MSK1));
	clearBits(LCD_DATA_PORT, LCD_DATA_MSK2);
	setBits(LCD_DATA_PORT, (((cmd) << 1 )&LCD_DATA_MSK2));
	LCD_Latch();
	
	_delay_us(40);/* wait for command to be executed - 40 us */
}
static void LCD_SendData(u8 data){
		setBit(LCD_CTRL_PORT,LCD_CTRL_RS); /* select data mode */
		/* send high N -> set most 4 bit and (set and clear enable) */
		clearBits(LCD_DATA_PORT, LCD_DATA_MSK1);
		setBits(LCD_DATA_PORT, ((data>>4)&LCD_DATA_MSK1));
		clearBits(LCD_DATA_PORT, LCD_DATA_MSK2);
		setBits(LCD_DATA_PORT, (((data>>4)<<1)&LCD_DATA_MSK2));
		LCD_Latch();
		/* send low N -> set least 4 bit and (set and clear enable) */
		clearBits(LCD_DATA_PORT, LCD_DATA_MSK1);
		setBits(LCD_DATA_PORT, ((data)&LCD_DATA_MSK1));
		clearBits(LCD_DATA_PORT, LCD_DATA_MSK2);
		setBits(LCD_DATA_PORT, (((data) << 1 )&LCD_DATA_MSK2));
		LCD_Latch();
		
		_delay_us(40);/* wait for write data command to be executed - 40 us */
}
/* row: 1:2, col:1:16  */
static void LCD_GotoXY(u8 row, u8 col){
	/*if(row == 1){
		LCD_SendCMD(CMD_SET_DDRAM_ADD_MSK + 0x00 + col - 1);
	}
	else if(row == 2){
		LCD_SendCMD(CMD_SET_DDRAM_ADD_MSK + 0x40 + col - 1);
	}*/
		LCD_SendCMD(CMD_SET_DDRAM_ADD_MSK + (row-1)*0x40 + col - 1);

}
void LCD_RetHome(void){
	LCD_SendCMD(CMD_RET_HOME);
	_delay_ms(5);
}
void LCD_Clear(void){
	LCD_SendCMD(CMD_CLEAR);
	_delay_ms(5);	
}
void LCD_Init(void){
	/* LCD Pins -> Out */
	setBits(LCD_DATA_DDR,LCD_DATA_MSK1);
	setBits(LCD_DATA_DDR,LCD_DATA_MSK2);
	setBit(LCD_CTRL_DDR,LCD_CTRL_RS);
	setBit(LCD_CTRL_DDR,LCD_CTRL_EN);
	_delay_ms(20);
	LCD_RetHome();
	LCD_SendCMD(CMD_FUN_SET);
	LCD_SendCMD(CMD_DISP_ON);
	LCD_SendCMD(CMD_ENTRY_MODE);
	LCD_Clear();
}

void LCD_DispChar(u8 data){
	LCD_SendData(data);
}
void LCD_DispCharXY(u8 row, u8 col, u8 data){
	LCD_GotoXY(row,col);
	LCD_DispChar(data);
}
void LCD_DispStr(u8* str){
	u8 i = 0;	while(str[i] != 0)	{		LCD_DispChar(str[i]);		i++;	}
}
void LCD_DispStrXY(u8 row, u8 col, u8* str){
		LCD_GotoXY(row,col);
		LCD_DispStr(str);
}

void LCD_DispInt(u32 intValue){
	u8 tempStr[11] = {0};
	sprintf(tempStr, "%u",intValue);	LCD_DispStr(tempStr);
}
void LCD_DispHex(u32 intValue){
	u8 tempStr[11] = {0};
	sprintf(tempStr, "%x",intValue);	LCD_DispStr(tempStr);
}
void LCD_DispHexXY(u8 row, u8 col, u32 intValue){
	LCD_GotoXY(row,col);
	LCD_DispHex(intValue);
}
void LCD_DispIntXY(u8 row, u8 col, u32 intValue){
		LCD_GotoXY(row,col);
		LCD_DispInt(intValue);
}
void LCD_Fun(void){
	LCD_SendCMD(CMD_SET_CGRAM_ADD_MSK + 7*8);


	LCD_SendData(0b00011111);
	LCD_SendData(0b00011111);
	LCD_SendData(0b00011111);
	LCD_SendData(0b00000000);
	LCD_SendData(0b00011111);
	LCD_SendData(0b00011111);
	LCD_SendData(0b00011111);
	LCD_SendData(0b00000000);
	_delay_ms(10);
	LCD_GotoXY(1,1);
}

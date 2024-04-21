/*
 * Keypad.c
 *
 * Created: 8/12/2021 10:44:18 AM
 *  Author: MahmoudH
 */

#include "Keypad.h"

static const u8 keys[KEY_ROWS_NUM][KEY_COLS_NUM]= {
		{9,8,7},
		{6,5,4},
		{3,2,1}
};

/* Routines */
void	Key_Init(void){
	/* Rows */
	setBits(KEY_ROW_DDR, KEY_ROWS_MSK);		/* Out */
	setBits(KEY_ROW_PORT, KEY_ROWS_MSK);	/* High Default */
	/* Cols */
	clearBits(KEY_COL_DDR, KEY_COLS_MSK);	/* In */
	setBits(KEY_COL_PORT, KEY_COLS_MSK);	/* Pullup */
}
u8		Key_GetKey(void){
	/*
	for each row r
	activate this row r
	for each col c
	if c activated
	get and return the pressed key by r, and c
	end
	end
	de-activate this row r
	end
	return 0 for no pressed key
	 */
	u8 row = 0;
	u8 col = 0;
	setBits(KEY_ROW_PORT, KEY_ROWS_MSK);	/* High Default */
	for (row = 0; row < KEY_ROWS_NUM; row++)
	{
		clearBit(KEY_ROW_PORT,row+2);
		for (col = 0; col < (KEY_COLS_NUM); col++)
		{
			if(!readBit(KEY_COL_PINR, col + 5 )){
				while(!readBit(KEY_COL_PINR, col + 5)); // Blocking
				return keys[row][col];
			}
		}
		setBit(KEY_ROW_PORT,row+2);
	}
	return 0;
}

u16		Key_Scan(void){
	u16 keys = 0x00;
	u8 row = 0;
	u8 col = 0;
	for (row = 0; row < KEY_ROWS_NUM; row++)
	{
		clearBit(KEY_ROW_PORT,row);
		for (col = 0; col < KEY_COLS_NUM; col++)
		{
			if(!readBit(KEY_COL_PINR, col + KEY_ROWS_NUM )){
				//while(!readBit(KEY_PINR, col + KEY_ROWS_NUM )); // Blocking
				//return keys[row][col];
				keys |= (1<<(col + row*4));
			}
		}
		setBit(KEY_ROW_PORT,row);
	}
	return keys;
}


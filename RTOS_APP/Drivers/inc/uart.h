/*
 * uart.h
 *
 * Created: 8/19/2021 10:07:53 AM
 *  Author: MahmoudH
 */ 


#ifndef UART_H_
#define UART_H_

#include "includes.h"

/*typedef struct{
	u32 baudrate; //
	u8 stopBits; //
	u8 dataBits; //
	u8 parityBit; // 
}UART_Struct;
*/
//void	Uart_Init(UART_Struct* pUart);
void	Uart_Init(u32 baudrate);
void	Uart_SendByte(u8 data);
u8		Uart_ReceiveByte(void);
Bool	Uart_ReceiveByte_unblock(u8* pData);

void	Uart_SendStr(u8* str);


#endif /* UART_H_ */
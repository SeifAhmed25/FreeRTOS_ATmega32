/*
 * uart.c
 *
 * Created: 8/19/2021 10:08:13 AM
 *  Author: MahmoudH
 */ 
#include "uart.h"

void	Uart_Init(u32 baudrate){
	u16 baud = (F_CPU)/((16UL*baudrate)-1);
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}
void	Uart_SendByte(u8 data){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}
u8		Uart_ReceiveByte(void){
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}
Bool	Uart_ReceiveByte_unblock(u8* pData){
	Bool result = FALSE;
	if ( UCSRA & (1<<RXC) ){
		(*pData) = UDR;
		result =  TRUE;		
	}
	else{
		result = FALSE;
	}
	return result;
}

void	Uart_SendStr(u8* str){
	u32 ind = 0;
	while(str[ind] != 0){
		Uart_SendByte(str[ind]);
		ind++;
	}
}
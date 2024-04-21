/*
 * ADC.c
 *
 * Created: 8/16/2021 1:05:20 PM
 *  Author: MahmoudH
 */ 

#include "ADC.h"

void	ADC_Init(void){
	/*
		Clock/128 - Vref = AVcc - Enable - 
	*/
	/* Clock/128 */
	setBit(ADCSRA,ADPS0);
	setBit(ADCSRA,ADPS1);
	setBit(ADCSRA,ADPS2);
	/* Vref = AVcc */
	setBit(ADMUX, REFS0);
	clearBit(ADMUX, REFS1);
	/* Enable */
	setBit(ADCSRA,ADEN);
}
/* 0 - > 7 */
u16		ADC_Read(ADC_CH channelNo){
	/* Select Channel */
	clearBits(ADMUX, 0x1F);
	setBits(ADMUX, channelNo);
	/* Start Conversion */
	setBit(ADCSRA,ADSC);
	/* Wait for conversion to complete */
	//while(readBit(ADCSRA,ADSC));
	while(readBit(ADCSRA,ADIF));
	setBit(ADCSRA,ADIF);
	/* return data */
	return ADC;
}

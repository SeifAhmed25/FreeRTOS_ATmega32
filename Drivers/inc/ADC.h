/*
 * ADC.h
 *
 * Created: 8/16/2021 1:04:58 PM
 *  Author: MahmoudH
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "includes.h"

typedef enum{
	ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7
}ADC_CH;

void	ADC_Init(void);
u16		ADC_Read(u8 channelNo);



#endif /* ADC_H_ */
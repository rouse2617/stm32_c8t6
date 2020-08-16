#ifndef __MQ_9_H
#define __MQ_9_H
#include "delay.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
void ADCx_Init(void);
u16 Get_ADC_Value(u8 ch,u8 times);
#endif

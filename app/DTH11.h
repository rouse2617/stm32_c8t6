#ifndef __DTH11_H
#define __DTH11_H 
#include "delay.h"
#include "stm32f10x.h"


#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOC
#define DHT11_PIN     GPIO_Pin_14                  
#define DHT11_PORT		GPIOC 

//���κ꣬��������������һ��ʹ��,����ߵ�ƽ��͵�ƽ
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_14)
 //��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)

typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);

#endif
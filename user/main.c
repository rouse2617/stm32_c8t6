//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ��������ԭ��ս�� STM32������/mini������
//1.8��SPI����TFTҺ������
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtech.net
//�Ա���վ��http://qdtech.taobao.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:QDtech2008@gmail.com 
//Skype:QDtech2008
//��������:2013/5/13
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "DTH11.h"
#include "usart.h"
#include "MQ_9.h"

DHT11_Data_TypeDef DHT11_Data;

void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	//ѡ���Ӧ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 // �ر�����LED
}


int main(void)
{
	char buf[100] ;
	int i = 0;
	float val;
	SystemInit();	//System init.
	delay_init(72);//Delay init.
	LED_GPIO_Config();
	Lcd_Init();
	DHT11_GPIO_Config();
	ADCx_Init();
	Lcd_Clear(BLACK);
	USART1_Init(9600);
	while(1)
{  
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
		{
			printf("{\"h\":\"%d\",\"t\":\"%d\"} ",DHT11_Data.humi_int,DHT11_Data.temp_int);
			delay_ms(1500);		/* 1s ��ȡһ���¶�ֵ */
		}
		else
		{
		//printf("Read DHT11 ERROR!\r\n");//��ȡ����ʧ�ܣ����ڴ�ӡ��Read DHT11 ERROR.
			
		}
	//sprintf(buf,"%d %,  %d ",DHT11_Data.humi_int,DHT11_Data.temp_int);
	//Gui_DrawFont_GBK16(16,12,BLUE,YELLOW,buf);
		val=Get_ADC_Value(ADC_Channel_1,20);
		val=(float)val*(3.3/4096);
		printf("%f\n",val);
		sprintf(buf,"co: %0.3f  \n",val);
		Gui_DrawFont_GBK16(0,30,BLUE,YELLOW,buf);
		
		Gui_DrawFont_GBK16(0,50,BLUE,YELLOW,"�¶�");

		
		Gui_DrawFont_Num32(40,45,BLUE,YELLOW,DHT11_Data.temp_int/10);
		Gui_DrawFont_Num32(65,45,BLUE,YELLOW,DHT11_Data.temp_int%10);

		Gui_DrawFont_Num32(90,45,BLUE,YELLOW,13);  //�¶ȷ��� --13

		Gui_DrawFont_GBK16(0,90,BLUE,YELLOW,"ʪ��");
		Gui_DrawFont_Num32(40,78,BLUE,YELLOW,DHT11_Data.humi_int/10);
		Gui_DrawFont_Num32(65,78,BLUE,YELLOW,DHT11_Data.humi_int%10);
		Gui_DrawFont_Num32(90,78,BLUE,YELLOW,12);  //�¶ȷ��� --13
		//	QDTFT_Test_Demo();	//See the test details in QDTFT_Demo.c		
	//  GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000); 

		delay_ms(2000); 

	//  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	//	printf("���\n");
}

}






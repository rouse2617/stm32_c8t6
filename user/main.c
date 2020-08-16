//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：正点原子战舰 STM32开发板/mini开发板
//1.8寸SPI串口TFT液晶驱动
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:QDtech2008@gmail.com 
//Skype:QDtech2008
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
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
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	//选择对应的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC端口
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 // 关闭所有LED
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
			delay_ms(1500);		/* 1s 读取一次温度值 */
		}
		else
		{
		//printf("Read DHT11 ERROR!\r\n");//读取数据失败，串口打印：Read DHT11 ERROR.
			
		}
	//sprintf(buf,"%d %,  %d ",DHT11_Data.humi_int,DHT11_Data.temp_int);
	//Gui_DrawFont_GBK16(16,12,BLUE,YELLOW,buf);
		val=Get_ADC_Value(ADC_Channel_1,20);
		val=(float)val*(3.3/4096);
		printf("%f\n",val);
		sprintf(buf,"co: %0.3f  \n",val);
		Gui_DrawFont_GBK16(0,30,BLUE,YELLOW,buf);
		
		Gui_DrawFont_GBK16(0,50,BLUE,YELLOW,"温度");

		
		Gui_DrawFont_Num32(40,45,BLUE,YELLOW,DHT11_Data.temp_int/10);
		Gui_DrawFont_Num32(65,45,BLUE,YELLOW,DHT11_Data.temp_int%10);

		Gui_DrawFont_Num32(90,45,BLUE,YELLOW,13);  //温度符号 --13

		Gui_DrawFont_GBK16(0,90,BLUE,YELLOW,"湿度");
		Gui_DrawFont_Num32(40,78,BLUE,YELLOW,DHT11_Data.humi_int/10);
		Gui_DrawFont_Num32(65,78,BLUE,YELLOW,DHT11_Data.humi_int%10);
		Gui_DrawFont_Num32(90,78,BLUE,YELLOW,12);  //温度符号 --13
		//	QDTFT_Test_Demo();	//See the test details in QDTFT_Demo.c		
	//  GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000); 

		delay_ms(2000); 

	//  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	//	printf("你好\n");
}

}






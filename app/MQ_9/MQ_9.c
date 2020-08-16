#include "MQ_9.h"
void ADCx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);// 设 置 ADC 分 频 因 子 6 72M/6=12,ADC 最大时间不能超过 14M
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//ADC
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN; //模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//禁止触发检测， 使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;//1 个转换在规则序列中也就是只转换规则序列 1
	ADC_Init(ADC1, &ADC_InitStructure);//ADC 初始化
	ADC_Cmd(ADC1, ENABLE);//开启 AD 转换器
	ADC_ResetCalibration(ADC1);//重置指定的 ADC 的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//获取 ADC 重置校准寄存器的状态
	ADC_StartCalibration(ADC1);//开始指定 ADC 的校准状态
	while(ADC_GetCalibrationStatus(ADC1));//获取指定 ADC 的校准程序
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的 ADC的软件转换启动功能
}
u16 Get_ADC_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
//设置指定 ADC 的规则组通道， 一个序列， 采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1,
	ADC_SampleTime_239Cycles5); //ADC1,ADC 通道,239.5 个周期,提高采样时间可以提高精确度
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的 ADC1 的软件转换启动功能
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	} 
	return temp_val/times;

}
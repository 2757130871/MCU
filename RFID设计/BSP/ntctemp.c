#include "ntctemp.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "misc.h"
#include "stm32f10x_dma.h"

volatile unsigned int  ADC_Buf[NUMSAMP+1];  //���¶Ȳɼ�ֵ
volatile unsigned int  ADC_BufCnt=0;    //�ɼ�����
//ADC buff
__IO u32 ADC_ConvertedValue[2];

 /**************************************************************************************
 * ��  �� : ��ʼ��ADC1
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void ADC1_Init(void)
{
	#define ADC1_DR_Address    ((u32)0x4001244C)
	ADC_InitTypeDef 				ADC_InitStructure;
	GPIO_InitTypeDef        GPIO_InitStructure;
	DMA_InitTypeDef         DMA_InitStructure;

	/* Enable the PWR/BKP Clock */
	//��DMAʱ�� ����ADCģʽ
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);        /* use for adc model */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	
	//��������� PB0 PB1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		//DMAͨ������ 
	DMA_DeInit(DMA1_Channel1);									
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; 
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 2;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);   //ʹ��DMAͨ��1
	DMA_Cmd(DMA1_Channel1, ENABLE);	
	
		//ADCģʽ����
		ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);				
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_13Cycles5);
		ADC_DMACmd(ADC1, ENABLE);
		ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult; 
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC2, &ADC_InitStructure);	
		ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 1, ADC_SampleTime_13Cycles5);
		ADC_DMACmd(ADC2, ENABLE);
		//ʹ��ADC1
		ADC_Cmd(ADC1, ENABLE);	 
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));	    //Enable ADC1 reset calibaration register    
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));	        //Start ADC1 calibaration  
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);		      //Start ADC1 Software Conversion
		//ʹ��ADC2
		ADC_Cmd(ADC2, ENABLE);
		ADC_ResetCalibration(ADC2);
		while(ADC_GetResetCalibrationStatus(ADC2));
		ADC_StartCalibration(ADC2);
		while(ADC_GetCalibrationStatus(ADC2));
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

//��ADC���ֵ ADCֵ��Χ0~255 
u8 ADCGet(u8 channel)
{
		if(!channel)
			//PB0 ADֵ
			return (u8)(ADC_ConvertedValue[0]>>4);
		else
			//PB1 ADֵ
			return (u8)(ADC_ConvertedValue[0]>>20);
}


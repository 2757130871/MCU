#ifndef __DHT11_H
#define	__DHT11_H
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"

#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOA
#define DHT11_PIN     GPIO_Pin_4                 
#define DHT11_PORT		GPIOA 

//���κ꣬��������������һ��ʹ��,����ߵ�ƽ��͵�ƽ
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_4)
 //��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN()	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

typedef struct
{
	u8  humi_int;		//ʪ�ȵ���������
	u8  humi_deci;	 	//ʪ�ȵ�С������
	u8  temp_int;	 	//�¶ȵ���������
	u8  temp_deci;	 	//�¶ȵ�С������
	u8  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
u8 Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static u8 Read_Byte(void);

#endif /* __DHT11_H */

/********************  ********************
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨������STM32F103C8T6

 *          |   PB15 - LED1   |
 *          |   PB14 - LED2   |
*********************************************************/
#include "led.h"


 /***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB�˿�
  GPIO_ResetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15 );	 // �ر����м̵���
	GPIO_SetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 );	 // �ر����г�ЧӦ��
	GPIO_ResetBits(GPIOB,GPIO_Pin_12 );	 // �ر����м̵���
	GPIO_SetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15 );	 // �ر����м̵���
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PB�˿�
	GPIO_SetBits(GPIOC,GPIO_Pin_13 );	 // �ر����г�ЧӦ��
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB�˿�
	GPIO_SetBits(GPIOA,GPIO_Pin_8 );	 // �ر����г�ЧӦ��
	GPIO_ResetBits(GPIOA,GPIO_Pin_8 );	 // �ر����м̵���
	
	
	//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //��������   
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //��������   
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //��������   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  //485 ͨѶ
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB�˿�
  MAX485_RX	;	 // 485 receive
	
}

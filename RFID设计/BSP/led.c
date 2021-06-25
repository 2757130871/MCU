/********************  ********************
 * 描述    ：led 应用函数库
 *          
 * 实验平台：基于STM32F103C8T6

 *          |   PB15 - LED1   |
 *          |   PB14 - LED2   |
*********************************************************/
#include "led.h"


 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
  GPIO_ResetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15 );	 // 关闭所有继电器
	GPIO_SetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 );	 // 关闭所有场效应管
	GPIO_ResetBits(GPIOB,GPIO_Pin_12 );	 // 关闭所有继电器
	GPIO_SetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15 );	 // 关闭所有继电器
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PB端口
	GPIO_SetBits(GPIOC,GPIO_Pin_13 );	 // 关闭所有场效应管
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
	GPIO_SetBits(GPIOA,GPIO_Pin_8 );	 // 关闭所有场效应管
	GPIO_ResetBits(GPIOA,GPIO_Pin_8 );	 // 关闭所有继电器
	
	
	//按键输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //浮空输入   
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //浮空输入   
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //浮空输入   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  //485 通讯
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
  MAX485_RX	;	 // 485 receive
	
}

/********************  ********************
 * 文件名  ：usart1.c
 * 描述    ：配置USART1         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
**********************************************************************************/

#include "usart.h"
#include <stdarg.h>
#include "stdio.h"
#include "misc.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0)
		; //循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif

u8 Flag1=FALSE,Flag2=FALSE,Flag3=FALSE;
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
char RxCounter,RxBuffer[100]="xiaobawang";     //接收缓冲,最大USART_REC_LEN个字节.
char RxCounter2,RxBuffer2[100]="xiaobawang";     //接收缓冲,最大USART_REC_LEN个字节.
char RxCounter3,RxBuffer3[100]="xiaobawang";     //接收缓冲,最大USART_REC_LEN个字节.



void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/* 使能 USART1 时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  
	/* USART1 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	
	USART_Init(USART1, &USART_InitStructure);  //初始化USART1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);// USART1使能
}
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	/* 使能 USART2 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE); 
  USART_DeInit(USART2);          //将外设USART1寄存器重设为缺省值
	/* USART1 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	
	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  
	/* USART2 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 9600;	//波特率设置：
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);  //初始化USART2
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;         //设置SCLK引脚上时钟输出的极性为低电平
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;   //时钟第一个边沿进行数据捕获
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;  //最后一位数据的时钟脉冲不从SCLK输出
  USART_ClockInit(USART2, &USART_ClockInitStructure); 
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART2, ENABLE);// USART1使能
}

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	/* 使能 USART3 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE); 
  USART_DeInit(USART3);          //将外设USART1寄存器重设为缺省值
	/* USART1 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOA
	
	//Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  
	/* USART3 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART3, &USART_InitStructure);  //初始化USART2
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;         //设置SCLK引脚上时钟输出的极性为低电平
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;   //时钟第一个边沿进行数据捕获
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;  //最后一位数据的时钟脉冲不从SCLK输出
  USART_ClockInit(USART3, &USART_ClockInitStructure); 
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART3, ENABLE);// USART1使能
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断，可以扩展来控制
		{
         RxBuffer[RxCounter++] =USART_ReceiveData(USART1);//接收模块的数据
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		if(RxCounter>3)
	  {
	  	Flag1=TRUE;
  	}
    	
		
  }
	
	
/**************************************************************************************
 * 描  述 : USART2全局中断服务
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void USART2_IRQHandler(void)
{  
  if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)  //接收中断
  {  
    RxBuffer2[RxCounter2++]= USART_ReceiveData(USART2);     //通过外设USART2接收数据
    
  }	
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);  //清除USART2的中断待处理位
 if(RxCounter2>3)
	{
		Flag2=TRUE;
	}	
	
}

/**************************************************************************************
 * 描  述 : USART2全局中断服务
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void USART3_IRQHandler(void)
{  
  if(USART_GetITStatus(USART3,USART_IT_RXNE)!= RESET)  //接收中断
  {  
    RxBuffer[RxCounter++]= USART_ReceiveData(USART3);     //通过外设USART3接收数据
    
  }	
  USART_ClearITPendingBit(USART3, USART_IT_RXNE);  //清除USART3的中断待处理位	
	if(RxCounter>3)
	{
		Flag3=TRUE;
	}
	
}

void USART1_SendData(USART_TypeDef* USARTx, char *Data)
{   
 
  USARTx->DR = (*Data & (uint16_t)0x01FF);  // 这里的*Data就是一个字符
 
  while((USARTx->SR&0x40) == 0);  	
}
void Usart1_Puts(char * str)
{
	while(*str)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送完毕
		USART_SendData(USART1,*str);
		str ++;
	}
}

void Usart2_Puts(char * str)
{
	while(*str)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//等待发送完毕
		USART_SendData(USART2,*str);
		str ++;
	}
}




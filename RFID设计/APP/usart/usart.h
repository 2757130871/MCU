#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>
#include "misc.h"
#define	FALSE					0
#define	TRUE					1
extern u8 Flag1,Flag2,Flag3;
void USART1_Config(void);
void USART2_Config(void);
void USART3_Config(void);
void USART1_SendData(USART_TypeDef* USARTx, char *Data);
void Usart1_Puts(char * str);
void Usart2_Puts(char * str);

#endif /* __USART1_H */


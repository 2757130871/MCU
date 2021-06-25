#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)
					
//485					
#define MAX485_TX  GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define MAX485_RX	 GPIO_ResetBits(GPIOA,GPIO_Pin_7)


void LED_GPIO_Config(void);

#endif /* __LED_H */

#ifndef __BSP_H
#define	__BSP_H
#include "includes.h"
void SysTick_init(void);
void BSP_Init(void);
void JTAG_Set(u8 mode);
#endif // __BSP_H

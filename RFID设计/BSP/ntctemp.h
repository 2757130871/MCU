#include "stm32f10x.h"
#include "delay.h"

#define  NUMSAMP   640
#define  NUMHEAD   40
#define  TEMPMAX   4090
#define  TEMPMIN   10

extern  void ADC1_Init(void);

extern     u8 ADCGet(u8 channel);



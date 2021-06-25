#include "delay.h"


//#define USE_TIMEMODE    1   //使用定时器方式产生延时(使用定时器延时时开启此宏定义)

#ifdef USE_TIMEMODE


#else


/**************************************************************************************
 * 描  述 : 毫秒延时
 * 入  参 : dly:延时参数，值越大，延时时间越长
 * 返回值 : 无
 **************************************************************************************/
void delay_us(u16 us)
{
  u16 i;
	
	do
  {
    i = 6;
		while(i--)__nop();
  } while (--us);
}
/**************************************************************************************
 * 描  述 : 毫秒延时
 * 入  参 : dly:延时参数，值越大，延时时间越长
 * 返回值 : 无
 **************************************************************************************/
void delay_ms(u16 ms)
{
  do
  {
    delay_us(250);
    delay_us(250);
    delay_us(250);
    delay_us(250);
  } while (--ms);
}
#endif
/*********************************END FILE********************************************/

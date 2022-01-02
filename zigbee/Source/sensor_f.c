#include"iocc2530.h"
unsigned char f_sensor(void);
unsigned char f_sensor2(void);
unsigned char f_sensor3(void);
#define DATA_PIN P1_5 
#define DATA_PIN2 P0_4 
#define DATA_PIN3 P0_7 
unsigned char f_sensor(void){
  unsigned char a=1;

    //初始化DO口
    P1DIR &= ~0x20;          //P1.5定义为输入口 
    P1SEL &= ~0x20;
  return DATA_PIN;
}

unsigned char f_sensor2(void){
  unsigned char a=1;
  
     P0DIR &= ~0x10; 
     P0SEL &= ~0x10;//P0.4定义为输入口 
  return DATA_PIN2;  
}
unsigned char f_sensor3(void){
  unsigned char a=1;
  
     P2DIR &= 0x7f;
     P2SEL &= 0x7f;//P0.4定义为输入口 
  return DATA_PIN3;  
}

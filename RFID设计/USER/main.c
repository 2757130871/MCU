/******************** ********************        
 MINI STM32 STM32F103C8T6
**********************************************************************************/	

#include "includes.h"
//#include "usart.h"	
#include "stm32f10x_it.h"
#include "dht11.h"
#include "ntctemp.h"
#include "rc522_function.h"
#include "rc522_config.h"

__align(8) static OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //∂®“Â’ª

#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//2:2
} 

int main(void)
{
  JTAG_Set(SWD_ENABLE);	 
	BSP_Init();
	DHT11_GPIO_Config();                     
	
	ADC1_Init();      //ADC1
	
	NVIC_Configuration(); 	 
	USART1_Config(); //USART1 ≈‰÷√PA9  dPA10  
	
	RC522_Init(); 
	PcdReset();
	M500PcdConfigISOType ( 'A' );
	
	OSInit();	
	OSTaskCreate(Task_Start,(void *)0,&startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);	
	OSStart();
  return 0;
 }




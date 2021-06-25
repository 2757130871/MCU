#include "includes.h"
#include "usart.h"
#include <string.h>
#include "ds18b20.h"
#include "dht11.h"
#include "ntctemp.h"
#include "math.h"
#include <stdlib.h>
#include "bujin.h"
#include "wdg.h"
#include "oled.h"
#include "bmp.h"
//#include "ina219.h"
#include "rc522_function.h"
#include "rc522_config.h"
  char TLINK_xlh[]="8UDX63464595QVWV";//���ݵ㶯�汾02���⿨  11-41
//char TLINK_xlh[]="3R9HSL6V2A307XJ2";//TLINKƽ̨
//char TLINK_xlh[]="86L8I2UZH300B23X";//TLINKƽ̨
//  char TLINK_xlh[]="LD158800041";
                  
extern char  RxCounter,RxBuffer[100];
extern char  RxCounter2,RxBuffer2[100];
extern char  RxCounter3,RxBuffer3[100];
int   count=0,swstate=0;
float temp_ds18b20,temp_linshi;
DHT11_Data_TypeDef DHT11_Data;
int   KEYB8=0,KEYB9=0,KEYB7=0;

char gps_buf[30]="3155.13530,N,11857.11801,E";

int  a,GPS_CONFIG=1;
u8 ADC_buff1, ADC_buff2;

char t10_buf[30]={0xB5,0x62,0x06,0x08,0x06,0x00,0x10,0x27,0x01,0x00,0x01,0x00,0x4D,0xDD};        //14������
char GGA_buf[30]={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x24};//16������
char GSA_buf[30]={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x02,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x32};//16������
char GSV_buf[30]={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x39};
char GLL_buf[30]={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x2B};
char VTG_buf[30]={0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x05,0x00,0x00,0x00,0x00,0x00,0x01,0x05,0x47};

//�Ʋ�������
char MPU6050[2]={0xA5,0x51};
int   bushu=0;
int   chazhi=0;
//������ʪ��
char read_tuwen_buf[9]={0x01,0x03,0x00,0x02,0x00,0x02,0x65,0xCB};  //01 03 00 02 00 02 65 CB
uint16_t tutemp,tuhumi;

//zigbee��ѯ����
int   switch1=0,switch2=0,switch3=0,switch4=0;
char readcg1[]={0x3A,0x00,0x01,0x02,0x39,0x23};  //6������	
char readcg2[]={0x3A,0x00,0x02,0x02,0x3A,0x23};  //6������	
//����
char kz10[]={0x3A,0x00,0x01,0x0A,0x00,0x31,0x23};  //7������	
char kz11[]={0x3A,0x00,0x01,0x0A,0x01,0x30,0x23};  //7������		
char kz20[]={0x3A,0x00,0x01,0x0A,0x02,0x33,0x23};  //7������	
char kz21[]={0x3A,0x00,0x01,0x0A,0x03,0x32,0x23};  //7������	

char kz30[]={0x3A,0x00,0x02,0x0A,0x00,0x32,0x23};  //7������	
char kz31[]={0x3A,0x00,0x02,0x0A,0x01,0x33,0x23};  //7������		
char kz40[]={0x3A,0x00,0x02,0x0A,0x02,0x30,0x23};  //7������	
char kz41[]={0x3A,0x00,0x02,0x0A,0x03,0x31,0x23};  //7������	

//�������
int bujincount=0,zheng=0,fan=0;

//���㹦��
/*
unsigned int voltage_mv,Current_ma,Power_mw,R_mv;

float voltage_mv_float,
Current_ma_float,
Power_mw_float,
R_mv_float;
*/
//RFID�����
u8  rfid_kuai_addr=0x0C;
u8  rfid_data[16]={0x46,0x59,0x5F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x32};//
u8  rfid_data1[16]={0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,0x32,0x33,0x34,0x35,0x36};//
u8  USERKEYINITA[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; //��??��?��????A�ꡧ3?��??��??,???����??�쨨��?T��?
u8  rfid_data_buf[16]={0};//
void IC_test ( void );
char cStr [ 30 ];
 unsigned char ucArray_ID [ 4 ];  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
uint8_t ucStatusReturn;          //����״̬
int rfid=0;

char wen1[30]="13.5",shi1[30]="23.5",light1[30]="33.5",fenchen1[30]="43",liuhuaq1[30]="53",co21[30]="635",nh31[30]="735",weight1[30]="83";
char wen2[30]="93.5",shi2[30]="10.5",light2[30]="11.5",fenchen2[30]="12",liuhuaq2[30]="13",co22[30]="145",nh32[30]="155",weight2[30]="163";
char wen3[30]="17.5",shi3[30]="18.5",light3[30]="19.5";
char liu3[30]="35",sw3[5]="0",sw4[5]="0";
char dian3[30]="0";
int  switch_change=0;
char WG1[150]="S20.0,49.0,97A38163,E";

char head1[1]="S";
char split1[1]=",";
char  end1[1]="E";



uint32_t TLINK_DATA_LINK=0,TLINK_XLH_LINK=0,timecount=0;
__align(8) static OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //����ջ 
__align(8) static OS_STK task_led3_stk[TASK_LED3_STK_SIZE];		  //����ջ
__align(8) static OS_STK task_led4_stk[TASK_LED4_STK_SIZE];		  //����ջ
__align(8) static OS_STK task_led5_stk[TASK_LED5_STK_SIZE];		  //����ջ
__align(8) static OS_STK task_wdg6_stk[TASK_wdg6_STK_SIZE];		  //����ջ

/**************************************************************************************
 * ��  �� : ������⣬������ż�⵽�͵�ƽʱ����LD2��������ż�⵽�ߵ�ƽʱϨ��LD2
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void infrared_Scan(void)
{
	
		 if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)           //����Ϊ�͵�ƽ
	  {
	    delay_ms(10);                                            //��ʱ������
	    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)	       //������Ϊ�͵�ƽ
	    {
				KEYB7=1;
		    		 
		   
	    }
	  }
			else
		{
		  	KEYB7=0;
		}
//		if(KEYB7==1)
//		{
//			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0)           //����Ϊ�͵�ƽ
//			{
//				delay_ms(10);                                            //��ʱ������
//				if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0)	       //������Ϊ�͵�ƽ
//				{
//					KEYB8=1;
//					switch3=1;
//					GPIO_SetBits(GPIOB,GPIO_Pin_14);				
//				 
//				}
//			}
//			else
//			{
//					KEYB8=0;
//					switch3=0;
//					GPIO_ResetBits(GPIOB,GPIO_Pin_14);
//			}
//		}
		if(KEYB7==1)
		{
			 if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)           //����Ϊ�͵�ƽ
	  {
	    delay_ms(10);                                            //��ʱ������
	    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)	       //������Ϊ�͵�ƽ
	    {
		    KEYB9=1;	
        switch4=1;	
        GPIO_SetBits(GPIOB,GPIO_Pin_15);				
		   
	    }
	  }
		else
		{
		  	KEYB9=0;
			  switch4=0;
			  GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		}
	}
	
			
}
/**************************************************************************************
 * ��  �� : ������ʾʵʱ��ʪ��
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/

void DHT11_SCAN(void)
{
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
	//	printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
	}
	else
	{
	//	printf("Read DHT11 ERROR!\r\n");
	}
}


void wifi_start(void)
{
						
					  OSTimeDlyHMSM(0, 0,5,200);				  //��ʱ
						printf("+++");
						OSTimeDlyHMSM(0, 0,0,200);				  //��ʱ
						printf("AT+CWMODE=1\r\n");
						OSTimeDlyHMSM(0, 0,0,100);				  //��ʱ
						printf("AT+CWJAP=\"fengyuan_wlw\",\"fengyuan_wlw\"\r\n");
						OSTimeDlyHMSM(0,0,10,0);				  //��ʱ
		        printf("AT+CIPMUX=0\r\n");
						OSTimeDlyHMSM(0, 0,2,200);				  //��ʱ
	          Usart1_Puts("AT+SAVETRANSLINK=1,\"112.74.98.39\",8647,\"TCP\"\r\n");
					 // printf("AT+CIPSTART=\"TCP\",\"link.tlink.io\",8647,\r\n");
						OSTimeDlyHMSM(0, 0,1,500);				  //��ʱ
						printf("AT+CIPMODE=1\r\n");
	
            OSTimeDlyHMSM(0, 0,0,500);				  //��ʱ
						printf("AT+RST\r\n");
	          OSTimeDlyHMSM(0, 0,8,500);				  //��ʱ
						
}

void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' ��û���õ�����ֹ��������ʾ����
	SysTick_init();
//	wifi_start();
 IWDG_Init(4,1625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	
	OSTaskCreate(Task_LED2,(void *)0,		  	//��������2
 &task_led2_stk[TASK_LED2_STK_SIZE-1], TASK_LED2_PRIO); 	
	
		OSTaskCreate(Task_3,(void *)0,		  	//��������3
 &task_led3_stk[TASK_LED3_STK_SIZE-1], TASK_LED3_PRIO);
	
	OSTaskCreate(Task_4,(void *)0,		  	//��������4
 &task_led4_stk[TASK_LED4_STK_SIZE-1], TASK_LED4_PRIO); 
	
	OSTaskCreate(Task_5,(void *)0,		  	//��������4
 &task_led5_stk[TASK_LED5_STK_SIZE-1], TASK_LED5_PRIO); 
 OSTaskCreate(Task_wdg6,(void *)0,		  	//��������6
 &task_wdg6_stk[TASK_wdg6_STK_SIZE-1], TASK_wdg6_PRIO);
	printf("restart");
    while (1)
    {
        
        OSTimeDlyHMSM(0, 0,8,100);
       // count++;
				TLINK_XLH_LINK++; //�����·��������ڼ���
			
				if( TLINK_DATA_LINK==0)
				{					
		//			printf("%s",TLINK_xlh);	
				}
				
				OSTimeDlyHMSM(0, 0,8,100);
				//-10��85����Ϊ0.5
//				if( DS18B20_Init()==0)	                        
//					{
//						
//						temp_linshi=DS18B20_Get_Temp();
//						if((temp_linshi>(-10))&&(temp_linshi<100))
//						{
//							temp_ds18b20=temp_linshi;
//						}	
//					}
//				DHT11_SCAN();                            //ʵʱ��ʾ��ʪ��
					
					//��ADCֵ��buff����
		      ADC_buff1 = ADCGet(0);   //PB0
	      	ADC_buff2 = ADCGet(1);   //PB1
     //     printf("G,%.1f,%.1f,%d,E",(float)(DHT11_Data.temp_int+DHT11_Data.temp_deci/10.0),(float)(DHT11_Data.humi_int+DHT11_Data.humi_deci/10.0),KEYB7); //MKAQ
			  	printf("G,%.1f,%.1f,E",(float)(DHT11_Data.temp_int+DHT11_Data.temp_deci/10.0),(float)(DHT11_Data.humi_int+DHT11_Data.humi_deci/10.0)); //MKAQ
				
  
					  
						if( TLINK_DATA_LINK==1)
							{
								
						  //	printf("S%.1f,%d,E",temp_ds18b20,ADC_buff1);
							//	printf("%s%s%s","S",gps_buf,"E");
							//	printf("S%.1f,%s,E",temp_ds18b20,gps_buf);
							//	printf("S%d,%s,E",bushu,gps_buf);
							//	printf("S%d,%d,%d,%d,E",switch1,switch2,switch3,switch4);
							// 	printf("S%.1f,%.1f,%d,E",(float)(DHT11_Data.temp_int+DHT11_Data.temp_deci/10.0),(float)(DHT11_Data.humi_int+DHT11_Data.humi_deci/10.0),255-ADC_buff1); //MKAQ
							//	printf("S%d,%d,E",255-ADC_buff1,switch1);
							//	printf("S%d,%d,%d,E",(DHT11_Data.temp_int),(DHT11_Data.humi_int),255-ADC_buff1); //MKAQ
							//	printf("S%.1f,%d,%d,%d,%d,%d,%d,E",temp_ds18b20,switch1,switch2,switch3,switch4,KEYB8,KEYB9);
							//	printf("S%d,%d,%d,%d,E",KEYB8,KEYB9,switch3,switch4); 2���ֶ�����Զ��
							//	  printf("S%d,%d,%.1f,%d,E",KEYB8,switch3,(float)tuhumi/10.0,switch4); //12���ֶ�1��Զ��
							//	printf("S%d,%d,%d,%d,E",KEYB8,switch3,KEYB9,switch4); //20181017 �ֶ�����Զ��
							//	  printf("S%d,%d,E",switch3,switch4); //20181017 �ֶ�����Զ��
								printf("S,%d,%s,E",switch1,rfid_data_buf);	
							}	
           //   OLED_DrawBMP(0,0,63,8,BMP3);							
	
				
				
				
				
				
				
			if( TLINK_XLH_LINK>4)    //�ж������·�������û�г�ʱ
				{
					TLINK_DATA_LINK=0;
					TLINK_XLH_LINK=0;
		//			wifi_start();
			//		GPIO_SetBits(GPIOC,GPIO_Pin_13);//mini�汾
					
				//	GPIO_SetBits(GPIOB,GPIO_Pin_12);//�����DTU��λ
				//	OSTimeDlyHMSM(0, 0,1,0);
				//  GPIO_ResetBits(GPIOB,GPIO_Pin_12);//�����
					
				}		
			
				
				
    }
}

//����2����������
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
			
			
			//USART_SendData(USART2, RxBuffer[0]);
			//printf("usart2");
			//xprintf("%s%d,%d,%s%s","S",temperature,humidity,gps_buf,"E");
		 
	
			if(Flag1==TRUE)
			{
					OSTimeDlyHMSM(0, 0,0,100);
					Flag1=FALSE;
											 //�ж�͸��ģ����û������
											 if( (strstr((char *)RxBuffer, "TCPOK")))
											{
												TLINK_DATA_LINK=1;
												TLINK_XLH_LINK=0;
									//			GPIO_ResetBits(GPIOC,GPIO_Pin_13);//MINI�汾
											//	GPIO_SetBits(GPIOB,GPIO_Pin_12);//�����
											}
											 if(RxBuffer[0]==0X54&&RxBuffer[1]==0X43&&RxBuffer[2]==0X50)
											{
												TLINK_DATA_LINK=1;
												TLINK_XLH_LINK=0;
								//				GPIO_ResetBits(GPIOC,GPIO_Pin_13);//MINI�汾
											//	GPIO_SetBits(GPIOB,GPIO_Pin_12);//�����
											}
												 if( (strstr((char *)RxBuffer, "FY_02_001:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_SetBits(GPIOB,GPIO_Pin_12);
											  GPIO_SetBits(GPIOA,GPIO_Pin_8);
											  switch1=1;
											 printf("S%d,%s,E",switch1,rfid_data_buf);	

										 }
										 if( (strstr((char *)RxBuffer, "FY_02_001:0")))   //�жϿ��ƽڵ�
										 {
											
												GPIO_ResetBits(GPIOB,GPIO_Pin_12);
											  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
											  switch1=0;
											 printf("S%d,%s,E",switch1,rfid_data_buf);	
                     									 
										 }
										 
										 if( (strstr((char *)RxBuffer, "200099277:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_ResetBits(GPIOB,GPIO_Pin_12);
											  switch1=1;

										 }
										 if( (strstr((char *)RxBuffer, "200099277:0")))   //�жϿ��ƽڵ�
										 {
											
												GPIO_SetBits(GPIOB,GPIO_Pin_12);
											  switch1=0;
                     									 
										 }
										 if( (strstr((char *)RxBuffer, "200099278:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_ResetBits(GPIOB,GPIO_Pin_13);
											 
											  switch2=1;	
										 }
										 if( (strstr((char *)RxBuffer, "200099278:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_SetBits(GPIOB,GPIO_Pin_13);
											  switch2=0;
                     								 
										 }
										  if( (strstr((char *)RxBuffer, "200099279:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_SetBits(GPIOB,GPIO_Pin_15);
											 switch3=1;
											 printf("S%d,%d,E",switch3,switch4); //20181017 �ֶ�����Զ��
											 
											
                     								 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099279:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_ResetBits(GPIOB,GPIO_Pin_15);
											 switch3=0;
											 printf("S%d,%d,E",switch3,switch4); //20181017 �ֶ�����Զ��
											 
                     								 
										 }
										  if( (strstr((char *)RxBuffer, "200099280:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_SetBits(GPIOB,GPIO_Pin_15);
											 switch4=1;
											 printf("S%d,%d,E",switch3,switch4); //20181017 �ֶ�����Զ��
											 OSTimeDlyHMSM(0, 0,1,300);
											 GPIO_ResetBits(GPIOB,GPIO_Pin_15);
											  switch4=0;
											 printf("S%d,%d,E",switch3,switch4); //20181017 �ֶ�����Զ��
											 	
										 }
										 if( (strstr((char *)RxBuffer, "200099280:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_ResetBits(GPIOB,GPIO_Pin_15);
											 switch4=0;
											  
                     								 
										 }
										 	if( (strstr((char *)RxBuffer, "200110577:1")))   //�жϿ��ƽڵ�
									 {
											GPIO_ResetBits(GPIOB,GPIO_Pin_13);	
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz10[timecount]);			  //��ʱ
												 }
												 OSTimeDlyHMSM(0, 0,0,500);
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz10[timecount]);			  //��ʱ
												 }									 
											
									 }
											if( (strstr((char *)RxBuffer, "200110577:0")))   //�жϿ��ƽڵ�
									 {
											 GPIO_SetBits(GPIOB,GPIO_Pin_13);	
										 for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz11[timecount]);			  //��ʱ
												 }
												 OSTimeDlyHMSM(0, 0,0,500);
												 for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz11[timecount]);			  //��ʱ
												 }
											
									 }
											if( (strstr((char *)RxBuffer, "200110578:1")))   //�жϿ��ƽڵ�
									 {
											//GPIO_ResetBits(GPIO_LED,GPIO_Pin_1);	
                      for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz20[timecount]);			  //��ʱ
												 }
												OSTimeDlyHMSM(0, 0,0,500);
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz20[timecount]);			  //��ʱ
												 }												 
											
									 }
											if( (strstr((char *)RxBuffer, "200110578:0")))   //�жϿ��ƽڵ�
									 {
											// GPIO_SetBits(GPIO_LED,GPIO_Pin_1);	
										  for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz21[timecount]);			  //��ʱ
												 }
													OSTimeDlyHMSM(0, 0,0,500);
												 for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz21[timecount]);			  //��ʱ
												 }
											 
									 }
									 if( (strstr((char *)RxBuffer, "200110579:1")))   //�жϿ��ƽڵ�
									 {
											//GPIO_ResetBits(GPIO_LED,GPIO_Pin_0);	
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz30[timecount]);			  //��ʱ
												 }
												 OSTimeDlyHMSM(0, 0,0,500);		
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz30[timecount]);			  //��ʱ
												 }												 
											
									 }
											if( (strstr((char *)RxBuffer, "200110579:0")))   //�жϿ��ƽڵ�
									 {
											// GPIO_SetBits(GPIO_LED,GPIO_Pin_0);	
										 for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz31[timecount]);			  //��ʱ
												 }
												 OSTimeDlyHMSM(0, 0,0,500);
											for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz31[timecount]);			  //��ʱ
												 }
											
									 }
											if( (strstr((char *)RxBuffer, "200110580:1")))   //�жϿ��ƽڵ�
									 {
											//GPIO_ResetBits(GPIO_LED,GPIO_Pin_1);	
                      for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz40[timecount]);			  //��ʱ
												 }
												 OSTimeDlyHMSM(0, 0,0,500);	
													 for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz40[timecount]);			  //��ʱ
												 }
											
									 }
											if( (strstr((char *)RxBuffer, "200110580:0")))   //�жϿ��ƽڵ�
									 {
											// GPIO_SetBits(GPIO_LED,GPIO_Pin_1);	
										  for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz41[timecount]);			  //��ʱ
												 }
													OSTimeDlyHMSM(0, 0,0,500);
												  for(timecount=0;timecount<7;timecount++)
												 {
													 USART1_SendData(USART2,&kz41[timecount]);			  //��ʱ
												 }
											 
									 }
				 
				 
				  memset(RxBuffer,'\0',RxCounter);
					RxCounter=0;
		 }
	  	if(Flag2==TRUE)
		  {	
				OSTimeDlyHMSM(0, 0,0,200);
				Flag2=FALSE;
			  
			
				
										if( (strstr((char *)RxBuffer, "200099277:1")))   //�жϿ��ƽڵ�
										{
												LED1( ON );
										}
										if( strstr((char *)RxBuffer, "V,"))
										{
											GPS_CONFIG=0;
										}
										//01 03 04 00 02 01 05 9A 60 
											 if((RxBuffer2[0]==0x01) &&RxBuffer2[1]==0x03)
										{
							 
											tuhumi= ((u16)RxBuffer2[3]<<8)+RxBuffer2[4];
             
										}
										
										if( strstr((char *)RxBuffer, "A,")&&strstr((char *)RxBuffer, "GPRMC")&&GPS_CONFIG==1)
										{
											 
												strncpy(gps_buf,strstr((char *)RxBuffer, "A,")+2,26);
												gps_buf[26]='\0';
												GPS_CONFIG=0;
										}
										 if((RxBuffer[0]==0x3A) &&RxBuffer[2]==0x01)
										{
											
										//	LUX=ucStr[6]-0x30;
											if(RxBuffer[6]==1)
											{
												switch1=0;
											}
											else if(RxBuffer[6]==0)
														   switch1=1;
											
											if(RxBuffer[7]==1)
											{
												switch2=0;
											}
											else if(RxBuffer[7]==0)
														   switch2=1;
											
												
										
										}
										if((RxBuffer[0]==0x3A) &&RxBuffer[2]==0x02)   //temperature,humidity
										{
										
												// temperature = ((u16)ucStr[4]);
												//	humidity = (u16)ucStr[5];
											if(RxBuffer[6]==1)
											{
												switch3=0;
											}
											else if(RxBuffer[6]==0)
														   switch3=1;
											
											if(RxBuffer[7]==1)
											{
												switch4=0;
											}
											else if(RxBuffer[7]==0)
														   switch4=1;
										}
								  		if( (strstr((char *)RxBuffer, "200099276:1")))   //�жϿ��ƽڵ�
										 {
												LED1( OFF );
											 
											  MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("\r\nRECEIVE B14 ON!\r\n");	
												MAX485_RX;											 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099276:0")))   //�жϿ��ƽڵ�
										 {
										
												LED1( ON);
											  MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("\r\nRECEIVE B14 OFF!\r\n");	
												MAX485_RX;													 
										 }
										 	if( (strstr((char *)RxBuffer, "200099277:1")))   //�жϿ��ƽڵ�
									 {
											  GPIO_SetBits(GPIOB,GPIO_Pin_15);	
												MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("\r\nRECEIVE B15 ON!\r\n");	
												MAX485_RX;						 
											
									 }
											if( (strstr((char *)RxBuffer, "200099277:0")))   //�жϿ��ƽڵ�
									 {
											  GPIO_ResetBits(GPIOB,GPIO_Pin_15);	
										    MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("\r\nRECEIVE B15 OFF!\r\n");	
												MAX485_RX;	
											
									 }
									  		if( (strstr((char *)RxBuffer, "200099278:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_ResetBits(GPIOB,GPIO_Pin_15);
											 
											  MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("RECEIVE OK!");	
												MAX485_RX;											 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099278:0")))   //�жϿ��ƽڵ�
										 {
										
												GPIO_SetBits(GPIOB,GPIO_Pin_12);	
											  MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("RECEIVE OK!");	
												MAX485_RX;													 
										 }
										 	if( (strstr((char *)RxBuffer, "200099279:1")))   //�жϿ��ƽڵ�
									 {
											  GPIO_ResetBits(GPIOB,GPIO_Pin_5);	
												MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("RECEIVE OK!");	
												MAX485_RX;						 
											
									 }
											if( (strstr((char *)RxBuffer, "200099279:0")))   //�жϿ��ƽڵ�
									 {
											  GPIO_SetBits(GPIOB,GPIO_Pin_5);	
										    MAX485_TX;
											  OSTimeDlyHMSM(0, 0,0,10);
                        Usart2_Puts("RECEIVE OK!");	
												MAX485_RX;	
											
									 }
			 
			 
			 
			  memset(RxBuffer2,'\0',RxCounter2);
				RxCounter2=0;
				
		  }
			
			if(Flag3==TRUE)
		  {	
				OSTimeDlyHMSM(0, 0,0,200);
				Flag3=FALSE;
			
			
			
				
									 if( (strstr((char *)RxBuffer, "200099277:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_ResetBits(GPIOB,GPIO_Pin_12);
											  switch1=1;

										 }
										 if( (strstr((char *)RxBuffer, "200099277:0")))   //�жϿ��ƽڵ�
										 {
											
												GPIO_SetBits(GPIOB,GPIO_Pin_12);
											  switch1=0;
                     									 
										 }
										 if( (strstr((char *)RxBuffer, "200099278:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_ResetBits(GPIOB,GPIO_Pin_13);
											 
											  switch2=1;
                     								 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099278:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_SetBits(GPIOB,GPIO_Pin_13);
											  switch2=0;
                     								 
										 }
										  if( (strstr((char *)RxBuffer, "200099279:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_SetBits(GPIOB,GPIO_Pin_14);
											 switch3=1;
											 
											
                     								 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099279:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_ResetBits(GPIOB,GPIO_Pin_14);
											 switch3=0;
											 
                     								 
										 }
										  if( (strstr((char *)RxBuffer, "200099280:1")))   //�жϿ��ƽڵ�
										 {
												GPIO_SetBits(GPIOB,GPIO_Pin_15);
											 switch4=1;
											 
										
                     								 
												
										 }
										 if( (strstr((char *)RxBuffer, "200099280:0")))   //�жϿ��ƽڵ�
										 {
											 
												GPIO_ResetBits(GPIOB,GPIO_Pin_15);
											 switch4=0;
											  
                     								 
										 }
									
			 
			 
			 
			  memset(RxBuffer3,'\0',RxCounter3);
				RxCounter3=0;
				
		  }
			OSTimeDlyHMSM(0, 0,0,150);
     				 
    }
}
//����3����Ʋ�
void Task_3(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
			
						//����  01 03 00 02 00 02 65 CB
			    MAX485_TX;
					OSTimeDlyHMSM(0, 0,0,10);
					for(a=0;a<8;a++)
						{
							 USART1_SendData(USART2,&read_tuwen_buf[a]);
						}
						a=0;
					MAX485_RX;
			OSTimeDlyHMSM(0, 0,2,150);
				 
    }
}

//����4����GPS����
void Task_4(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
	  infrared_Scan();
			
   	OSTimeDlyHMSM(0, 0,0,100);
		IC_test ();//IC�����	
		if(rfid==1)
		{
			sprintf ( cStr, "%02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );							
			printf ( "%s",cStr ); 
			OSTimeDlyHMSM(0, 0,1,50);
			rfid=0;
			
		}
			/*
			//ͨ�����ԣ��鿴��������ֵ
		voltage_mv=INA_GET_Voltage_MV();	//�õ���ѹ��mV��
		voltage_mv_float=(float)voltage_mv/1000;	//ת��Ϊ�����͵�ѹ��V��
		Current_ma=INA_GET_Current_MA();	//�õ�������mA��
		Current_ma_float=(float)Current_ma;	////�õ������͵�����V��
		if(Current_ma_float>3000)
		{
			Current_ma_float=0;
		}
		
		Power_mw=INA_GET_Power_MW();//�õ����ʣ�mW��
		Power_mw_float=(float)Power_mw;//�õ������͹��ʣ�mW��
		Power_mw_float=Current_ma_float*voltage_mv_float;
			
		printf("S%.1fV,%.1fma,%.1fmW,E",voltage_mv_float,Current_ma_float,Power_mw_float); //20181017 �ֶ�����Զ��
			*/
//	   if(GPS_CONFIG==1)
//			{
//			
//			for(a=0;a<14;a++)
//			{
//			  USART1_SendData(USART2, &t10_buf[a]);
//			}
//			OSTimeDlyHMSM(0, 0,10,200);
//			for(a=0;a<16;a++)
//			{
//			  USART1_SendData(USART2, &GGA_buf[a]);
//			}
//			OSTimeDlyHMSM(0, 0,10,200);
//			for(a=0;a<16;a++)
//			{
//			  USART1_SendData(USART2, &GLL_buf[a]);
//			}
//				OSTimeDlyHMSM(0, 0,10,200);
//			for(a=0;a<16;a++)
//			{
//			  USART1_SendData(USART2, &GSA_buf[a]);
//			}
//				OSTimeDlyHMSM(0, 0,10,200);
//			for(a=0;a<16;a++)
//			{
//			  USART1_SendData(USART2, &GSV_buf[a]);
//			}
//				OSTimeDlyHMSM(0, 0,10,200);
//			for(a=0;a<16;a++)
//			{
//			  USART1_SendData(USART2, &VTG_buf[a]);
//			}
//	  	}
//			OSTimeDlyHMSM(0, 0,1,150);
//			for(a=0;a<2;a++)
//				{
//					USART1_SendData(USART3, &MPU6050[a]);
//				}
//			GPS_CONFIG=1;
	
	
     				 
    }
}
//����5
void Task_5(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
				if( TLINK_DATA_LINK==0)
					{					
						GPIO_ResetBits(GPIOC,GPIO_Pin_13);				
					}
						if( TLINK_DATA_LINK==1)
					{					
						GPIO_SetBits(GPIOC,GPIO_Pin_13);
						OSTimeDlyHMSM(0, 0,1,300);
						GPIO_ResetBits(GPIOC,GPIO_Pin_13);
						
					}
					DHT11_SCAN();                            //ʵʱ��ʾ��ʪ��

		  
		    	OSTimeDlyHMSM(0, 0,0,500);
				 
    }
}
//����5
void Task_wdg6(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
      //ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
		  IWDG_Feed();//���WK_UP����,��ι��
	//	  Usart3_Puts("\r\nWEIDOG\r\n");
		
			OSTimeDlyHMSM(0, 0,0,500);
				 
    }
}
/**
  * ��������: �Ž����Ժ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void IC_test ( void )
{
//	char cStr [ 30 ];
//  unsigned char ucArray_ID [ 4 ];  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
//	uint8_t ucStatusReturn;          //����״̬
	
 // while ( 1 )
  { 
       /*Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK ) 
		{
			/*��ʧ���ٴ�Ѱ��*/
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );	
			  if ( ucStatusReturn == MI_OK  )
      {
				ucStatusReturn=MI_ERR;
				ucStatusReturn = PcdAnticoll ( ucArray_ID );
				     if ( ucStatusReturn == MI_OK  )
      {
				rfid=1;
				
//			  	sprintf ( cStr, "%02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );
//			  //	printf("S%.1f,%.1f,%s,E",(float)(DHT11_Data.temp_int+DHT11_Data.temp_deci/10.0),(float)(DHT11_Data.humi_int+DHT11_Data.humi_deci/10.0),cStr); //MKAQ
//				  				sprintf(wen1,"%.1f",(float)(DHT11_Data.temp_int+DHT11_Data.temp_deci/10.0));
//					        sprintf(shi1,"%.1f",(float)(DHT11_Data.humi_int+DHT11_Data.humi_deci/10.0));
//					       


//									memset(WG1, '\0', sizeof(WG1));
//									strncat(WG1,head1,1);
//									strcat(WG1,wen1);
//									strncat(WG1,split1,1);
//									strcat(WG1,shi1);
//									strncat(WG1,split1,1);
//									strcat(WG1,cStr);
//									strncat(WG1,split1,1);
//									strncat(WG1,end1,1);
//							  	printf("%s",WG1);		
				
				
			//	OSTimeDlyHMSM(0, 0,1,0);
				ucStatusReturn=MI_ERR;
				ucStatusReturn = PcdSelect( ucArray_ID );
	
	//			ucStatusReturn=MI_ERR;
	//			ucStatusReturn = PcdSelect( ucArray_ID );
				
			}	
           if ( ucStatusReturn == MI_OK  )
      {
				ucStatusReturn=MI_ERR;
				ucStatusReturn = PcdAuthState(0x60,0x1,USERKEYINITA,ucArray_ID);//��֤;
				//ucStatusReturn = PcdAuthState(0x60,0x00,USERKEYINITA,ucArray_ID);//��֤;
				
			}	
            if ( ucStatusReturn == MI_OK  )
      {
			//	delayms(20);
				ucStatusReturn=MI_ERR;
			//	ucStatusReturn = PcdWrite(0x01,rfid_data1);//����;
				ucStatusReturn = PcdRead(0x01,rfid_data_buf);//����;
			//	printf ( "%s\r\n",rfid_data ); 
				
			}	
          if ( ucStatusReturn == MI_OK  )
      {
				ucStatusReturn=MI_ERR;
				
	      if(rfid_data_buf[0]==0X46&&rfid_data_buf[1]==0X59)
				{
				//printf ( "%s\r\n",rfid_data_buf ); 
	//			printf("S%d,%s,E",switch1,rfid_data_buf);
				GPIO_SetBits(GPIOA,GPIO_Pin_8 );	 // �ر����м̵���
				GPIO_SetBits(GPIOB,GPIO_Pin_12);
				OSTimeDlyHMSM(0, 0,1,150);	
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
				GPIO_ResetBits(GPIOA,GPIO_Pin_8 );	 // �ر����м̵���
				}
			//	printf ( "%s\r\n",rfid_data_buf ); 
			//	memset(rfid_data_buf,'\0',16);
		//		PcdHalt();
		//		Write_MFRC522();
				
			}
				
			}	
	
		}			
			 
   		
		 

		

   
  }	
}




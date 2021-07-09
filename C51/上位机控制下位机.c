#include <reg52.h> //reg52.h
#include <intrins.h> //×Ö·û´®²Ù×÷º¯Êý

sbit LED1 = P2 ^ 0;
sbit LED2 = P2 ^ 2;
sbit LED3 = P2 ^ 4;
sbit K1 = P3 ^ 1;

#define uint unsigned int
#define uchar unsigned char

uint temp;

void delay(uint x)
{
	uint i, j;
	for (i = x;i > 0;i--)
		for (j = 150;j > 0;j--);

}

void init()
{
	EX0 = 1; //¿ªÆôÍâ²¿ÖÐ¶Ï1
	EA = 1;   //¿ªÆô×ÜÖÐ¶Ï
	IT0 = 0;	//µÍµçÆ½´¥·¢

}

void usart_init()
{
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;

}

void main()
{
	usart_init();
	//init();
	while (1)
	{
		/*SBUF = temp++;

		while(!TI);
		TI = 0;
		delay(500);*/



	}

}

void Int0() interrupt 0
{
	P2 = 0;
}

void UART() interrupt 4
{
	if (RI)
	{
		uchar temp = SBUF;
		P2 = temp;
		RI = 0;
	}

}

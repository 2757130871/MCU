#include <reg52.h> //reg52.h

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
	EX0 = 1;
	EA = 1;
	IT0 = 0;

}

void usart_init()
{
	TMOD = 0x20; //T1工作模式2 8为自动重装
	TH1 = 0xfd;
	TL1 = 0xfd;	//比特率9600
	TR1 = 1;	//
	SM0 = 0;	//串口工作方式1 10位异步
	SM1 = 1;
	REN = 1; 	//串口允许接收

}

void main()
{
	usart_init();
	//init();
	while (1)
	{
		SBUF = temp++;

		while (!TI);
		TI = 0;
		delay(500);
	}

}

void Int0() interrupt 0
{
	P2 = 0;
}


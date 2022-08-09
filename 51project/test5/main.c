#include <REGX52.H>

into() interrupt 0{
	P1=P1<<1|0x01;      //给对应的Led的引脚低电平
}

void main()
{
	P1=0xfe;            //初始化
	EA=1;EX0=1;IT0=1;
	while(1);
}
//P1用于protues  P2为单片机
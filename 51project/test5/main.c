#include <REGX52.H>

into() interrupt 0{
	P1=P1<<1|0x01;      //����Ӧ��Led�����ŵ͵�ƽ
}

void main()
{
	P1=0xfe;            //��ʼ��
	EA=1;EX0=1;IT0=1;
	while(1);
}
//P1����protues  P2Ϊ��Ƭ��
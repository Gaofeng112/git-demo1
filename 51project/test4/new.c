#include<reg51.h>

sfr P1=0x90;
main()
{
	P1=0xff;
	while(1)
	{
		P1=P1<<4;
		P1=P1|0x0f;
	}
}
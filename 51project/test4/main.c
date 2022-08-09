#include<reg51.h>

sfr Pd=0x90;
main()
{
	Pd=0xff;
	while(1)
	{
		Pd=Pd<<4;
		Pd=Pd|0x0f;
	}
}
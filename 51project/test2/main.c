#include<reg51.h>

void main()
{
	char p,*x,*y;
	x=0x20;        //20H��Ԫ
	y=0x21;        //21H��Ԫ 
	
	p=-1;           //��ֵ
	*x=p;          //x<0ʱ
	
	for(;;)
	{
		if(*x>0)  *y=*x;        //x>0
		if(*x==0) *y=0x20;      //x=0
		if(*x<0)  *y=*x+5;      //x<0
	}
}
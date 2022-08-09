#include<reg51.h>

void main()
{
	char p,*x,*y;
	x=0x20;        //20H单元
	y=0x21;        //21H单元 
	
	p=-1;           //赋值
	*x=p;          //x<0时
	
	for(;;)
	{
		if(*x>0)  *y=*x;        //x>0
		if(*x==0) *y=0x20;      //x=0
		if(*x<0)  *y=*x+5;      //x<0
	}
}
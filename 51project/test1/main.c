#include<reg51.h>

void main()
{
	
  char  n;             //中间变量用于储存值
	char *ptr=0x25;      //25H单元
  float *ptr2=0x30;    //30H单元
	float f;             //中间变量
	
	*ptr=6;              //赋值一个10以内的整数
	n=*ptr;              //n来存6的值
	
	f=n*n;               //f用来存平方后的值
	*ptr2=f;             //再将平方后的值赋值给ptr2
	
}
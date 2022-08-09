#include<reg51.h>

void main()
{
	data unsigned int a,k,*P3;   //定义内部RAM
	data char i,*P1,*P2;         //其他变量21H和20H
	P1=0x20;
	P2=0x21;
	P3=0x30;
	
	*P3=0100100101010;      //赋值一个二进制数
	a=*P3;
	k = 10000;
	
	while(a/k==0)k=k/10;
	for(i=0;a!=0;i++)
	{		
		*P2=a/k;              //记录十进制的值
		a=a%k;
		P2++;
		k=k/10;
	} 
	*P1=i;                  //记录长度
}



	

/*#include<reg51.h>
#include<absacc.h>


void main()
{
	int data m_at_30H;
	
	data unsigned char * p =30H;  //30H单元
	unsigned int q = 0B01;        //两个字节二进制
	*p=q;                         //内部RAM 30H单元存放二进制数
	
	DWORD[30H]=0B01;              //30H存储了一个两个字节二进制
	
	
}
*/
/*#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar data *d1,*d2;
uint dat;
main()
{
uchar temp[5],i,l;
d1=0x30;
d2=0x20;
dat=*d1*256+*(d1+1);
temp[0]=dat/10000;
temp[1]=dat%10000/1000;
temp[2]=dat%1000/100;
temp[3]=dat%100/10;
temp[4]=dat%10;
for(i=0;i<5;i++)if(temp[i]!=0)break;
l=5-i;
*d2=l;
d2++;
    do{
    *d2=temp[i];
    d2++;
    i++;
    }while(i<5);
while(1);
}
*/
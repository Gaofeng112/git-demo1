#include<reg51.h>

void main()
{
	data unsigned int a,k,*P3;   //�����ڲ�RAM
	data char i,*P1,*P2;         //��������21H��20H
	P1=0x20;
	P2=0x21;
	P3=0x30;
	
	*P3=0100100101010;      //��ֵһ����������
	a=*P3;
	k = 10000;
	
	while(a/k==0)k=k/10;
	for(i=0;a!=0;i++)
	{		
		*P2=a/k;              //��¼ʮ���Ƶ�ֵ
		a=a%k;
		P2++;
		k=k/10;
	} 
	*P1=i;                  //��¼����
}



	

/*#include<reg51.h>
#include<absacc.h>


void main()
{
	int data m_at_30H;
	
	data unsigned char * p =30H;  //30H��Ԫ
	unsigned int q = 0B01;        //�����ֽڶ�����
	*p=q;                         //�ڲ�RAM 30H��Ԫ��Ŷ�������
	
	DWORD[30H]=0B01;              //30H�洢��һ�������ֽڶ�����
	
	
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
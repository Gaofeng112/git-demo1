#include<reg51.h>

void main()
{
	
  char  n;             //�м�������ڴ���ֵ
	char *ptr=0x25;      //25H��Ԫ
  float *ptr2=0x30;    //30H��Ԫ
	float f;             //�м����
	
	*ptr=6;              //��ֵһ��10���ڵ�����
	n=*ptr;              //n����6��ֵ
	
	f=n*n;               //f������ƽ�����ֵ
	*ptr2=f;             //�ٽ�ƽ�����ֵ��ֵ��ptr2
	
}
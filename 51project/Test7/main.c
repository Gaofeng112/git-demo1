/*#include <REGX52.H>
typedef unsigned char uchar;
typedef unsigned int  uint;

sbit diy = P2_0; //����ܵ�λѡ
sbit die = P2_1;

uchar dat; //��ʱ��
//�������0-9װ��������
unsigned int table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
uchar a=30,b=30,c=5,d=5;

void smg(uchar dat){ //����ܵ���ʾ����
	ucahr a,b;
	a=dat%100/10;        //��dat���ݲ�ָ�λ��ʮλ
	b=dat%100%10/1;
	diy=0;die=1;         //��һλ����ܲ����ڶ�λ�������
	P1=~table[a];
	delay(10);
	diy=1;die=0;
	P1=~table[b];
	delay(10);    //��Ӱ
	P1=0x00;
}

void init(){
	TMOD&=0x0F;
  TMOD|=0x01;       //����T0��ģʽ
	  
}

void delay(uint m)//��ʱ����
{
	unsigned int i,j;
	for(i=0;i<m;i++)
	for(j=0;j<255;j++);
}

void main()
{
	while(1)
	{
		//��������ֵP1��
		P1=0xc9;
		delay();
		P1=0xa9;
		delay();
		P1=0x9c;
		delay();
		P1=0x9a;
		delay();
	}
}
*/
//??: LED?????
#include <REGX52.H>
#define uint unsigned int
#define uchar unsigned char
#define SEG P3

sbit E_RED=P0^0;  		//�������
sbit E_YELLOW=P0^1;		//�����Ƶ�
sbit E_GREEN=P0^2;		//�����̵�
sbit N_RED=P0^3;		  //�ϱ����
sbit N_YELLOW=P0^4;		//�ϱ��Ƶ�
sbit N_GREEN=P0^5;		//�ϱ��̵�

sbit btn = P1^0; //�ⲿ�жϿ���


sbit SCON1 = P2^0;			//��������ܵĸ�λʮλ��ʾ
sbit SCON2 = P2^1;

uchar num=10,ge,shi; 		  //���嵹��ʱ��ʼֵ����λʮλ
uchar a=0;				        //�������Ƶ��������	
uchar count=0;     			  //������ʾ����ܵı���
uchar flag;					      //������ʱ�Ƿ�Ϊ1s

//LED��9������
unsigned char code ledTab[]={
	0xC0, // 1100 0000 ����0
	0xF9, // 1111 1001 ����1
	0xA4, // 1010 0100 ����2
	0xB0, // 1011 0000 ����3
	0x99, // 1001 1001 ����4
  0x92, // 1001 0010 ����5
	0x82, // 1000 0010 ����6
	0xF8, // 1111 1000 ����7
	0x80, // 1000 0000 ����8
	0x90  // 1001 0000 ����9
};  



//1s�ӳ�	
void Delay_Ms(uint x){
	uchar t;
	while(x--)
	{
		for(t=50;t>0;t--);
	}
}

int0()interrupt 0
{
	TR0=~TR0;
}

//��������
void stop(){
	if(btn==0){
		Delay_Ms(1000);	 //ȡ������
		TR0=~TR0;           //ֹͣ����ʱ
		N_RED = 0;N_YELLOW = 1;N_GREEN = 1;
    E_RED = 0;E_YELLOW = 1;E_GREEN = 1;
	}
}



void T0INTinit() //��ʱ��T0��ʼ��Ϊ1s
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;  
	ET0=1; 
	TR0=1;
}

void T0INT() interrupt 1
{
TH0=(65536-50000) / 256;
TL0=(65536-50000) % 256;   //��ʱΪ50ms
flag++;
	if(flag==20)//�ܹ�Ϊ1s
	{
		flag=0;
	  num--;
		if(num == 0&&(a%4==0||a%4==2)) //???????
		{
			num = 5;
			a++;
		} else if (num == 0 && a%2 == 1){ //????????
			num =10;
			a++;
		}
		switch (a%4)
       {
    	 case 0: //�ϱ���,������
				N_RED = 1;N_YELLOW = 1;N_GREEN = 0; 
        E_RED = 0;E_YELLOW = 1;E_GREEN = 1; 
        break;
    	 case 1: //�ϱ���,������
				N_RED=1;	N_YELLOW = ~N_YELLOW ; N_GREEN=1; 
				E_RED=0;  E_YELLOW = 1; E_GREEN=1; 
        break;
    	 case 2: //�ϱ���,������
				N_RED = 0;N_YELLOW = 1;	N_GREEN = 1;
				E_RED = 1; E_YELLOW =1; E_GREEN = 0; 
				break;
    	 case 3: //�ϱ��죬������
				N_RED = 0;N_YELLOW = 1;	N_GREEN = 1; 
				E_RED = 1;E_YELLOW = ~N_YELLOW ; E_GREEN = 1;
				break;
	    }
	}
}


//������
void main(){
	T0INTinit();
	while(1){	
		stop();
		SEG=0xff; //��Ӱ
		shi = num / 10;
		ge = num % 10;
		switch(count){	
			//�������һ����
			case 0: SCON1=0; SCON2=1; SEG=ledTab[ge]; break;
			case 1: SCON1=1; SCON2=0; SEG=ledTab[shi]; break;
		}
		count++;
		if(count>1) count=0;
	}
}


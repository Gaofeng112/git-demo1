#include <REGX52.H>
#define uint unsigned int
#define uchar unsigned char
#define SEG P3

sbit E_RED=P2^0;  		//�������
sbit E_GREEN=P2^1;		//�����̵�
sbit Yellow=P2^5;		  //�Ƶ�
sbit N_RED=P2^6;		  //�ϱ����
sbit N_GREEN=P2^7;		//�ϱ��̵�


sbit HCA = P2^2;			//��������ܵĸ�λʮλ��ʾ
sbit HCB = P2^3;
sbit HCC = P2^4;				

uchar num=10,ge,shi; 		  //���嵹��ʱ��ʼֵ����λʮλ
uchar a=0;				        //�������Ƶ��������	
uchar count=0;     			  //������ʾ����ܵı���
uchar flag;					      //������ʱ�Ƿ�Ϊ1s

//LED��9������
unsigned char code ledTab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


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
		if(num == 0&&(a%4==0||a%4==2)) //
		{
			num = 5;
			a++;
		} else if (num == 0 && a%2 == 1){ //
			num =10;
			a++;
		}
		switch (a%4)
       {
    	 case 0: //�ϱ���,������
				N_RED = 1;N_GREEN = 0; 
        E_RED = 0;E_GREEN = 1; 
			  Yellow = 1;
        break;
    	 case 1: //��,������
				N_RED=1;	 N_GREEN=1; 
				E_RED=0;   E_GREEN=1; 
			  Yellow=~Yellow;
        break;
    	 case 2: //�ϱ���,������
				N_RED = 0; N_GREEN = 1;
				E_RED = 1; E_GREEN = 0; 
			  Yellow=1;
				break;
    	 case 3: //�ϱ��죬��
				N_RED = 0;N_GREEN = 1; 
				E_RED = 1;E_GREEN = 1;
			  Yellow=~Yellow;
				break;
	    }
	}
}


//������
void main(){
	T0INTinit();
	while(1){	
		P0=0x00; //��Ӱ
		shi = num / 10;
		ge = num % 10;
		switch(count){	
			//�������һ����
			case 0: HCC=1; HCB=0; HCA=1; P0=ledTab[shi]; break;
			case 1: HCC=1; HCB=0; HCA=0; P0=ledTab[ge]; break;
			case 2: HCC=0; HCB=0; HCA=1; P0=ledTab[shi]; break;
			case 3: HCC=0; HCB=0; HCA=0; P0=ledTab[ge]; break;
		}
		count++;
		if(count>3) count=0;
	}
}
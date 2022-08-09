/*#include <REGX52.H>
typedef unsigned char uchar;
typedef unsigned int  uint;

sbit diy = P2_0; //数码管的位选
sbit die = P2_1;

uchar dat; //计时数
//将数码管0-9装入数组中
unsigned int table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
uchar a=30,b=30,c=5,d=5;

void smg(uchar dat){ //数码管的显示函数
	ucahr a,b;
	a=dat%100/10;        //将dat数据拆分个位与十位
	b=dat%100%10/1;
	diy=0;die=1;         //第一位数码管不亮第二位数码管亮
	P1=~table[a];
	delay(10);
	diy=1;die=0;
	P1=~table[b];
	delay(10);    //消影
	P1=0x00;
}

void init(){
	TMOD&=0x0F;
  TMOD|=0x01;       //设置T0的模式
	  
}

void delay(uint m)//延时程序
{
	unsigned int i,j;
	for(i=0;i<m;i++)
	for(j=0;j<255;j++);
}

void main()
{
	while(1)
	{
		//轮流给送值P1口
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

sbit E_RED=P0^0;  		//东西红灯
sbit E_YELLOW=P0^1;		//东西黄灯
sbit E_GREEN=P0^2;		//东西绿灯
sbit N_RED=P0^3;		  //南北红灯
sbit N_YELLOW=P0^4;		//南北黄灯
sbit N_GREEN=P0^5;		//南北绿灯

sbit btn = P1^0; //外部中断开关


sbit SCON1 = P2^0;			//控制数码管的个位十位显示
sbit SCON2 = P2^1;

uchar num=10,ge,shi; 		  //定义倒计时初始值，个位十位
uchar a=0;				        //定义亮灯的四种情况	
uchar count=0;     			  //用来显示数码管的变量
uchar flag;					      //看倒计时是否为1s

//LED的9个数字
unsigned char code ledTab[]={
	0xC0, // 1100 0000 数字0
	0xF9, // 1111 1001 数字1
	0xA4, // 1010 0100 数字2
	0xB0, // 1011 0000 数字3
	0x99, // 1001 1001 数字4
  0x92, // 1001 0010 数字5
	0x82, // 1000 0010 数字6
	0xF8, // 1111 1000 数字7
	0x80, // 1000 0000 数字8
	0x90  // 1001 0000 数字9
};  



//1s延迟	
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

//紧急开关
void stop(){
	if(btn==0){
		Delay_Ms(1000);	 //取消抖动
		TR0=~TR0;           //停止倒计时
		N_RED = 0;N_YELLOW = 1;N_GREEN = 1;
    E_RED = 0;E_YELLOW = 1;E_GREEN = 1;
	}
}



void T0INTinit() //定时器T0初始化为1s
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
TL0=(65536-50000) % 256;   //定时为50ms
flag++;
	if(flag==20)//总共为1s
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
    	 case 0: //南北绿,东西红
				N_RED = 1;N_YELLOW = 1;N_GREEN = 0; 
        E_RED = 0;E_YELLOW = 1;E_GREEN = 1; 
        break;
    	 case 1: //南北黄,东西红
				N_RED=1;	N_YELLOW = ~N_YELLOW ; N_GREEN=1; 
				E_RED=0;  E_YELLOW = 1; E_GREEN=1; 
        break;
    	 case 2: //南北红,东西绿
				N_RED = 0;N_YELLOW = 1;	N_GREEN = 1;
				E_RED = 1; E_YELLOW =1; E_GREEN = 0; 
				break;
    	 case 3: //南北红，东西黄
				N_RED = 0;N_YELLOW = 1;	N_GREEN = 1; 
				E_RED = 1;E_YELLOW = ~N_YELLOW ; E_GREEN = 1;
				break;
	    }
	}
}


//主程序
void main(){
	T0INTinit();
	while(1){	
		stop();
		SEG=0xff; //消影
		shi = num / 10;
		ge = num % 10;
		switch(count){	
			//让数码管一起亮
			case 0: SCON1=0; SCON2=1; SEG=ledTab[ge]; break;
			case 1: SCON1=1; SCON2=0; SEG=ledTab[shi]; break;
		}
		count++;
		if(count>1) count=0;
	}
}


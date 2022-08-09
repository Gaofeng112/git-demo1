#include <regx52.h>
#include "LCD1602.h"

/**
  * @brief  串口初始化，//9600bps@11.0592MH32z
  * @param  无
  * @retval 无
  */
void UartInit(void)		
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;		//设置定时初始值
	TH1 = 0xFD;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;           //中断打开
	ES=1;
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0); //判断是否为传送数据
	TI = 0;         //发送中断标志位清零
}

void main()
{
	UartInit();
	LCD_Init();
	while(1)
	{
		LCD_ShowString(1, 1, "C51_RXD:");
		LCD_ShowString(2, 1, "C51_TXD:");
		LCD_ShowString(2, 10, "        ");
	};	
}

void UART_Routine() interrupt 4  //串口中断函数
{
	if(RI == 1)                  //如果接受标志位为1，接受到了数据
	{
		LCD_ShowChar(1, 9, SBUF);
		LCD_ShowChar(2, 9, SBUF + 17);
		//UART_SendByte(SBUF + 17);	
		RI=0;
	}
}
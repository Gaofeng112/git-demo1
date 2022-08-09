#include <regx52.h>
#include "LCD1602.h"

/**
  * @brief  ���ڳ�ʼ����//9600bps@11.0592MH32z
  * @param  ��
  * @retval ��
  */
void UartInit(void)		
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;		//���ö�ʱ��ʼֵ
	TH1 = 0xFD;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��%d�ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	EA=1;           //�жϴ�
	ES=1;
}

/**
  * @brief  ���ڷ���һ���ֽ�����
  * @param  Byte Ҫ���͵�һ���ֽ�����
  * @retval ��
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0); //�ж��Ƿ�Ϊ��������
	TI = 0;         //�����жϱ�־λ����
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

void UART_Routine() interrupt 4  //�����жϺ���
{
	if(RI == 1)                  //������ܱ�־λΪ1�����ܵ�������
	{
		LCD_ShowChar(1, 9, SBUF);
		LCD_ShowChar(2, 9, SBUF + 17);
		//UART_SendByte(SBUF + 17);	
		RI=0;
	}
}
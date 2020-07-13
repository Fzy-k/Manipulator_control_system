#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dj.h"
#include "air11.h"
#define n1 3340             //x�Ჽ�������������ʵ�ʾ���Ļ���ϵ��
#define n2 3630             //y�Ჽ�������������ʵ�ʾ���Ļ���ϵ��
#define n3 3340             //z�Ჽ�������������ʵ�ʾ���Ļ���ϵ��


/*
������֣���pa1,pa2,pa3��Ϊ��������ˣ���pa4,pa5,pa6��Ϊ�����

���ڲ��֣���pa9��Ϊ��Ϣ���룬pa10��Ϊ��Ϣ���

��ǹ���֣���pa12,pa11��Ϊ�̵������ƶ�
*/

u32 x,y,z;//λ����  
int dir1,dir2,dir3;//����
u8 dat=1;
void data_conversion(void);//����ת��
u16 fla = 0;

int main(void)
{
	delay_init();//��ʱ������ʼ��
	uart_init(115200);//���ڳ�ʼ��
	dj_init();//�����ʼ��
	air_init();//�̵������ƶ˿�
	led_init();//led�Ƴ�ʼ��
	
	led0 = 1;

	//********************************begin**************************************                                                           
  while(1)
	{
		led0 = 0;
	  air1_move();
		air2_move();
		
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		if(USART_RX_STA & 0x8000)
	{
			led0 = 0;  //����״̬		
		  delay_us(100);
			data_conversion();//���ڽ��ջ�������		
			delay_us(100);
		  
		  if(fla == 0)
			{
			  dj_move(x*n1,dir1,y*n2,dir2,(z-10)*n3,dir3);	//���������������
				delay_ms(1000);
				
				air1_move();
				delay_ms(500);
				
				dj_move(0*n1,1,0*n2,1,10*n3,1);
        delay_ms(1000);
				
				air2_move(); 
				delay_ms(1000);
				
				dj_move(0*n1,1,0*n2,1,10*n3,1);
			  delay_ms(500);

				         
			  USART_SendData(USART1,dat); //���������Ϣ
		    printf("\n\r���룺x = %d, y = %d, z = %d\r\n",x,y,z);
		    printf("\n\r����dir1 = %d, dir2 = %d, dir3 = %d\r\n",dir1,dir2,dir3);
			  delay_ms(100);
			
			  USART_RX_STA = 0;//����״̬λ
			}
			else 
			{
				
				dj_move(x*n1,dir1,y*n2,dir2,z*n3,dir3);
				delay_ms(1000);
				delay_ms(500);
			  air1_move();
				dj_move(0*n1,1,0*n2,1,10*n3,1);
			  delay_ms(500);
				
				air2_move(); 
				dj_move(0,1,0,1,10*n3,0);
				delay_ms(500);
				fla++;

				dat = '1';           //���������Ϣ
				USART_SendData(USART1,dat);
				printf("\n\r���룺x = %d, y = %d, z = %d\r\n",x,y,z);
				printf("\n\r����dir1 = %d, dir2 = %d, dir3 = %d\r\n",dir1,dir2,dir3);
			
				delay_ms(100);
				
				USART_RX_STA = 0;//����״̬λ
		  }
   	}		
			
	
	}	
	//******************************** end ************************************* 
}
    
void data_conversion()//����ת��
{
	u16 len,i;
	u32 ge1,ge2,ge3,shi1,shi2,shi3,bai1,bai2,bai3;
	
	len=USART_RX_STA&0x3f;
	for(i = 0;i <= len;i++)
	{
		USART_RX_BUF[i] -= 48;//�ַ�������ת����
	}
	
	dir1 = USART_RX_BUF[0];	
	bai1 = USART_RX_BUF[1];
	shi1 = USART_RX_BUF[2];
	ge1 = USART_RX_BUF[3];
	
	dir2 = USART_RX_BUF[4];	
	bai2 = USART_RX_BUF[5];
	shi2 = USART_RX_BUF[6];
	ge2 = USART_RX_BUF[7];
	
	dir3 = USART_RX_BUF[8];	
	bai3 = USART_RX_BUF[9];
	shi3 = USART_RX_BUF[10];
	ge3 = USART_RX_BUF[11];
	
	x = bai1*100+shi1*10+ge1;
	y = bai2*100+shi2*10+ge2;
	z = bai3*100+shi3*10+ge3;
}
	




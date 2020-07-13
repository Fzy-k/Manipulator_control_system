#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dj.h"
#include "air11.h"
#define n1 3340             //x轴步进电机脉冲数与实际距离的换算系数
#define n2 3630             //y轴步进电机脉冲数与实际距离的换算系数
#define n3 3340             //z轴步进电机脉冲数与实际距离的换算系数


/*
电机部分：将pa1,pa2,pa3作为脉冲输出端，将pa4,pa5,pa6作为方向端

串口部分：将pa9作为信息输入，pa10作为信息输出

气枪部分：将pa12,pa11作为继电器控制端
*/

u32 x,y,z;//位移量  
int dir1,dir2,dir3;//方向
u8 dat=1;
void data_conversion(void);//数据转换
u16 fla = 0;

int main(void)
{
	delay_init();//延时函数初始化
	uart_init(115200);//串口初始化
	dj_init();//电机初始化
	air_init();//继电器控制端口
	led_init();//led灯初始化
	
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
			led0 = 0;  //运行状态		
		  delay_us(100);
			data_conversion();//串口接收缓存数据		
			delay_us(100);
		  
		  if(fla == 0)
			{
			  dj_move(x*n1,dir1,y*n2,dir2,(z-10)*n3,dir3);	//根据数据驱动电机
				delay_ms(1000);
				
				air1_move();
				delay_ms(500);
				
				dj_move(0*n1,1,0*n2,1,10*n3,1);
        delay_ms(1000);
				
				air2_move(); 
				delay_ms(1000);
				
				dj_move(0*n1,1,0*n2,1,10*n3,1);
			  delay_ms(500);

				         
			  USART_SendData(USART1,dat); //发送完成信息
		    printf("\n\r距离：x = %d, y = %d, z = %d\r\n",x,y,z);
		    printf("\n\r方向：dir1 = %d, dir2 = %d, dir3 = %d\r\n",dir1,dir2,dir3);
			  delay_ms(100);
			
			  USART_RX_STA = 0;//重置状态位
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

				dat = '1';           //发送完成信息
				USART_SendData(USART1,dat);
				printf("\n\r距离：x = %d, y = %d, z = %d\r\n",x,y,z);
				printf("\n\r方向：dir1 = %d, dir2 = %d, dir3 = %d\r\n",dir1,dir2,dir3);
			
				delay_ms(100);
				
				USART_RX_STA = 0;//重置状态位
		  }
   	}		
			
	
	}	
	//******************************** end ************************************* 
}
    
void data_conversion()//数据转换
{
	u16 len,i;
	u32 ge1,ge2,ge3,shi1,shi2,shi3,bai1,bai2,bai3;
	
	len=USART_RX_STA&0x3f;
	for(i = 0;i <= len;i++)
	{
		USART_RX_BUF[i] -= 48;//字符型数据转整型
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
	




#include "sys.h"
#include "dj.h"
#include "delay.h"

//端口初始化
void dj_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
}

//控制电机运动
void dj_move(float x,int dir1,float y,int dir2,float z,int dir3)
{
	//判别各电机方向	
	if(dir1) PAout(4) = 0;
	else PAout(4) = 1;
	
	if(dir2) PAout(5) = 0;
	else PAout(5) = 1;
	
	if(dir3) PAout(6) = 0;
	else PAout(6) = 1;
	
	//发送脉冲信号给步进电机驱动器
	for(;x>0||y>0||z>0;x--,y--,z--)
	{
    
		PAout(1) = 0;
		PAout(2) = 0;
		PAout(3) = 0;
    delay_us(5);
		
		if(x>0)
		{
			PAout(1) = 1;
		}
		else PAout(1) = 0;
    delay_us(8);
    if(y>0)		
    {
      PAout(2) = 1;
		}
		else PAout(1) = 0;
		delay_us(8);
		if(z>0)
		{
			PAout(3) = 1;
		}
		else PAout(1) = 0;
		delay_us(8);
	}
	
	PAout(1) = 0;
	PAout(2) = 0;
	PAout(3) = 0;
}






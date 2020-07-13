#include "sys.h"
#include "dj.h"
#include "delay.h"

//�˿ڳ�ʼ��
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

//���Ƶ���˶�
void dj_move(float x,int dir1,float y,int dir2,float z,int dir3)
{
	//�б���������	
	if(dir1) PAout(4) = 0;
	else PAout(4) = 1;
	
	if(dir2) PAout(5) = 0;
	else PAout(5) = 1;
	
	if(dir3) PAout(6) = 0;
	else PAout(6) = 1;
	
	//���������źŸ��������������
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






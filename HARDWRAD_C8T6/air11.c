#include "sys.h"
#include "air11.h"
#include "delay.h"
#include "usart.h"
#include "dj.h"

//�˿ڳ�ʼ��
void air_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_15|GPIO_Pin_14);
}

//��������ĩ������
void air1_move(void)
{
	PBout(14) = 1;
	PAout(11) = 1;
	delay_ms(500);
	PAout(11) = 0;
	PBout(14) = 0;
}

//��������ĩ������
void air2_move(void)
{
	PBout(15) = 1;
	PAout(12) = 1;
	delay_ms(1000);
	 PAout(12) = 0;
	PBout(15) = 0;
	
}




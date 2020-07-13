#include "sys.h"
#include "security.h"

void security_init()
{
	EXTI_InitTypeDef exti_initstructure;
	NVIC_InitTypeDef nvic_initstructure;
	GPIO_InitTypeDef gpio_initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4|GPIO_PinSource3|GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6|GPIO_PinSource7|GPIO_PinSource8);
	
	gpio_initstructure.GPIO_Mode = GPIO_Mode_IPU;
	gpio_initstructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	gpio_initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_initstructure);
	
	exti_initstructure.EXTI_Line = EXTI_Line5|EXTI_Line3|EXTI_Line4|EXTI_Line6|EXTI_Line7|EXTI_Line8;
	exti_initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_initstructure.EXTI_LineCmd = ENABLE;
	exti_initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&exti_initstructure);
	
	nvic_initstructure.NVIC_IRQChannel = EXTI4_IRQn|EXTI3_IRQn|EXTI9_5_IRQn;               
	nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 3;
	nvic_initstructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic_initstructure);
	
}
	
void EXTI4_IRQHandler(void)
{
	
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	
	EXTI_ClearITPendingBit(EXTI_Line4);
	
}


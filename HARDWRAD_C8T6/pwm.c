#include "sys.h"
#include "pwm.h"

void pwm_init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructrue;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructrue;
	TIM_OCInitTypeDef TIM_OCInitStructrue;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;//pa7Îªpmw²¨Êä³ö¶Ë¿Ú
	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructrue);
	
	TIM_TimeBaseInitstructrue.TIM_Period = arr;
	TIM_TimeBaseInitstructrue.TIM_Prescaler = psc;
	TIM_TimeBaseInitstructrue.TIM_ClockDivision = 0;
	TIM_TimeBaseInitstructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstructrue);
	
	TIM_OCInitStructrue.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructrue.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructrue.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStructrue);
	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
//	TIM_Cmd(TIM3,ENABLE);
}

//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
//	{
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//		flag++;
//	}
//}





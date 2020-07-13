#include "air.h"
#include "delay.h"
#include "usart.h"

#define PB6 PAout(12)
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
  
	 //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	//初始化TIM3
	TIM_TimeBaseStructure.TIM_Period=arr;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//根据T指定的参数初始化外设TIM3 OC2
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //使能TIM3在CCR2上的预装载寄存器
	TIM_Cmd(TIM3,ENABLE);      //使能TIM3
	
}


//刀端口初始化函数
void Dao_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);					//初始化设置为0
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);					//初始化设置为0

}

//comp=16为0角度;
//Angle=160为0角度;


void Movement_Order(void)
{
	PAout(11) = 1;
	delay_ms(1000);
	PAout(11) = 0;
	delay_ms(1000);
	
	PAout(12) = 1;
	delay_ms(1000);
	PAout(12) = 0;
	delay_ms(1000);


//	    u16 angle= 30;
//	    u16 i;
//			PB6 = !PB6;								//出刀
//			delay_ms(300);
//			
//			for(i=2000;i<3000;i+=50)//向上约90度
//			{
//				
//				TIM_SetCompare2(TIM3,i);
//				delay_ms(40);
//			}	
//			
//			delay_ms(500);		
//			
//			PB6 = !PB6;								//收刀
//			delay_ms(100);
//			PB6 = !PB6;								//出刀
//			delay_ms(100);
//			
//			PB6 = !PB6;								//收刀
//			delay_ms(100);
//			PB6 = !PB6;								//出刀
//			delay_ms(100);
//			
//			PB6 = !PB6;								//收刀
//			delay_ms(100);
//			PB6 = !PB6;								//出刀
//			delay_ms(500);
//			
//			for(i=3000;i>2000;i-=50)//向下约90度
//			{
//				
//				TIM_SetCompare2(TIM3,i);
//				delay_ms(40);
//			}	
//			
//			delay_ms(500);
//			
//			PB6 = !PB6;								//收刀
//			delay_ms(200);
//			
//			printf("Servo radian is %d\r\n\r\n",angle); //打印提示信息（舵机旋转弧度）

}


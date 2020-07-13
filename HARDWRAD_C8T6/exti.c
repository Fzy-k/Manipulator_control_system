#include "exti.h"
#include "delay.h"
#include "usart.h"
#include  "motor.h"

u8 level_exti=0;           //水平
u8 flex_exti= 0;           //伸缩
u8 ver_exti=0;             //垂直

//小灯用于中断调试
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
}
 
void EXTI_OUT_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟
	
   //初始化GPIOE2,3,4
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	 GPIO_Init(GPIOE, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	 GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

		
		//GPIOE.1   中断线以及中断初始化配置  下降沿触发      升降电机
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1); 	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


    //GPIOE.2 中断线以及中断初始化配置   下降沿触发       伸缩电机
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);			
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	
  	EXTI_Init(&EXTI_InitStructure);	 	
		
	
    //GPIOE.3	  中断线以及中断初始化配置 下降沿触发			  水平电机
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  
		

    //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP   整体归位按钮
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	
		

    //整体复位按钮
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道  整体复位按钮中断
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);      //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    // 升降电机
		NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;	
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2  
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		//伸缩电机
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);     //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

   // 水平电机
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}

//外部中断0服务程序 按下wake——up键,电机返回直到触发电机中断
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)	 	 //WK_UP按键
	{				 
     motor_go(3351*50,0,850*55,0,3273*60,0);	  //  升降    伸缩     车体
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}


//外部中断1服务程序 升降电机
void EXTI1_IRQHandler(void)
{
  delay_ms(10);//消抖
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0) 
	{	 
	  LED0=!LED0;
		ver_exti=1;	
	}	
	EXTI_ClearITPendingBit(EXTI_Line1);  
}

 
//外部中断 伸缩电机
void EXTI2_IRQHandler(void)
{
  delay_ms(10);//消抖
	if( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)	  
	{		
	  LED1=!LED1;
		flex_exti=1;			
	}	
	EXTI_ClearITPendingBit(EXTI_Line2);  
}


 
//外部中断 水平电机
void EXTI3_IRQHandler(void)
{
  delay_ms(10);//消抖
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)	 
	{		
    LED0=!LED0;
    LED1=!LED1;		
		level_exti=1;		
	}			
	EXTI_ClearITPendingBit(EXTI_Line3);  
}
 



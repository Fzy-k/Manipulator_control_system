#include "exti.h"
#include "delay.h"
#include "usart.h"
#include  "motor.h"

u8 level_exti=0;           //ˮƽ
u8 flex_exti= 0;           //����
u8 ver_exti=0;             //��ֱ

//С�������жϵ���
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 
void EXTI_OUT_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��
	
   //��ʼ��GPIOE2,3,4
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	 GPIO_Init(GPIOE, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	 GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

		
		//GPIOE.1   �ж����Լ��жϳ�ʼ������  �½��ش���      �������
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1); 	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���       �������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);			
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	
  	EXTI_Init(&EXTI_InitStructure);	 	
		
	
    //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش���			  ˮƽ���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  
		

    //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP   �����λ��ť
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	
		

    //���帴λ��ť
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��  ���帴λ��ť�ж�
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);      //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    // �������
		NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;	
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2  
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		//�������
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);     //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

   // ˮƽ���
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//������3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

//�ⲿ�ж�0������� ����wake����up��,�������ֱ����������ж�
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)	 	 //WK_UP����
	{				 
     motor_go(3351*50,0,850*55,0,3273*60,0);	  //  ����    ����     ����
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}


//�ⲿ�ж�1������� �������
void EXTI1_IRQHandler(void)
{
  delay_ms(10);//����
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0) 
	{	 
	  LED0=!LED0;
		ver_exti=1;	
	}	
	EXTI_ClearITPendingBit(EXTI_Line1);  
}

 
//�ⲿ�ж� �������
void EXTI2_IRQHandler(void)
{
  delay_ms(10);//����
	if( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)	  
	{		
	  LED1=!LED1;
		flex_exti=1;			
	}	
	EXTI_ClearITPendingBit(EXTI_Line2);  
}


 
//�ⲿ�ж� ˮƽ���
void EXTI3_IRQHandler(void)
{
  delay_ms(10);//����
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)	 
	{		
    LED0=!LED0;
    LED1=!LED1;		
		level_exti=1;		
	}			
	EXTI_ClearITPendingBit(EXTI_Line3);  
}
 



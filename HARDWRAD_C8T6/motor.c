#include "motor.h"
#include "exti.h"
#include "delay.h"

int signal=0;

float reset_dist1=3400*2;
float reset_dist2=3277*2;
float reset_dist3=3260*2;

float reset_dir1=0;
float reset_dir2=0;
float reset_dir3=0;

void motor_init()
{

		 GPIO_InitTypeDef  GPIO_InitStructure;	
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PG端口时钟
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;				     //PG. 9端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 	    		 //PG.11端口配置, 推挽输出
	
       
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;				 //PG.13 端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;							//GPIO.G10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOG.10
	    		 
					 
    GPIO_SetBits(GPIOA,GPIO_Pin_1); 						      //PG.12输出高 
		GPIO_SetBits(GPIOA,GPIO_Pin_2);	                //PG.11输出高
		GPIO_SetBits(GPIOA,GPIO_Pin_3); 						      //PG.15 输出高 
		
}

void motor_go(float dist1, int dir1,float dist2, int dir2, float dist3, int dir3)
{	
		unsigned int i;

		//控制升降电机运动方向Z轴
		if(dir1)
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		else
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
		
		//控制伸缩电机运动方向
		if(dir2)
					  GPIO_ResetBits(GPIOA,GPIO_Pin_5);

		else
					GPIO_SetBits(GPIOA,GPIO_Pin_5);


		
		//控制车体运动方向
		if(dir3)
			GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		else
			GPIO_SetBits(GPIOA,GPIO_Pin_6);

		
		for(i=0;i<dist1 || i<dist2|| i<dist3;i++)
		{  
				if(i<dist1&&level_exti==0)
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
				else if(i<dist1&&level_exti==1)
				{				  
				  reset_dir1++;
					if(reset_dir1==1)//方向位、距离重置只进入一次
          {  
					   i=0;
						 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
						 dist1=reset_dist1;
					}				
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
				}
				delay_us(12);
				
				if(i<dist2&&flex_exti==0)
					GPIO_SetBits(GPIOA,GPIO_Pin_2);
				else if(i<dist2&&flex_exti==1)
				{				  
				  reset_dir2++;
					if(reset_dir2==1)//方向位重置只进入一次
          {  
					   i=0; 
						 GPIO_ResetBits(GPIOA,GPIO_Pin_5);
						 dist2=reset_dist2;
					}					
					GPIO_SetBits(GPIOA,GPIO_Pin_2);
				}
		    delay_us(12); 
				
				if(i<dist3&&ver_exti==0)
					GPIO_SetBits(GPIOA,GPIO_Pin_3);
				else if(i<dist3&&ver_exti==1)
				{				  
				  reset_dir3++;
					if(reset_dir3==1)//方向位重置只进入一次
          {  
					   i=0; 
						 GPIO_ResetBits(GPIOA,GPIO_Pin_6);
						 dist3=reset_dist3;
					}
					GPIO_SetBits(GPIOA,GPIO_Pin_3);
				}
				
				delay_us(12); 

				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
				GPIO_ResetBits(GPIOA,GPIO_Pin_2);
				GPIO_ResetBits(GPIOA,GPIO_Pin_3);
				delay_us(12);	

		}

		signal=1;
		
		level_exti=0;           //水平
    flex_exti= 0;           //伸缩
    ver_exti=0;             //垂直
		

    reset_dir1=0;           //累加数归0
    reset_dir2=0;
    reset_dir3=0;

}
 	 

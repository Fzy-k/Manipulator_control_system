#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

//extern u16 pus1,dir1;

//u16 usart_manage()
//{
//	
//}

int main(void)
{
//	pwm_init(9999,163);//���� 5ms��pa7Ϊ���������
//	TIM_SetCompare2(TIM3,4999);
	led_init();
	
	while(1)
	{
		led1 = 1;//״̬���
	}
//	u16 i;
//	delay_init();
//	uart_init(11900);//bound is not real
//	pwm_init(4999,71);//���� 5ms
//	while(1)
//	{	
//		if(USART_RX_STA&0x8000)
//		{
//			
//		
//			pus1 = usart_manage();
//			if(dir1)
//			{
//				PBout(10) = 0;
//				TIM_Cmd(TIM3,ENABLE);//������ʱ������ʼ����pwm��
//				for(i=0;i<pus1;i++)
//				{
//					delay_ms(5);
//				}
//				TIM_Cmd(TIM3,DISABLE);
//			}
//			else
//			{
//				PBout(10) = 1;
////				TIM_Cmd(TIM3,ENABLE);//������ʱ������ʼ����pwm��
//				for(i=0;i<pus1;i++)
//				{
//					delay_ms(5);
//				}
////				TIM_Cmd(TIM3,DISABLE);
//			}
//		}
//	}
//	
}


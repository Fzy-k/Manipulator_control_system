#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
void LED_Init(void);//��ʼ��

extern u8 level_exti;           
extern u8 flex_exti;           
extern u8 ver_exti;       

void EXTI_OUT_Init(void);//�ⲿ�жϳ�ʼ��		


#endif

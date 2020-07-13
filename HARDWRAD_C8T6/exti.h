#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
void LED_Init(void);//初始化

extern u8 level_exti;           
extern u8 flex_exti;           
extern u8 ver_exti;       

void EXTI_OUT_Init(void);//外部中断初始化		


#endif

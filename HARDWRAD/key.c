#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键 0
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键 1
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键 2 
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键 3(WK_UP) 

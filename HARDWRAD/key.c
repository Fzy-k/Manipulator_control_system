#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ���� 0
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ���� 1
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ���� 2 
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ���� 3(WK_UP) 

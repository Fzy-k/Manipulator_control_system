#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ���� 0
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ���� 1
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ���� 2 
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ���� 3(WK_UP) 
//#define KEY0 PEin(4) //PE4
//#define KEY1 PEin(3) //PE3 
//#define KEY2 PEin(2) //PE2
//#define WK_UP PAin(0) //PA0 WK_UP

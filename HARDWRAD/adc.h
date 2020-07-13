#include "sys.h"
#include "delay.h"
extern u16 ch;

void adc_init();
u16 adc_get(u8 ch);
u16 adc_get_averge(u8 ch,u8 times);

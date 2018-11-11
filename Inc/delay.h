#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f1xx.h"
void delay_ms(uint32_t n);
void delay_ms_it(volatile unsigned long nms);
void delay_us_it(volatile unsigned long nus);

#endif

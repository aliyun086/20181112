#include "delay.h"

extern volatile unsigned int timenum;       
extern volatile unsigned long time_delay;  


/**
*  use systick , but not utilize interrupt.
*/
void delay_ms(uint32_t nms)
{
	int32_t temp;  
	SysTick->LOAD = 8000*nms;  
	SysTick->VAL=0X00;
	SysTick->CTRL=0X01;
	do  
	{  
		temp=SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16))));
	
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

/**
*   delay_ms_it
*/
void delay_ms_it(volatile unsigned long nms)  
{  

	if (SysTick_Config(HAL_RCC_GetHCLKFreq()/1000))  
	{ 
		while (1);  
	}  
	time_delay=nms;
	while(time_delay);  
	SysTick->CTRL=0x00; 
	SysTick->VAL =0X00;  
}  

/**
*   delay_us_it
*/
void delay_us_it(volatile unsigned long nus)  
{
	if (SysTick_Config(HAL_RCC_GetHCLKFreq()/1000000))  
	{  

	while (1);  
	}  
	time_delay=nus;
	while(time_delay);  
	SysTick->CTRL=0x00; 
	SysTick->VAL =0X00;  
}  

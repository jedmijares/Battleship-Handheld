#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
	
void SysTick_Init(void){
	//Initialize Systick
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
	NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

void delay1ms(int ms){
	//Use the Systick Timer to generate a 1ms delay
	int i = 0;
	for(i = 0; i < ms; i++)
	{
		NVIC_ST_RELOAD_R = 80000-1;  // number of counts to wait
		NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
		while((NVIC_ST_CTRL_R&0x00010000)==0){} // wait for count flag
	}
}

// initializes clock and interrupts

#ifndef _SysTick_h
#define _SysTick_h

#include "printMatrix.h"

void SysTick_Init(unsigned long period);
void SysTick_Handler(void);
unsigned long millis(void);
void delay1ms(int ms);
void beep(int time);

#endif

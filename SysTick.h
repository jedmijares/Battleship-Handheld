#ifndef _SysTick_h
#define _SysTick_h

void SysTick_Init(unsigned long period);
void SysTick_Handler(void);
unsigned long millis(void);
//void SysTick_Delay10ms(void);
void delay1ms(int ms);

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#endif

#ifndef _SysTick_h
#define _SysTick_h

#include "printMatrix.h"

void SysTick_Init(unsigned long period);
void SysTick_Handler(void);
unsigned long millis(void);
//void SysTick_Delay10ms(void);
void delay1ms(int ms);
void beep(int time);

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#endif

//int main(void)
//{
//	short reading; // reading of buttons
//	short buttonState;
//	short oldReading = 0x11; // previous reading of buttons
//	unsigned long lastDebounceTime = 0;
//	unsigned long debounceDelay = 50; // time to wait before more button input
//	unsigned long bInt = 1000; // time to toggle blue
//	unsigned long bPrevious = 0;
//	
//	PLL_Init();
//	PortF_Init();
//	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
//	
//	while(1)
//	{
//		if((millis() - bPrevious) >= bInt)
//		{
//			bPrevious = millis();
//			blueToggle();
//		}
//		
//		reading = pushbuttons(); // read value of buttons
//		if( reading != oldReading ) lastDebounceTime = millis(); // if reading does not match last value, we're still bouncing
//		if( (millis() - lastDebounceTime) > debounceDelay) // if the time since the last bounce is greater than the delay, step in
//		{
//			if (reading != buttonState) // if the reading does not match what the computer thinks the button was last, step in
//			{
//				buttonState = reading;
//				if(buttonState == 0x10)
//					greenToggle();
//			}
//		}
//		oldReading = reading;
//	}
//}

#include "Nokia5110.h"
#include "PLL.h"
#include "PortF.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"

//int main(void){
//	unsigned short xpos = 0;
//	unsigned short ypos = 0;
//	short buttons = 0;
//  PLL_Init();                           // set system clock to 80 MHz
//  Nokia5110_Init();
//  SysTick_Init();
//  PortF_Init();
//  Nokia5110_Clear();
//  
//	while(1)
//	{
//		buttons = pushbuttons();
//		if(buttons == 0x10)
//		{
//			xpos++;
//			delay1ms(10);
//		}
//		if(buttons == 0x01)
//		{
//			ypos++;
//			delay1ms(10);
//		}
//		Nokia5110_SetPixel(xpos,ypos);
//		Nokia5110_DisplayBuffer();
//	}
//}

int main(void)
{
	short reading; // reading of buttons
	short buttonState;
	short oldReading = 0x11; // previous reading of buttons
	unsigned long lastDebounceTime = 0;
	unsigned long debounceDelay = 50; // time to wait before more button input
	unsigned long bInt = 1000; // time to toggle blue
	unsigned long bPrevious = 0;
	
	PLL_Init();
	PortF_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
	while(1)
	{
		if((millis() - bPrevious) >= bInt)
		{
			bPrevious = millis();
			blueToggle();
		}
		
		reading = pushbuttons(); // read value of buttons
		if( reading != oldReading ) lastDebounceTime = millis(); // if reading does not match last value, we're still bouncing
		if( (millis() - lastDebounceTime) > debounceDelay) // if the time since the last bounce is greater than the delay, step in
		{
			if (reading != buttonState) // if the reading does not match what the computer thinks the button was last, step in
			{
				buttonState = reading;
				if(buttonState == 0x10)
					greenToggle();
			}
		}
		oldReading = reading;

	}
}

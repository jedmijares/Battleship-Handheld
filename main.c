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

volatile unsigned long ms = 0;

void SysTick_Handler(void)
{
  //GPIO_PORTF_DATA_R ^= 0x04;       // toggle PF2
  ms = ms + 1;
}

int main(void)
{
	short buttons;
	long bInt = 1000;
	unsigned long bPrevious = 0;
	
	PLL_Init();
	PortF_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms)
	while(1)
	{
		if((ms - bPrevious) >= bInt)
		{
			bPrevious = ms;
			blueToggle();
			//GPIO_PORTF_DATA_R ^= 0x04;       // toggle PF2
		}
		buttons = pushbuttons();
		if(buttons == 0x10)
		{
			
		}
		if(buttons == 0x01)
		{
			
		}
	}
}

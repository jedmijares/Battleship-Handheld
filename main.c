#include "Nokia5110.h"
#include "PLL.h"
#include "PortF.h"
#include "SysTick.h"

int main(void){
	unsigned short xpos = 0;
	unsigned short ypos = 0;
	short buttons = 0;
  PLL_Init();                           // set system clock to 80 MHz
  Nokia5110_Init();
  SysTick_Init();
  PortF_Init();
  Nokia5110_Clear();
  
	while(1)
	{
		buttons = pushbuttons();
		if(buttons == 0x10)
		{
			xpos++;
			delay1ms(10);
		}
		if(buttons == 0x01)
		{
			ypos++;
			delay1ms(10);
		}
		Nokia5110_SetPixel(xpos,ypos);
		Nokia5110_DisplayBuffer();
	}
}

#include "Nokia5110.h"
#include "PLL.h"
#include "PortF.h"
#include "SysTick.h"
#include "image.h"

int main(void){
	unsigned short xpos = 0;
	short buttons = 0;
  PLL_Init();                           // set system clock to 80 MHz
  Nokia5110_Init();
  SysTick_Init(80000);
  PortF_Init();
  Nokia5110_Clear();
	Nokia5110_PrintBMP(0, 47, grid);
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(8, 0);
	Nokia5110_OutString("Them");
	delay1ms(1000);
	Nokia5110_PrintBMP(0, 4, hit);
	Nokia5110_DisplayBuffer();
  Nokia5110_SetCursor(8, 0);
	Nokia5110_OutString("Them");
	delay1ms(1000);
	Nokia5110_PrintBMP(0, 10, miss);
	Nokia5110_DisplayBuffer();
  Nokia5110_SetCursor(8, 0);
	Nokia5110_OutString("Them");
	delay1ms(1000);
	Nokia5110_PrintBMP(7, 4, boat1s);
	Nokia5110_DisplayBuffer();
  Nokia5110_SetCursor(8, 0);
	Nokia5110_OutString("Them");
	while(1){
	Nokia5110_PrintBMP(0, 4, hitOutline);
	Nokia5110_DisplayBuffer();
	delay1ms(400);
	Nokia5110_PrintBMP(0, 4, hit);
	Nokia5110_DisplayBuffer();
	delay1ms(400);
	}
	
	
//	while(1)
//	{
//		buttons = pushbuttons();
//		if(buttons == 0x10)
//		{
//			xpos--;
//			delay1ms(67);
//		}
//		else if(buttons == 0x01)
//		{
//			xpos++;
//			delay1ms(67);
//		}
//		if(xpos > 84)
//			xpos = 80;
//		if(xpos < 1)
//			xpos = 1;
//		
//		Nokia5110_PrintBMP(0, 0, grid);
//		Nokia5110_DisplayBuffer();
//	}
}

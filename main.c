// main file for EE 287 final project
// By Jed Mijares and Jacob Culler

#include "Nokia5110.h"
#include "PLL.h"
#include "PortF.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "squares.h"
#include "printMatrix.h"

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



int main(void)
{
	int i, j;
	Sea board[8][8];
	short xCursor = 0;
	short yCursor = 0;
	short buttons = 0x11;
	
	PLL_Init();
	PortF_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
	Nokia5110_Init();
	
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			board[i][j].isHit = 0;
			board[i][j].isShip = 0;
		}
	}
	board[3][3].isShip = 1;
	board[3][3].isHit = 1;
	board[1][0].isHit = 1;
	board[1][1].isShip = 1;
	printGrid();
	print(board);
	select(board, xCursor, yCursor);
	while(1)
	{
		buttons = pushbuttons();
		if(buttons == 0x10) 
		{
			xCursor++;
			select(board, xCursor, yCursor);
			delay1ms(250);
		}
		if(buttons == 0x01) 
		{
			yCursor++;
			select(board, xCursor, yCursor);
			delay1ms(250);
		}
		
	}
}


//int main(void){
//  PLL_Init();                           // set system clock to 80 MHz
//  Nokia5110_Init();
//  SysTick_Init(80000);
//  PortF_Init();
//  Nokia5110_Clear();
//	Nokia5110_PrintBMP(0, 47, grid, 1);

//  
//	Nokia5110_OutString("Them");
//	delay1ms(1000);
//	Nokia5110_PrintBMP(0, 4, hit,1);
//	Nokia5110_DisplayBuffer();
//  Nokia5110_SetCursor(8, 0);
//	Nokia5110_OutString("Them");
//	delay1ms(1000);
//	Nokia5110_PrintBMP(0, 10, miss,1);
//	Nokia5110_DisplayBuffer();
//  Nokia5110_SetCursor(8, 0);
//	Nokia5110_OutString("Them");
//	delay1ms(1000);
//	Nokia5110_PrintBMP(7, 4, boat1s,1);
//	Nokia5110_DisplayBuffer();
//  Nokia5110_SetCursor(8, 0);
//	Nokia5110_OutString("Them");
//	while(1){
//	Nokia5110_PrintBMP(0, 4, hitOutline,1);
//	Nokia5110_DisplayBuffer();
//	delay1ms(400);
//	Nokia5110_PrintBMP(0, 4, hit,1);
//	Nokia5110_DisplayBuffer();
//	delay1ms(400);
//	}
//}
	
	

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

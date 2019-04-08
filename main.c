// main file for EE 287 final project
// By Jed Mijares and Jacob Culler

#include "Nokia5110.h"
#include "PLL.h"
#include "PortF.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "squares.h"
#include "printMatrix.h"

Sea board[8][8];
short xCursor = 0;
short yCursor = 0;

void checkBounds(short *x , short *y){
	if(*x > 7)
		*x = 7;
	if(*x < 0)
		*x = 0;
	if(*y < 0)
		*y = 0;
	if(*y > 7)
		*y = 7;
}

void fire(){
	checkBounds(&xCursor, &yCursor);
	board[xCursor][yCursor].isHit = 1;
	select(board, xCursor, yCursor);
}

void xPlus(){
	xCursor++;
	checkBounds(&xCursor, &yCursor);
	select(board, xCursor, yCursor);
}
void yPlus(){
	yCursor++;
	checkBounds(&xCursor, &yCursor);
	select(board, xCursor, yCursor);
}

int main(void)
{	
	int shotsFired = 0;
	int goodShots = 0;
	//char* shotsString;//[sizeof(int)*8+1];
	Sea board[8][8];
	short reading; // reading of buttons
	short buttonState;
	short oldReading = 0x11; // previous reading of buttons
	unsigned long lastDebounceTime = 0;
	unsigned long debounceDelay = 50; // time to wait before more button input
	const int SHOTSNEEDED = 2; // total squares that are ships
	short won = 0; // 1 if game is won
	
	PLL_Init();
	PortF_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
	Nokia5110_Init();
	
	for(short i = 0; i < 8; i++){
		for(short j = 0; j < 8; j++){
			board[i][j].isHit = 0;
			board[i][j].isShip = 0;
		}
	}
	board[1][1].isShip = 1;
	board[0][0].isShip = 1;
	board[0][2].isShip = 1;
	board[0][1].isShip = 1;
	//board[0][0].isHit = 1;
	board[4][1].isHit = 1;
	printGrid();
	print(board);
	select(board, xCursor, yCursor);
	Nokia5110_SetCursor(8,0);
	Nokia5110_OutChar('0');
	Nokia5110_DisplayBuffer();
	
	
	while(1)
	{
		reading = pushbuttons(); // read value of buttons
		if(reading != oldReading ) lastDebounceTime = millis(); // if reading does not match last value, we're still bouncing
		if((millis() - lastDebounceTime) > debounceDelay) // if the time since the last bounce is greater than the delay, step in
		{
			if (reading != buttonState) // if the reading does not match what the computer thinks the button was last, step in
			{
				buttonState = reading;
				if(buttonState == 0x10 && xCursor < 7)
				{
					xPlus();
				}
				if(buttonState == 0x01) 
				{
					//if(board[xCursor][yCursor].isHit == 0 & board[xCursor][yCursor].isShip == 1) goodShots++;
					fire();
					//shotsFired++;
				}
			}
		}
		
		if((goodShots >= SHOTSNEEDED) && (won == 0)) // if you won
		{
			Nokia5110_SetCursor(8,2);
			Nokia5110_OutChar('W');
			//won = 1;
		}
		
		oldReading = reading; // for button debouncing
		//sprintf(shotsString, "%d", shotsFired);
		Nokia5110_SetCursor(7,0);
		Nokia5110_OutUDec(shotsFired);
		//Nokia5110_OutChar((char)shotsFired);
		if (millis()%4 == 1) Nokia5110_DisplayBuffer();
	}
}

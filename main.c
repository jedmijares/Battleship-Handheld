// main file for EE 287 final project
// By Jed Mijares and Jacob Culler

#include "Nokia5110.h"
#include "PLL.h"
#include "Ports.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "squares.h"
#include "printMatrix.h"
#include "random.h"

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
void xMinus(){
	xCursor--;
	checkBounds(&xCursor, &yCursor);
	select(board, xCursor, yCursor);
}
void yMinus(){
	yCursor--;
	checkBounds(&xCursor, &yCursor);
	select(board, xCursor, yCursor);
}

int main(void)
{	
	int shotsFired = 0;
	int goodShots = 0; // number of successful hits against ships

	short buttonState; // actually used to check input
	short oldReading = 0x11; // previous reading of buttons
	unsigned long lastDebounceTime = 0; 
	unsigned long debounceDelay = 50; // time to wait before more button input
	const short SHOTSNEEDED = 3; // shots needed to win game
	short reading; // reading of buttons
	
	PLL_Init(); // set clock to 80 MHz
	Ports_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
	Nokia5110_Init();
	Random_Init(NVIC_ST_CURRENT_R);
	
	for(short i = 0; i < 8; i++){
		for(short j = 0; j < 8; j++){
			board[i][j].isHit = 0;
			board[i][j].isShip = 0;
		}
	}
	board[0][0].isShip = 1;
	board[1][0].isShip = 1;
	board[2][0].isShip = 1;
	printGrid();
	print(board);
	select(board, xCursor, yCursor);
	Nokia5110_DisplayBuffer();
	
	
	while(1)
	{
		reading = readBButtons(); // read value of buttons
		if(reading != oldReading ) lastDebounceTime = millis(); // if reading does not match last value, we're still bouncing
		if((millis() - lastDebounceTime) > debounceDelay) // if the time since the last bounce is greater than the delay, step in
		{
			if (reading != buttonState) // if the reading does not match what the computer thinks the button was last, step in
			{
				buttonState = reading;
				if(rightPressed() && xCursor < 7)
				{
					xPlus();
					Nokia5110_DisplayBuffer();
					beep(50);
				}
				if(downPressed() && yCursor < 7)
				{
					yPlus();
					Nokia5110_DisplayBuffer();
					beep(50);
				}
				if(leftPressed() && xCursor >0)
				{
					xMinus();
					Nokia5110_DisplayBuffer();
					beep(50);
				}
				if(upPressed() && yCursor > 0)
				{
					yMinus();
					Nokia5110_DisplayBuffer();
					beep(50);
				}
				if(selectPressed()) 
				{
					if(board[xCursor][yCursor].isHit == 0 & board[xCursor][yCursor].isShip == 1) 
					{
						goodShots++;
					}
					fire();
					shotsFired++;
					Nokia5110_DisplayBuffer();
					beep(50);
				}
			}
		}
		oldReading = reading;
		
		Nokia5110_SetCursor(8,2);
		Nokia5110_OutString("Hits");
		Nokia5110_SetCursor(8,4);
		Nokia5110_OutString("Miss");
		Nokia5110_SetCursor(8,3);
		Nokia5110_OutUDec2(shotsFired); // modified version of OutUDec that doesn't add space
		Nokia5110_SetCursor(8,5);
		Nokia5110_OutUDec2(goodShots);
		if(goodShots >= SHOTSNEEDED)
		{
			Nokia5110_SetCursor(8,1);
			Nokia5110_OutString("WIN");
		}
	}
}
 

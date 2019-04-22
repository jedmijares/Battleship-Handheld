// main file for EE 287 final project
// By Jed Mijares and Jacob Culler

#include "Nokia5110.h"
#include "PLL.h"
#include "Ports.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "structs.h"
#include "printMatrix.h"
#include "random.h"
#include <stdbool.h>

struct Square board[8][8];
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
	const short SHOTSNEEDED = 9; // shots needed to win game
	short reading; // reading of buttons
	
	PLL_Init(); // set clock to 80 MHz
	Ports_Init();
	SysTick_Init(80000); // interrupt every 80,000 cycles (1 ms at 80 MHz)
	Nokia5110_Init();
	
	for(short i = 0; i < 8; i++){  // reset board
		for(short j = 0; j < 8; j++){
			board[i][j].isHit = 0;
			board[i][j].isShip = 0;
		}
	}
	
	Nokia5110_Clear();
	Nokia5110_SetCursor(1,1);
	Nokia5110_OutString("Jed");
	Nokia5110_SetCursor(2,2);
	Nokia5110_OutString("M.");
	
	Nokia5110_SetCursor(6,1);
	Nokia5110_OutString("Jacob");
	Nokia5110_SetCursor(8,2);
	Nokia5110_OutString("C.");
	
	Nokia5110_SetCursor(3,3);
	Nokia5110_OutString("Present");
	Nokia5110_SetCursor(1,4);
	Nokia5110_OutString("Battleship");
	
	//delay1ms(2000);
	while(!readBButtons()) {}
	Nokia5110_Clear();
	
	Random_Init(NVIC_ST_CURRENT_R); // random seed depending on when user presses button to start
	
	struct Ship ship2;
	struct Ship ship3;
	struct Ship ship4;
	ship2.length = 2;
	ship3.length = 3;
	ship4.length = 4;
	randomPlaceShip(ship2, board);
	randomPlaceShip(ship3, board);
	randomPlaceShip(ship4, board);
	printGrid();
	print(board);
	select(board, xCursor, yCursor);
	Nokia5110_DisplayBuffer();
	
	delay1ms(1000);
	
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
		Nokia5110_OutString("Shot");
		Nokia5110_SetCursor(8,3);
		Nokia5110_OutUDec2(shotsFired); // modified version of OutUDec that doesn't add space beforehand
		
		Nokia5110_SetCursor(8,4);
		Nokia5110_OutString("Hits");
		Nokia5110_SetCursor(8,5);
		Nokia5110_OutUDec2(goodShots);
		if(goodShots >= SHOTSNEEDED)
		{
			Nokia5110_SetCursor(8,1);
			Nokia5110_OutString("WIN");
		}
	}
}
 

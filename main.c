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
	print(board);
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

int main(void){
	int i, j;
	
	PLL_Init();
	PortF_Init();
	SysTick_Init(80000); // interrupt/toggle every 80,000 cycles (1 ms at 80 MHz)
	Nokia5110_Init();
	
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
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
	Nokia5110_SetCursor(8,0);
	Nokia5110_OutChar('0');
	Nokia5110_DisplayBuffer();
	while(1)
	{
		Nokia5110_SetCursor(8,0);
		Nokia5110_OutChar('0');
		delay1ms(1000);
		if(pushbuttons() == 0x10) 
			xPlus();
		else if(pushbuttons() == 0x01) 
			yPlus();
		else if(pushbuttons() == 0x00)
			fire();
		
		Nokia5110_DisplayBuffer();

	}
}



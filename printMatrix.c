#include "printMatrix.h"
#include "squares.h"
#include "Nokia5110.h"
#include "Sprites.h"

//x starts at 0 and increments by 7
//y starts at 4 and increments by 6
//text starts at 8,0

void print(squares in[][]){
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			if(in[i][j].isHit && in[i][j].isShip){
				Nokia5110_PrintBMP(i*7, j*6+4, hit);				
			}
			else if(in[i][j].isHit && !in[i][j].isShip){
				Nokia5110_PrintBMP(i*7, j*6+4, miss);
			}
		}
	}
	Nokia5110_DisplayBuffer();
}

void select(squares in[][], int x, int y){
	print(in);
	if(in[x][y].isHit && in[x][y].isShip)
		Nokia5110_PrintBMP(x*7, y*6+4, hitOutline);
	if(in[i][j].isHit && !in[i][j].isShip)
		Nokia5110_PrintBMP(x*7, y*6+4, missOutline);
	Nokia5110_DisplayBuffer();
}
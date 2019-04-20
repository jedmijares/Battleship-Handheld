#include "structs.h"

void randomPlaceShip(struct Ship ship, struct Square board[8][8])
{
	ship.isVertical = false;
	ship.hits = 0;
	ship.sunk = false;
	ship.xpos = (Random32()%(8-ship.length+1));
	ship.ypos = 0;
	for(int i = ship.xpos; (i-ship.xpos) < ship.length; i++)
	{
		if(!ship.isVertical)
		{
			board[i][ship.ypos].isShip = true;
		}
		else
			board[ship.xpos][i].isShip = true;
	}
}

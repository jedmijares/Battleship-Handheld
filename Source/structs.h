#ifndef _structs_h
#define _structs_h

#include <stdbool.h>
#include "random.h"

struct Square
{
	short shipID; // ID of the ship there, or 0 otherwise
	bool isHit; // has square been targeted yet
};

#define MAXLENGTH 4
struct Ship
{
	short xpos;
	short ypos;
	short length;
	short ID;
	bool isVertical;
	short hits;
	//bool sunk;
};

void randomPlaceShip(struct Ship ship, struct Square board[8][8]);

#endif

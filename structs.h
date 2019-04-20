#ifndef _structs_h
#define _structs_h

#include <stdbool.h>
#include "random.h"

struct Square
{
	bool isShip;
	bool isHit;
};

#define MAXLENGTH 4
struct Ship
{
	short xpos;
	short ypos;
	short length;
	bool isVertical;
	short hits;
	bool sunk;
};

void randomPlaceShip(struct Ship ship, struct Square board[8][8]);

#endif

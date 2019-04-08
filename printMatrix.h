#ifndef _printMatrix_h
#define _printMatrix_h

#include "squares.h"
#include "Nokia5110.h"

void printGrid(void);
void print(Sea in[8][8]);
void select(Sea in[8][8], short x, short y);
void deselect(Sea in[8][8], short x, short y);

#endif

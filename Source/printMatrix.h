#ifndef _printMatrix_h
#define _printMatrix_h

#include "structs.h"
#include "Nokia5110.h"

void printGrid(void);
void print(struct Square in[8][8]);
void select(struct Square in[8][8], short x, short y);
void deselect(struct Square in[8][8], short x, short y);

#endif

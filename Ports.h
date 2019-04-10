// allows interaction with GPIO pins

#ifndef _Ports_h
#define _Ports_h

#include "stdint.h"

void Ports_Init(void);
uint32_t pushbuttons(void);
void redOn(void);
void redOff(void);
void blueOn(void);
void blueOff(void);
void greenOn(void);
void greenOff(void);
void blueToggle(void);
void redToggle(void);
void greenToggle(void);
void buzzerToggle(void);
short downPressed(void);
short rightPressed(void);
short readBButtons(void);
#endif

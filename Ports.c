#include "Ports.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"


#define PF40 (*((volatile unsigned long *)0x40025044))
#define RLED (*((volatile unsigned long *)0x40025008))
#define GLED (*((volatile unsigned long *)0x40025020))
#define BLED (*((volatile unsigned long *)0x40025010))
#define BUZZER (*((volatile unsigned long *)0x40004040)) // PA4
#define BBUTTONS (*((volatile unsigned long *)0x400053CC)) // B 0 1 4 5 6 7
#define RIGHT (*((volatile unsigned long *)0x40005200)) // B7
#define DOWN (*((volatile unsigned long *)0x40005100)) // B6

void Ports_Init(void){
	//Initialize PF3, PF2, and PF1 as outputs
	//Initialize PF4 and PF0 as inputs
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000023;     // 1) A, B, F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0 
	
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
	
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	GPIO_PORTA_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
	GPIO_PORTA_DIR_R |= 0x10;         // PA4 out
	GPIO_PORTB_DIR_R &= ~0xF3; 				// B0 1 4 5 6 7 in            
	
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTA_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
	
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0    
	
  GPIO_PORTF_DEN_R |= 0x1F;          // 7) enable digital pins PF4-PF0        
	GPIO_PORTA_DEN_R |= 0x10;
	GPIO_PORTB_DEN_R |= 0xF3;
}

void buzzerToggle(void) // toggles A4
{
	BUZZER ^= 0x10;
}

short readBButtons(void) {return (BBUTTONS & 0xF3);}
short downPressed(void) {return (DOWN & 0x40);}
short rightPressed(void) {return (RIGHT & 0x80);}

uint32_t pushbuttons(void){
	//Return the state of the PortF buttons
	return(PF40 & 0x11);
}

void blueOn(void){
	BLED |= 0xFF;
}

void redOn(void){
	RLED |= 0xFF;
}

void greenOn(void){
	GLED |= 0xFF;
}

void blueOff(void){
	BLED &= 0x00;
}

void redOff(void){
	RLED &= 0x00;
}

void greenOff(void){
	GLED &= 0x00;
}

void blueToggle(void){
	BLED ^= 0xFF;
}

void redToggle(void){
	RLED ^= 0xFF;
}

void greenToggle(void){
	GLED ^= 0xFF;
}

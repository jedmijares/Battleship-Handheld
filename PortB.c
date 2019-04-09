#include "PortB.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"


//#define PF40 (*((volatile unsigned long *)0x40025044))
//#define RLED (*((volatile unsigned long *)0x40025008))
//#define GLED (*((volatile unsigned long *)0x40025020))
//#define BLED (*((volatile unsigned long *)0x40025010))


void PortB_Init(void){
	//Initialize PF3, PF2, and PF1 as outputs
	//Initialize PF4 and PF0 as inputs
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x000000202;     // 1) B clock
  delay = SYSCTL_RCGC2_R;           // delay   
  //GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTB_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTB_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}

//uint32_t pushbuttons(void){
//	//Return the state of the buttons
//	//return(PF40 & 0x11);
//}


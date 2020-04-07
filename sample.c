#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button/button.h"
#include "timer/timer.h"

unsigned int i=0;
unsigned int n=1;
unsigned int j=0;

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void)
{  
	LED_init();							/* LED Initialization                 */
	BUTTON_init();						/* BUTTON Initialization              */
	/* TIMER Initialization 
	TIMER0 inizialized in interrupt and reset mode
	TIMER1 inizialized in interrupt and reset mode*/
	
	init_timer(0,0x023C3460); //TimerInterval=1.5sec*25MHz=0x023C3460 go to MR0 to generate interrupt each 1.5sec and in the same time reset it self 
	init_timer(1,0xFFFFFFFF); //TIMER1 is used to generation of random number and debouncing of button, MR0 is 0xFFFFFFF because it counts until the limit and restart from 0x0 by resetting 
	                  
	enable_timer(1); //Enable_timer 1
	
	
	LPC_SC->PCON |= 0x1;	// power-down mode 							
	LPC_SC->PCON &= 0xFFFFFFFFD; 
	SCB->SCR |= 0x2;			// set SLEEPONEXIT	
	
	__ASM("wfi");
	while(1);
}

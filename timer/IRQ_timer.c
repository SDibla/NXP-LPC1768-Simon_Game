/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Descriptions:        interrupt handlers of Timer/Counter 0 and 1
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"

extern unsigned int n,i,j;
unsigned int previous=0,odd=0,end=0;

void TIMER0_IRQHandler (void) //To show sequence of led 
{
	if(odd==0){ //odd interrupts
		generate_Seq();	//display the led
		i++;
		odd=1;
	}
	else{ //even interrupts
		all_LED_off(); //switch off all led
		odd=0;
	}
	if(i==n && odd==0){
		disable_timer(0); //so it no longer generates interrupts
		LPC_TIM0->TC = 0x00000000;
		previous=i;
	}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER1_IRQHandler (void) //To obtain random number 0-2
{
	end=1; 
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../timer/timer.h"
#define delay 10000000
extern unsigned int n,i,j,end;
extern unsigned int seq[];
unsigned int next_time=0;

/*
INT0=0=LED4(in led_On function is 7-0)
KEY1=1=LED5(in led_On function is 7-1)
KEY2=2=LED6(in led_On function is 7-2)
*/

void EINT0_IRQHandler (void)	  
{
	if(LPC_TIM1->TC >= delay || end == 1){ //debouncing
		if(i==0 && j==0){  //To start the game or continue with large seq
			enable_timer(0); //Enable_timer 0
			all_LED_off();
		}else if(n==i && j<n){ //I can press button only when all the led seq was displayed and until we not reach the total number of press
			if(seq[j]==0)
				j++;
			else
				show_J();
			if(j==n)
				show_N();
		}
		end=0;
	}
	LPC_SC->EXTINT |= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	if(LPC_TIM1->TC >= delay || end == 1){ //debouncing
		if(n==i && j<n){ //I can press button only when all the led seq was displayed and until we not reach the total number of press
			if(seq[j]==1)
				j++;
			else
				show_J();
			if(j==n)
				show_N();
		}
		end=0;
	}
	LPC_SC->EXTINT |= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	if(LPC_TIM1->TC >= delay || end == 1){//debouncing
		if(n==i && j<n){ //I can press button only when all the led seq was displayed and until we not reach the total number of press
			if(seq[j]==2)
				j++;
			else
				show_J();
			if(j==n)
				show_N();
		}
		end=0;
	}
	LPC_SC->EXTINT |= (1 << 2);     /* clear pending interrupt         */    
}



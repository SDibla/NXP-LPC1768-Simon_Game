/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_led.c
** Descriptions:        Atomic led init functions
** Correlated files:    
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#define LED_NUM     8                   /* Number of user LEDs                */
#include "LPC17xx.h"
#include "led.h"
#include "../timer/timer.h"

const unsigned long led_mask[] = {1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7};

extern unsigned int n,i,j,previous;
unsigned int seq[256]={0};

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/

void LED_init(void)
{
	LPC_PINCON->PINSEL4 &= 0xFFFF0000;	// PIN mode GPIO: P2.0-P2.7 are set to zero
	LPC_GPIO2->FIODIR |= 0x000000FF;		// P2.0-P2.7 on PORT2 defined as Output
}

void LED_deinit(void)
{
  LPC_GPIO2->FIODIR &= 0xFFFFFF00;
}

/*----------------------------------------------------------------------------
  Functions that turn on/off all led
 *----------------------------------------------------------------------------*/

void all_LED_on(void)
{
	LPC_GPIO2->FIOSET = 0x000000FF;
}

void all_LED_off(void)
{
	LPC_GPIO2->FIOCLR = 0x000000FF;
}

/*----------------------------------------------------------------------------
  Functions that turn on/off the requested led
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num)
{
  LPC_GPIO2->FIOPIN |= led_mask[num];
}

void LED_Off(unsigned int num)
{
  LPC_GPIO2->FIOPIN &= ~led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that generate random led and repeat the seq 
 *----------------------------------------------------------------------------*/
void generate_Seq(void){
	int rnd;
	if(i<previous) //repeat original seq
		LED_On(7-seq[i]); //show various led of original seq
	else{ //add new random led
		rnd = LPC_TIM1->TC;
		rnd=rnd%3; //0->led4, 1->led5, 2->led6
		LED_On(7-rnd);
		seq[i]=rnd; //save the new value
	}
}
/*------------------------------------------------------------------------------
  Functions that show bin value of N or J and set i,n,j,previous 
*-------------------------------------------------------------------------------*/
void show_J(void){
	LPC_GPIO2->FIOPIN |= j; //
	n=1;
	i=0;
	j=0;
	previous=0;
}

void show_N(void){
	LPC_GPIO2->FIOPIN |= n; //
	n++;
	i=0;
	j=0;
}

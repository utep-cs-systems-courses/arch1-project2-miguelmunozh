#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
char switch_state_down,switch_state_down2,switch_state_down3, switch_state_down4, switch_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}
/*
char switch_state(char n){
  if(n == 1){
    n==0;
  }else if(n == 0){
    n==1;}
  return n;
 }*/
void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();

  
  /*handle all 4 buttons, if the button is push switch_statedownN = 1 otherwise is 0*/
  switch_state_down =  (p1val & BIT0) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_down2 = (p1val & BIT1) ? 0 : 1;
  switch_state_down3 = (p1val & BIT2) ? 0 : 1;
  switch_state_down4 = (p1val & BIT3) ? 0 : 1; 
  switch_state_changed = 1;
  led_update();
}

#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

//#include "buzzer.h"
char switch_state_down,switch_state_down2,switch_state_down3, switch_state_down4, switch_state_changed; /* effectively boolean */
char state = 1;
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
  //led_update();  
}

void piano(){
  if(switch_state_changed){
    char ledFlags =0;
    //if switch one is pressed
  if(switch_state_down){
    buzzer_set_period(1000);
    ledFlags = LED_GREEN;
    //ledFlags |= switch_state_down ? 0 : LED_RED;
    //led_update();
  }else{
     ledFlags = 0;
     switch_state_changed = 0;
     buzzer_set_period(0);
   }
  //if switch two is pressed
  if(switch_state_down2){
    buzzer_set_period(3000);
    ledFlags =  LED_RED;
  }
  //if switch three is pressed
  if(switch_state_down3){
    buzzer_set_period(5000);
    ledFlags = LED_GREEN;
    //ledFlags |= switch_state_down3 ? 0 : LED_RED;
  }
  //if switch four is pressed
  if(switch_state_down4){
    buzzer_set_period(7000);
    ledFlags = LED_RED;
    //ledFlags |= switch_state_down4 ? 0 : LED_GREEN;
  }
  
  P1OUT &= (0Xff - LEDS) | ledFlags;
  P1OUT |= ledFlags;
  }
  switch_state_changed =0;
  }
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
  //  led_update();
  /*   if(switch_state_down){
    state = 1;
  }
  if(switch_state_down2){
    state = 2;
    }*/
  
}


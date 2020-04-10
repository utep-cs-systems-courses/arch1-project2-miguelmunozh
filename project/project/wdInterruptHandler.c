#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "buzzer.h"
//#include "toggle.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char another_count =0;
    //switch_interrupt_handler();
    //or set the song in btn6 or 7
  switch_interrupt_handler();
    
  if(state == 1){
      if(++blink_count == 50){
        state_advance_song();
        blink_count = 0;
      }
      
     }
    if(state== 2){
      if (++another_count ==250) {
	buzzer_set_period(0);
	state_advance_binary();
	  another_count = 0;
	}
      }
    if(state == 3){
      if(++blink_count == 30){
        state_advance_rithm();
        blink_count = 0;
      }      
    }
    if(state == 4){
      if(++blink_count == 40){
	buzzer_set_period(0); //stop the beep
        state_advance();
        blink_count = 0;
      }      
    }
  }

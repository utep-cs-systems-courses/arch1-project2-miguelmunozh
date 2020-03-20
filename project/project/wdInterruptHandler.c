#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char another_count =0;
    //switch_interrupt_handler();
    //or set the song in btn6 or 7
  /* 
this makes the buttons not work correctly
if piano is called in p1_interrupt_handler.c

  if(++blink_count == 30){
    // switch_interrupt_handler();
    //piano();
    state_advance_binary();	
	blink_count=0;      
    }*/
  //this makes the song not to work correctly if piano is called here, but if
  //piano is called in p1ih.c then the button doesnt work properly here 
  switch_interrupt_handler();
    
    char state = 1; 
    if(state == 1){
      if(++blink_count == 30){
      //buzzer_set_preiod(1000);
        state_advance_binary();
        blink_count = 0;
      }
      state = 2;
     }
    /*    if(state = 2){
      //piano();
      // buzzer_set_period(1000);
      if (++another_count ==10) {
	  piano();
	  another_count = 0;
	}
      }*/
  }

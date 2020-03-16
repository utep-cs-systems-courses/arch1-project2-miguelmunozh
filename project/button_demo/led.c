
#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
/*BTN FUNCTONALITY*/

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if (switch_state_changed) {
    //here I could put an array that changes the led lighst on and off //
    //when it just turns on by changing the ledFlags value??           //
    /////////////////////////////////////////////////////////////////////

    char ledFlags = 0; /* by default, no LEDs on */
    /*while BUTTON one is being pressed do this*/
    if(switch_state_down){
    //cuando esta abajo el buton(presionado)
    ledFlags |= switch_state_down ? LED_GREEN : 0;
    buzzer_set_period(1000);
    //cuando no esta presionado
    ledFlags |= switch_state_down ? 0 : LED_RED;
    }else{
      switch_state_changed =0;
      buzzer_set_period(0);
    }

    /*if button two is pressed, do this*/
    if(switch_state_down2){
    ledFlags |= switch_state_down2 ? LED_RED : 0;
    ledFlags |= switch_state_down2 ? 0 : LED_GREEN;
    buzzer_set_period(2000);
    }else{
      //buzzer_set_period(0);
    }
    if(switch_state_down3){
      buzzer_set_period(3000);
    ledFlags |= switch_state_down3 ? LED_GREEN : 0;
    ledFlags |= switch_state_down3 ? 0 : LED_RED;
    }
    if(switch_state_down4){
      buzzer_set_period(4000);
    ledFlags |= switch_state_down4 ? LED_RED : 0;
    ledFlags |= switch_state_down4 ? 0 : LED_GREEN;
    }
    

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;
}


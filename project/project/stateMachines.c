#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}


char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}


/*binary state machine that counts to 3,
 this state machine goes through 4 stages
 which are cases 0 - 3*/
char toggle(){
  static char state =0;
  switch(state){
  case 0:
    red_on = 0;
    green_on =0;
    state =1;
    break;
  case 1:
      green_on = 1;
      state = 2;
      break;
  case 2:
    red_on = 1;
    //red_on=toggle_red();
    green_on=0;
    state =3;
    break;
  case 3:
    red_on =1;
    green_on =1;
    // state =0;
    break;
}
return 1;

}

/*toggle_song turns off and on the leds at the rythim of the ''music''*/
char toggle_song(){
 static char state =0;
  switch(state){
  case 0:
    //change leds
    red_on = 1;
    green_on =0;
    //play a tone
    buzzer_set_period(1000);
    state =1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(2000);
    state = 2;
    break;
  case 2:
    red_on = 1;
    //red_on=toggle_red();
    green_on=0;
    buzzer_set_period(1000);
    state =3;
    break;
  case 3:
    red_on =0;
    green_on =1;
    buzzer_set_period(2000);
    state = 4;
    break;
  case 4:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(1000);
    state = 5;
    break;
  case 5:
    red_on =0;
    green_on =1;
    buzzer_set_period(2000);
    state = 6;
    break;
  case 6:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(1000);
    state = 7;
    break;
  case 7:
    red_on =0;
    green_on =1;
    buzzer_set_period(2000);
    state = 8;
    break;
  case 8:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(1000);
    state = 9;
    break;
  case 9:
    red_on =0;
    green_on =1;
    buzzer_set_period(2000);
    state = 10;
    break;
  case 10:
    red_on = 1;
    green_on = 1;
    buzzer_set_period(5000);
    state = 11;
    break;
  case 11:
    red_on =1;
    green_on =1;
    buzzer_set_period(5000);
    state = 12;
    break;
  case 12:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(1000);
    state = 13;
    break;
  case 13:
    red_on =0;
    green_on =1;
    buzzer_set_period(2000);
    state = 14;
    break;
  case 14:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(3000);
    state = 15;
    break;
  case 15:
    red_on =1;
    green_on =0;
    buzzer_set_period(1000);
    state = 16;
    break;
  case 16:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(2000);
    state = 17;
    break;
  case 17:
    red_on =0;
    green_on =1;
    buzzer_set_period(3000);
    state = 18;
    break;
  case 18:
    red_on = 1;
    green_on = 1;
    buzzer_set_period(7000);
    state = 19;
    break;
  case 19:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(4000);
    state = 20;
    break;
  case 20:
    red_on =0;
    green_on =1;
    buzzer_set_period(7000);
    state = 21;
    break;
  case 21:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(4000);
    state = 22;
    break;
  case 22:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(6000);
    state = 23;
    break;
  case 23:
    red_on =1;
    green_on =1;
    buzzer_set_period(5000);
    state = 24;
    break;
  case 24:
    red_on = 1;
    green_on = 1;
    buzzer_set_period(5000);
    state = 25;
    break;
  case 25:
    red_on = 0;
    green_on = 0;
    buzzer_set_period(0);
    break;
  }
return 1;
  
}

void state_advance_binary(){
  led_changed = toggle_song();
  led_update();
}

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
    state =0;
    break;
  }
return 1;

}

/*toggle_song turns off and on the leds at the rythim of the ''music''*/
char toggle_rithm(){
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
    state = 26;
    break;
  case 26:
    buzzer_set_period(0);
    state = 0;
    break;
  }
return 1;
  
}
void state_advance_song(){
 static char stat =0;
  switch(stat){
  case 0:
    buzzer_set_period(440);
    stat =1;
    break;
  case 1:
    buzzer_set_period(440);
    stat = 2;
    break;
    case 2:
    buzzer_set_period(440);
    stat = 3;
    break;
    case 3:
    buzzer_set_period(349);
    stat =4;
    break;
  case 4:
    buzzer_set_period(349);
    stat = 5;
    break;
    case 5:
    buzzer_set_period(523);
    stat = 6;
    break;
  case 6:
    buzzer_set_period(440);
   stat = 7;
    break;
    case 7:
    buzzer_set_period(440);
    stat = 8;
    break;
    case 8:
    buzzer_set_period(440);
    stat = 9;
    break;
    case 9:
    buzzer_set_period(349);
   stat = 10;
    break;
    case 10:
    buzzer_set_period(349);
    stat = 11;
    break;
    case 11:
    buzzer_set_period(523);
    stat = 12;
    break;
    case 12:
    buzzer_set_period(523);
    stat = 13;
    break;
  case 13:
    buzzer_set_period(659);
    stat = 14;
    break;
  case 14:
    buzzer_set_period(659);
    stat = 15;
    break;
      case 15:
    buzzer_set_period(659);
    stat = 16;
    break;
      case 16:
    buzzer_set_period(698);
    stat = 18;
    break;
      case 18:
    buzzer_set_period(698);
    stat = 19;
    break;
      case 19:
    buzzer_set_period(523);
    stat = 20;
    break;
      case 20:
    buzzer_set_period(415);
    stat = 21;
    break;
      case 21:
    buzzer_set_period(415);
    stat = 22;
    break;
  case 22:
    buzzer_set_period(659);
    stat = 23;
    break;
      case 23:
    buzzer_set_period(659);
    stat = 24;
    break;
      case 24:
    buzzer_set_period(698);
    stat = 25;
    break;
      case 25:
    buzzer_set_period(0);
    stat = 26;
    break; 
case 26:
    buzzer_set_period(880);
    stat = 27;
    break;
      case 27:
    buzzer_set_period(880);
    stat = 28;
    break; 
case 28:
    buzzer_set_period(880);
    stat = 29;
    break;
      case 29:
    buzzer_set_period(440);
    stat = 30;
    break; 
case 30:
    buzzer_set_period(440);
    stat = 31;
    break;
      case 31:
    buzzer_set_period(880);
    stat = 32;
    break; 
case 32:
    buzzer_set_period(880);
    stat = 34;
    break;
      case 34:
    buzzer_set_period(830);
    stat = 35;
    break; 
case 35:
    buzzer_set_period(784);
    stat = 37;
    break;
      case 37:
    buzzer_set_period(740);
    stat = 38;
    break; 
case 38:
    buzzer_set_period(698);
    stat = 39;
    break;
      case 39:
    buzzer_set_period(740);
    stat = 41;
    break; 
case 41:
    buzzer_set_period(740);
    stat = 42;
    break;
      case 42:
    buzzer_set_period(0);
    stat = 43;
    break; 
case 43:
    buzzer_set_period(0);
    stat = 44;
    break;
      case 44:
    buzzer_set_period(455);
    stat = 45;
    break; 
case 45:
    buzzer_set_period(622);
    stat = 46;
    break;
      case 46:
    buzzer_set_period(622);
    stat = 47;
    break; 
case 47:
    buzzer_set_period(587);
    stat = 48;
    break;
      case 48:
    buzzer_set_period(554);
    stat = 49;
    break; 
case 49:
    buzzer_set_period(523);
    stat = 50;
    break;
      case 50:
    buzzer_set_period(466);
    stat = 51;
    break; 
      case 51:
    buzzer_set_period(523);
    stat = 52;
    break; 
      case 52:
    buzzer_set_period(0);
    stat = 53;
    break; 
      case 53:
    buzzer_set_period(0);
    stat = 54;
    break; 

      case 54:
    buzzer_set_period(349);
    stat = 55;
    break;
      case 55:
    buzzer_set_period(415);
    stat = 56;
    break; 
      case 56:
    buzzer_set_period(415);
    stat = 57;
    break; 
      case 57:
	buzzer_set_period(415);
    stat = 58;
    break; 
      case 58:
	buzzer_set_period(349);
    stat = 59;
    break;
    case 59:
    buzzer_set_period(349);
    stat = 60;
    break;
      case 60:
    buzzer_set_period(440);
    stat = 61;
    break; 
      case 61:
    buzzer_set_period(523);
    stat = 62;
    break; 
      case 62:
    buzzer_set_period(523);
    stat = 63;
    break; 
      case 63:
    buzzer_set_period(440);
    stat = 67;
    break;
    case 67:
    buzzer_set_period(523);
    stat = 68;
    break;
      case 68:
    buzzer_set_period(659);
    stat = 69;
    break; 
      case 69:
    buzzer_set_period(659);
    stat = 70;
    break; 
      case 70:
    buzzer_set_period(659);
    stat = 71;
    break; 
      case 71:
    buzzer_set_period(659);
    stat = 72;
    break;
    
  case 72:
    buzzer_set_period(0);
    stat = 73;
    break;
  case 73:
    buzzer_set_period(0);
    stat = 0;
    break;
  }
}

void state_advance_binary(){
  led_changed = toggle();
  led_update();
}
void state_advance_rithm(){
  led_changed = toggle_rithm();
  led_update();
}

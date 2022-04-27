#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

char button_state;

void __interrupt_vec(WDT_VECTOR) WDT()     /* 250 interrupts/sec */
{
  static char count = 0;

  // SW1
  if ((++count == 120) && button_state == 0) { // button 1, plays song
    // starwars_song(); // play song
    count = 0;
  }
  // SW2
  else if ((count % 25) == 0 && button_state == 1) // button 2, siren buzz
    buzzer_siren(); // produce siren buzz
  else if ((count == 62) && button_state == 1) { // advances siren state, switches leds
    siren_state(); // increase tone
    count = 0;
  }
  // SW3
  else if (button_state == 2) { // button 3, only green led on, buzzer off
    buzzer_off; // turn buzzer off
    green_led_on(); // turn green led on
  }
  // SW4
  else if ((count == 3) && button_state == 3) { // button 4, red led brighly & dimming
    buzzer_off(); // turn buzzer off
    red_led_on();
    dim(); // dim red led
    count = 0;
  }
}

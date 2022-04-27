#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

// variables to control blinking
static char curr_state = 0; // determine current toggle state
static char state = 1; // determine up or down state

// light starts at 50%
void toggle_red50() // led 50% intensity
{
  switch (curr_state) {
  case 0:
    red_on = 1; // red on
    curr_state = 1;
    break;
  case 1:
    red_on = 0; // red off
    curr_state = 0;
    break;
  }
  led_update();
}

// light moves from 50% intensity to 75% to show led gets brigther
void toggle_red75() // led 75% intensity
{
  switch (curr_state) {
  case 0:
    red_on = 1; // red on
    curr_state = 1;
    break;
  case 1:
    red_on = 1; // red on
    curr_state = 2;
    break;
  case 2:
    red_on = 0; // red off
    curr_state = 0;
    break;
  }
  led_update();
}

// light moves from 75% intensity to 25% to show led gets dimmer
void toggle_red25() // led 25% intensity
{
  switch (curr_state) {
  case 0:
    red_on = 0; // red off
    curr_state = 1;
    break;
  case 1:
    red_on = 0; // red off
    curr_state = 2;
    break;
  case 2:
    red_on = 1; // red on
    curr_state = 0;
    break;
  }
  led_update();
}

/* light starts at 50% to show brighly to 75% and dimming to 25% */
void dim()
{
  static int led_state = 0;

  switch (led_state) {
  case 0: // 50% intensity
    toggle_red50(); // on
    toggle_red50(); // off
    led_state = 1;
    break;
  case 1: // 75% intensity
    toggle_red75(); // on
    toggle_red75(); // on
    toggle_red75(); // off
    led_state = 2;
    break;
  case 2: // 25% intensity
    toggle_red25(); // off
    toggle_red25(); // off
    toggle_red25(); // on
    led_state = 0;
    break;
  }
}

void green_led_on() // turn green led on
{
  green_on = 1;
  red_on = 0;
  led_update();
}

void red_led_on() // turn red led on
{
  red_on = 1;
  green_on = 0;
  led_update();
}

void up_state() /* determine up state */
{ 
  state = 1;
  green_led_on(); // green led on up state
}

void down_state() /* determine down state */
{
  state = 0;
  red_led_on(); // red led on down state
}

void siren_state() /* buzzer makes increasing or decreasing tone */
{
  static char buzz_state = 0;

  switch(buzz_state) {
  case 0:
  case 1: // tone increases on green led
    up_state(); // up state to increase tone
    buzz_state++; // up state
    break; 
  case 2: // tone decreases on red led
    down_state(); // down state to decrease tone
    buzz_state = 0; // reset state
  default:
    break;
  }
}

void buzzer_siren() // play siren
{
  static int x = 500;

  if (state) { // tone up if on up state
    x += 225;
  }
  else{ // tone down if on down state
    x -= 450;
  }

  short cycles = 2000000 / x;
  buzzer_set_period(cycles);
}

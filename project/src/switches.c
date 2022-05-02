#include <msp430.h>
#include "switches.h"
#include "led.h"

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

/* controls S switches */
void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if ((p2val & SW1) == 0) // switch 1, state 0
    button_state = 0;
  else if ((p2val & SW2) == 0) // switch 2, state 1
    button_state = 1;
  else if ((p2val & SW3) == 0) // switch 3, state 2
    button_state = 2;
  else if ((p2val & SW4) == 0) // switch 4, state 3
    button_state = 3;
}

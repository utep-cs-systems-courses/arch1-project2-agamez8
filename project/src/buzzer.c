#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"

void buzzer_init()
{
  /* 
       Direct timer A output "TA0.1" to P2.6.  
       According to table 21 from data sheet:
       P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
       P2SEL.6 must be 1
       Also: P2.6 direction must be output
  */
  
  timerAUpmode(); /* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; /* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) // buzzer clock = 2MHz.  (period of 1k results in 2kHz tone)
{
  CCR0 = cycles;
  CCR1 = cycles >> 1; /* one half cycle */
}

/* turn buzzer off */
void buzzer_off()
{
  buzzer_set_period(0);
}

static int note_count = 0;

void starwars_song() // Plays Star Wars theme by John Williams
{
  switch (note_count)
  {
  case 0:
    buzzer_set_period(950);
    note_count++;
    break; // Lower C note
  case 1:
  case 6:
  case 11:
    buzzer_set_period(630);
    note_count++;
    break; // G note
  case 2:
  case 7:
  case 12:
  case 14:
    buzzer_set_period(710);
    note_count++;
    break; // F note
  case 3:
  case 8:
  case 13:
    buzzer_set_period(750);
    note_count++;
    break; // E note
  case 4:
  case 9:
  case 15:
    buzzer_set_period(840);
    if (note_count == 15)
    {
      note_count = 0;
    }
    else
    {
      note_count++;
    }
    break; // D note
  case 5:
  case 10:
    buzzer_set_period(475);
    note_count++;
    break; // C note
  }
}

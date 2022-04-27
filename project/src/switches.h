#ifndef switches_included
#define switches_included

#define SW1 BIT0 // 0000 0001
#define SW2 BIT1 // 0000 0010
#define SW3 BIT2 // 0000 0100
#define SW4 BIT3 // 0000 1000

// 0000 1111 = 15
#define SWITCHES (SW1 | SW2 | SW3 | SW4) /* 4 switches on board */

void switch_init();
void switch_interrupt_handler();

//extern char sw1_state, sw2_state, sw3_state, sw4_state;
extern char button_state;

#endif //included

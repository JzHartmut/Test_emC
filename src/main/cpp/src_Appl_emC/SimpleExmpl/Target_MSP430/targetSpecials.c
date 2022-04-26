#include <msp430fr4133.h>            //here hardware is used.

void toogleLed_P1_0 ( ) {
  P1OUT ^=  0x01; // Toggle P1.0, it is a Led
}

void toogleLed_green ( ) {
  P4OUT ^=  0x01; // Toggle P4.0, it is the green Led
}


void initP1 ( ) {
  P1DIR = 0x01; // Set P1.0 to output and P1.3 to input direction
  P1OUT &= ~1;   // set P1.0 to Off 00000000
  P1OUT |= 1<<2; // set p1.3 to 1 for pullup
  P1REN |= 1<<2; // turn on pull up widerstand
  P1IE |= 1<<2;  // P1.2 interrupt enabled
}

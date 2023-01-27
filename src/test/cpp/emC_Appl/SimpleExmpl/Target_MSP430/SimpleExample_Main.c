#include <SimpleExmpl/SimpleExmpl_Appl.h>
#include <msp430fr4133.h>

#include <Platform_MSP430FR4133/lcd_MSP430.h>
#include <Platform_MSP430FR4133/initCPU_MSP430.h>

#define ENABLE_PINS 0xFFFE


/**An operation which is invoked in the backloop,
 * toogle the green led in the time backloopLedTime;
 */
extern void backloopLed(void);

int bRun = 1;


/**Static data definition for the application. */
SimpleNumExmpl_s dataC = INIZ_SimpleNumExmpl(dataC);

/**Independent static data definition for a referenced module,
 * may be a derived type also, hence references in the application data. */
ModuleB_s modB = INIZ_ModuleB(modB, 3.5f);


/**The main() initializes the applications.
 * For non-C++ all static data initializations are done already by defining memory content.
 * For C++ is is possible that some constructors are already executed.
 * For that - to have an overview - constructs only the application data,
 *   which calls inner construction. Do not have a lot of static C++ data!
 *   Alternatively: Use mem allocation in main and call ctor in main.
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer


  initClockFast();           // Generally, use fast clock (applspec.)
  initLcd_MSP430();

  PM5CTL0 = ENABLE_PINS;

  P4DIR |= BIT0;             //set P4.0 to output
  initTimer0_MSP430Fullrange();        // a wrapping timer for time measurements.
                                       // Construct the application data with given static data.
  SimpleNumExmpl_s* thiz = ctor_SimpleNumExmpl(&dataC.base.obj, &modB);
  bool initDone;
  do {
    initDone = init_SimpleNumExmpl(thiz);
  } while(!initDone);
  //
                             // only after the initialization of the application:
  initTimer1_us(4000);       // initialize the cyclically interrupt for step
  //
  __bis_SR_register(GIE);    // Enable all interrupts
  while(bRun) {              // backloop for ever.
    //backloop();  //~72 mem access per loop, 41000 loops/sec
  }                 //=> ~ 300 ns/mem access 5 Clk-cycle a 62.5 ns

  return 0;
}


static char* testTexts[] =
{ "012345"
, "6789AB"
, "CDEFGH"
, "0.12.34.56"
, "12:45:30"
, "abcdef"
, "SEND"
, "RECEIIVE"
, "HALLO"
, "WANDJI"
};




#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer1A1Interrupt()
{
  static int ct2 = 1;
  static int ixText = 0;
  if(--ct2 <=0) {
    ct2 = 250;
    setText_Lcd(testTexts[ixText]);
    if(++ixText >=10){ ixText = 0;}
    //step_SimpleNumExmpl(&dataC, 0.15f * ixText);
    //setText_Lcd(dataC.bufferResult);
  }

  TA1CTL &= ~0x01; // interrupt flag cleared
}




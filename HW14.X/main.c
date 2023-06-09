#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>


int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  
  RPA0Rbits.RPA0R = 0b0101; // use pin A0 for OC1
  T2CONbits.TCKPS = 4;     // Timer2 prescaler N=16 (1:4))
  PR2 = 59999;             // period = (PR2+1) * N * (1/48000000) = 0.02 s = 50 Hz
  TMR2 = 0;                // initial TMR2 count is 0
  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC1CONbits.OCTSEL = 0;   // Use timer2
  OC1RS = 4500;             // duty cycle = OC1RS/(PR2+1) = 7.5%
  OC1R = 4500;              // initialize before turning OC1 on; afterward it is read-only
  T2CONbits.ON = 1;        // turn on Timer2
  OC1CONbits.ON = 1;       // turn on OC1
  
  while (1) {
      OC1RS = 60000*0.9/20;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 96000000){}
      OC1RS = 60000*2.125/20;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 96000000){}
	}
  }
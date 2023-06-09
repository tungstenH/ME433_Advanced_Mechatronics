#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  
  float vs[1000]; // triangle wave vector
  float vt[1000]; // sine wave vector
  for (int i = 0; i < 1000; i++) {
      vs[i] = 511.5*sin(2*M_PI*i/500) + 511.5;
      if(i < 500){
          vt[i] = 1023*i/500;
      } else {
          vt[i] = 2046 - 1023*i/500;
      }
  }
  
  int count = 0;
  while (1) {
      _CP0_SET_COUNT(0);
      // figure out the voltage for sine
      unsigned short  valA = vs[count];
      unsigned short t = 0;
      t = 0b111<<12;
      unsigned char a_or_b = 0b0;
      t = t|(a_or_b<<15);
      t = t|(valA << 2);
      
      
    // send the voltage with spi
      LATAbits.LATA0 = 0;
      spi_io(t>>8);
      spi_io(t);
      LATAbits.LATA0 = 1;
      
    // figure out the voltage for triangle
      unsigned short valB = vt[count];
      t = 0b111<<12;
      a_or_b = 0b1;
      t = t|(a_or_b<<15);
      t = t|(valB << 2);
    // send the volatage with spi
      LATAbits.LATA0 = 0;
      spi_io(t>>8);
      spi_io(t);
      LATAbits.LATA0 = 1;
      
      while(_CP0_GET_COUNT() < 24000){}
      
      count = count + 1;
      if (count == 1000){
          count = 0;
      }
      
	}
  }

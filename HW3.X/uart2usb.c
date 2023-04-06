#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  sprintf(message, "Program Start \r\n");
  NU32DIP_WriteUART1(message);
  while(1){
    if (!NU32DIP_USER) {
      int i = 0;
      for(i=0;i<100;i++){
          sprintf(message, "%f \r\n", sin((double)(0.2*i)));
          NU32DIP_WriteUART1(message);
          _CP0_SET_COUNT(0);
          while(_CP0_GET_COUNT()<240000) {}
      }
    }
  }
}

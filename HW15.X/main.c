#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"
#include <math.h>

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  ws2812b_setup(); //INITIALIZE THE LEDS
  
  int hue[4];
  hue[0] = 50;
  hue[1] = 100;
  hue[2] = 150;
  hue[3] = 200;
  wsColor color[4];
  
  while (1) {
      // Convert int to RGB
      color[0] = HSBtoRGB(hue[0],0.8,0.2);
      color[1] = HSBtoRGB(hue[1],0.8,0.2);
      color[2] = HSBtoRGB(hue[2],0.8,0.2);
      color[3] = HSBtoRGB(hue[3],0.8,0.2);
      ws2812b_setColor(&color[0],4);
      
      hue[0] = hue[1];
      hue[1] = hue[2];
      hue[2] = hue[3];
      hue[3] = hue[3] + 50;
      if(hue[3]>360){
          hue[3] = hue[3] - 360;
      } 
      
      NU32DIP_YELLOW = 0;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 400000){}
      NU32DIP_YELLOW = 1;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 400000){}
              
	}
  }
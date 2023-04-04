#include "nu32dip.h" // constants, functions for startup and UART

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  sprintf(message, "Program Start \r\n");
  NU32DIP_WriteUART1(message);
  while (1) {
    int n = 5; int t = 500; // Default
    
    // Retrieve the number of times light should blink
    sprintf(message, "Enter the amount of blinks: \r\n");
    NU32DIP_WriteUART1(message);
    NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
    sscanf(message, "%d", &n);
    // Retrieve how long the blink period is 
    sprintf(message, "Enter the blink period (ms): \r\n");
    NU32DIP_WriteUART1(message);
    NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
    sscanf(message, "%d", &t);
    
    if (NU32DIP_USER){
        blink(n, t); // 5 times, 500ms each time
	}
  }
}

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
		

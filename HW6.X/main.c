#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include <math.h>

unsigned char addWrite = 0b01000000;
unsigned char addRead = 0b01000001;;

unsigned char i2c_read (unsigned char reg){
    i2c_master_start();
    i2c_master_send(addWrite);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(addRead);
    unsigned char r = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();   
    return (r&0b00000001);
}

void i2c_write (unsigned char reg, unsigned char val){
    i2c_master_start();
    i2c_master_send(addWrite);
    i2c_master_send(reg);
    i2c_master_send(val);
    i2c_master_stop();         
}

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();
  i2c_write(0x00, 0b00001111);
  
  while (1) {
      // Blinking PIC LED to make sure Master is working
      _CP0_SET_COUNT(0);
      NU32DIP_YELLOW = 1; // off
      while(_CP0_GET_COUNT() < 1800000){;} // delay
      _CP0_SET_COUNT(0);
      NU32DIP_YELLOW = 0; // on
      while(_CP0_GET_COUNT() < 1800000){;} // delay
      
      if(i2c_read(0x09) == 0){
          i2c_write(0x0A, 0b10000000);
      } else {
          i2c_write(0x0A, 0b00000000);
      }
      
      
	}
  }

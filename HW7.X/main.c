#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
	
	// char array for the raw data
    char m_in[100];
    char m_out[200];
    int i;
    
	// floats to store the data
    #define NUM_DATA_PNTS 300
    float ax[NUM_DATA_PNTS], ay[NUM_DATA_PNTS], az[NUM_DATA_PNTS];
    float gx[NUM_DATA_PNTS], gy[NUM_DATA_PNTS], gz[NUM_DATA_PNTS];
    float temp[NUM_DATA_PNTS];
	
	// read whoami
    // print whoami
    char who = whoami();
	if (who != 0x68){  // if whoami is not 0x68, stuck in loop with LEDs on
        
        while(1){
            
        }
    }
    
    char IMU_buf[IMU_ARRAY_LEN];
    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        blink(1, 5);
        
        // wait to print until you get a newline
        NU32DIP_ReadUART1(m_in,100); 
        
        
        for (i=0; i<NUM_DATA_PNTS; i++){
            _CP0_SET_COUNT(0);
            // read IMU
            burst_read_mpu6050(IMU_buf);
            // convert data
            ax[i] = conv_xXL(IMU_buf);
            ay[i] = conv_yXL(IMU_buf);
            az[i] = conv_zXL(IMU_buf);
            gx[i] = conv_xG(IMU_buf);
            gy[i] = conv_yG(IMU_buf);
            gz[i] = conv_zG(IMU_buf);
            temp[i] = conv_temp(IMU_buf);
            
            while (_CP0_GET_COUNT() < 48000000 / 2 / 100) { }
        }
           
        // print out the data
        for (i=0; i<NUM_DATA_PNTS; i++){
            sprintf(m_out, "%d %f %f %f %f %f %f %f\r\n", NUM_DATA_PNTS-i,ax[i],ay[i],az[i],gx[i],gy[i],gz[i],temp[i]);
            NU32DIP_WriteUART1(m_out);
        }
        
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

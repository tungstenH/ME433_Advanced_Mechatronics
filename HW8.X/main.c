#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include "font.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
    ssd1306_setup();
	
	// char array for the raw data
    char m_in[100];
    char m_out[200];
    int i;
    
	// floats to store the data
    #define NUM_DATA_PNTS 300
    float az;
	
	// read whoami
    // print whoami
    char who = whoami();
	if (who != 0x68){  // if whoami is not 0x68, stuck in loop with LEDs on
        while(1){}
    }
    
    char IMU_buf[IMU_ARRAY_LEN];
    while (1) {
        char m[100];
        sprintf(m,"The current aZ: ");
        drawString(m, 0, 0);
        sprintf(m,"FPS: ");
        drawString(m, 0, 8);
        ssd1306_update();
        
        _CP0_SET_COUNT(0);
        burst_read_mpu6050(IMU_buf);
        az = conv_zXL(IMU_buf);
        sprintf(m,"%f", az);
        drawString(m, 80, 0);
        ssd1306_update();
        float fps = (float)24000000/_CP0_GET_COUNT();
        sprintf(m,"%f", fps);
        drawString(m, 25, 8);
        ssd1306_update();
    }
}

void drawChar(char letter, char x, char y){
    for(int j=0; j<5; j++){
        char col = ASCII[letter-0x20][j];
        for(int i=0; i<8; i++){
            ssd1306_drawPixel(x+j, y+i, (col>>i)&0b1);
        }
    }
    
}

void drawString(char* m, char x, char y){
    int k = 0;
    while(m[k] != 0) {
        drawChar(m[k], x+k*5, y);
        k++;
    }
}
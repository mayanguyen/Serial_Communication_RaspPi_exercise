/*
 * Van Mai Nguyen Thi <vn4720@bard.edu>
 * Lab 6: Serial Communication with the Pi
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <mmio.h>

volatile unsigned int* direction = (unsigned int*)(0x20200004);
volatile unsigned int* clr = (unsigned int*)(0x20200028);
volatile unsigned int* set = (unsigned int*)(0x2020001C);

volatile unsigned int* direction2 = (unsigned int*)(0x20200008);

volatile unsigned int GPLEV0 = (unsigned int)(0x20200034);
volatile unsigned int GPPUD = (unsigned int)(0x20200094);
volatile unsigned int GPPUDCLK0 = (unsigned int)(0x20200098);

void on(int n){
    *clr = (1 << n);
}

void off(int n){
    *set = (1 << n);
}

void loop(){
    volatile int i;
    for (i = 0; i < 100000; i++)
        ;
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    int a;
    uart_init();
    *direction = *direction | (1 << 18);
    *direction2 = *direction2 | (1 << 15);
    
    mmio_write(GPPUD, 1 << 1);
    delay(150);
    mmio_write(GPPUDCLK0, (1 << 23));
    delay(150);
    mmio_write(GPPUD, 0x00000000);
    mmio_write(GPPUDCLK0, 0x00000000);
    
    for (;;){
        a = uart_getc();
        
        if (a != -1) {
            
            if (a == 'N')   off(25);
            else if (a == 'F')  on(25);
            else if (a == 'B') {
                if ( mmio_read(GPLEV0) & (1 << 23) )    uart_putc('0');
                else    uart_putc('1');
            }
        }
        
        if ( mmio_read(GPLEV0) & (1 << 23) ) {
            off(16);
        }
        else {
            on(16);
        }
        
        
        loop();
    }
}





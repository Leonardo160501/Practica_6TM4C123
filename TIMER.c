#include "lib/include.h"

#define SYS_CLK 20e6

extern void initTimer0(void) {
    // Enable Timer0 clock
    SYSCTL->RCGCTIMER |= (1 << 0);
    // Wait for Timer0 to be ready
    while ((SYSCTL->PRTIMER & (1 << 0)) == 0) {}
    // Configure Timer0 as a 32-bit timer
    TIMER0->CFG = 0x00000004;
    // Set the Timer0 load value to (SYS_CLK / 3kHz) - 1
    TIMER0->TAMR = 0x00000002;
    TIMER0->TAILR = (uint32_t)(SYS_CLK / 3e3) - 1;
    // Enable Timer0
    TIMER0->CTL |= 0x00000001;
}


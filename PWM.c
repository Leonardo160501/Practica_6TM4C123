#include "lib/include.h"

extern void PWM_Init(void)
{
    // Enable PWM0 clock
SYSCTL->RCGC0 |= (1 << 20);

// Configure PWM0 pins as PWM outputs
GPIOB->AFSEL |= (1 << 6);
GPIOB->PCTL = (GPIOB->PCTL & 0xF0FFFFFF) + (0x04000000);
GPIOB->AFSEL |= (1 << 7);
GPIOB->PCTL = (GPIOB->PCTL & 0x0FFFFFFF) + (0x40000000);

// Configure PWM0 generator
PWM0->_0_CTL = 0x00000000;
PWM0->_0_GENA = 0x0000008C;
PWM0->_0_GENB = 0x0000080C;
PWM0->_0_LOAD = 0x000001F4;
PWM0->_0_CMPA = 0x0000009A;
PWM0->_0_CMPB = 0x0000009A;
PWM0->_0_CTL = 0x00000001;

// Start PWM0
PWM0->ENABLE = 0x00000003;
}
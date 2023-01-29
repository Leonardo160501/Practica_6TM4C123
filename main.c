#include "lib/include.h"

int main(void)
{
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART0();
    Configura_Reg_PWM1();
    initTimer0();
    while(1)
    {
        read_adc();
    }
    
}
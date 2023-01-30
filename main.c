#include "lib/include.h"

#define PWM_FREQUENCY 3000

int main(void)
{
    Configurar_PLL(_40MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART0();
    PWM_Init();
    initTimer0();
    while(1)
    {
        // Wait for the ADC interrupt from Timer0
        while ((ADC0->RIS & 0x1) == 0)
        {
        }

        // Read the ADC result for channel 0
        uint32_t adcResult0 = ADC0->SSFIFO0 & 0xFFF;

        // Clear the ADC interrupt flag for channel 0
        ADC0->ISC = 0x1;

        // Start the ADC conversion for channel 1
        ADC0->PSSI |= 0x2;

        while ((ADC0->RIS & 0x2) == 0)
        {
        }

        // Read the ADC result for channel 1
        uint32_t adcResult1 = ADC0->SSFIFO1 & 0xFFF;

        // Clear the ADC interrupt flag for channel 1
        ADC0->ISC = 0x2;

        // Process the ADC results for both channels here

        // Scale the ADC results to the range [-10, 10]
        int32_t adcResultScaled0 = ((int32_t)adcResult0 * 20 / 4095) - 10;
        int32_t adcResultScaled1 = ((int32_t)adcResult1 * 20 / 4095) - 10;

        // Update the duty cycle of PWM0 and PWM1 based on the ADC results
        uint32_t pwmDutyCycle0 = ((uint32_t)(adcResultScaled0 + 10) * PWM_FREQUENCY / 20) & 0xFFFF;
        uint32_t pwmDutyCycle1 = ((uint32_t)(adcResultScaled1 + 10) * PWM_FREQUENCY / 20) & 0xFFFF;
        PWM0->_0_CMPA = pwmDutyCycle0;
        PWM0->_1_CMPA = pwmDutyCycle1;
    }
    
    
}
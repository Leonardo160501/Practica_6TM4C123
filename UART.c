#include "lib/include.h"


extern void Configurar_UART0(void)
{
    //Habilitar el deloj del UART y el gpio con registros
    SYSCTL->RCGCUART |= (1<<0); 
    SYSCTL-> RCGCGPIO |= (1<<0); //Puerto C
    //Configurar el GPIO
    GPIOA-> AFSEL |= (1<<1) | (1<<0);
    //              Rx       Tx
    GPIOA->DIR |= (0<<1) | (1<<0);
    GPIOA->PUR |= (0<<1) | (1<<0);
    GPIOA->PDR |= (0<<1) | (1<<0);
    GPIOA->DEN |= (0<<1) | (1<<0);
    GPIOA->AMSEL = 0x00; //Desactivamos la funcion analogica
    GPIOA->PCTL = (GPIOA->PCTL & 0XFFFFFF00) | 0x00000011;

    UART0->CTL |= (0<<8) | (0<<9) | (0<<0) | (0<<4); 
    //Velocidad 115200 baudrate, frecuencia de reloj 50,000,000.
    //BRD = 50,000,000 / (16 * 115200) = 27.1267361
    //UARTFBRD[DIVFRAC] = integer(.1267361 * 64 + 0.5) = 8.6111104
    //para 9600 
    //130
    //14
    UART0->IBRD = 27;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART0->FBRD = 8;
    UART0->LCRH = (0x3<<5) | (1<<4);
    UART0->CC = 0x00;
    UART0->CTL |= (1<<8) | (1<<9) | (1<<0) | (1<<4); 
    
}


extern void printChar(char c) //enviamos un caracter
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}
extern void printString(char* string)//enviamos una cadena
{
    while(*string){
       printChar(*(string++)); 
    }
    printChar('\n');
}

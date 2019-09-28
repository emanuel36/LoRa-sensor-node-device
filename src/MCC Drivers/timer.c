#include <xc.h>
#include "../../inc/MCC Drivers/timer.h"
#include "../../inc/MCC Drivers/mcc.h"

volatile uint16_t timer0ReloadVal16bit;

void TMR0_Initialize(uint8_t period){
    //PRESCALE 4096, MFINTOSC, Interrupção a cada 
    T0CON1 = 0xBC;  
    
    //Interrupção a cada 5 minutos
    TMR0H = 0x70;
    TMR0L = 0xF2;

    timer0ReloadVal16bit = (TMR0H << 8) | TMR0L;

    PIR0bits.TMR0IF = 0;

    PIE0bits.TMR0IE = 1;
 
    T0CON0 = 0x91; //TMR0 16 bits enable, postcale 1 - 16
}

void TMR0_ISR(){
    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
    
    ledBlink();
    ledBlink();
    ledBlink();
}

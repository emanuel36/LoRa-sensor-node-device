#include <xc.h>
#include "timer.h"
#include "statusLed.h"
#include "eusart.h"

volatile uint16_t timer0ReloadVal16bit;

void TMR0_Initialize(uint8_t period){
    //PRESCALE 4096, MFINTOSC, Interrupção a cada 
    T0CON1 = 0xBC;  
    
    //Interrupção a cada 5 minutos
    TMR0H = 0x70;
    TMR0L = 0xF2;
    
//    TMR0H = 0xFB;
//    TMR0L = 0x3C;

    timer0ReloadVal16bit = (TMR0H << 8) | TMR0L;

    PIR0bits.TMR0IF = 0;

    PIE0bits.TMR0IE = 1;
 
    T0CON0 = 0x90; //(0x90 | (0x0F & period)); //TMR0 16 bits enable, postcale 1 - 16
}

void TMR0_Reload(){
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
}

void TMR0_StartTimer(){
    TMR0_Reload();
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(){
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}


void TMR2_Initialize(){
    // T2CS MFINTOSC_31.25KHz; 
    T2CLKCON = 0x06;

    // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T2HLT = 0x00;

    // T2RSEL T2CKIPPS pin; 
    T2RST = 0x00;

    // T2PR 255; 
    T2PR = 0xFF;

    // TMR2 0; 
    T2TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE4bits.TMR2IE = 1;

    // T2CKPS 1:128; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0xF0;
}

void TMR2_Period8BitSet(uint8_t periodVal){
    PR2 = periodVal;
}

void TMR2_Counter8BitSet(uint8_t timerVal){
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_CounterReset(){
    // Write to the Timer2 register
    TMR2_Counter8BitSet(0x00);
}

void TMR2_Start(){
    // Start the Timer by writing to TMRxON bit
    TMR2_CounterReset();
    T2CONbits.TMR2ON = 1;
}

void TMR2_Stop(){
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

void TMR0_ISR(){
    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
    
    EUSART_SendString("Interrupt\n");
    
    TMR0_StartTimer();
}

void TMR2_ISR(void){
    // clear the TMR2 interrupt flag
    PIR4bits.TMR2IF = 0;

    if(LATA5 || LATA4){
        TMR2_Period8BitSet(0xFF);
    }else{
        TMR2_Period8BitSet(0x0F);
    }
    
    swapLedState();
    
    TMR2_Start();
}

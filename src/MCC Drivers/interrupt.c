#include "../../inc/MCC Drivers/interrupt.h"
#include "../../inc/MCC Drivers/timer.h"

void __interrupt() INTERRUPT_InterruptManager (void){
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1){
        TMR0_StopTimer();
        TMR0_ISR();
    }
    
    if(PIE4bits.TMR2IE == 1 && PIR4bits.TMR2IF == 1){
        TMR2_Stop();
        TMR2_ISR();
    } 
}

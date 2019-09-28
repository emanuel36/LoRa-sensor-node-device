#include "../../inc/MCC Drivers/interrupt.h"
#include "../../inc/MCC Drivers/timer.h"

void __interrupt() INTERRUPT_InterruptManager (void){
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1){
        TMR0_ISR();
    }
}

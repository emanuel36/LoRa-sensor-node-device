#include <xc.h>
#include "../inc/MCC Drivers/mcc.h"

void main(void){
    // initialize the device
    MCU_Initialize();
    
    TRISCbits.TRISC3 = 0;

    while (1){
        LATC3 = 0;
        __delay_ms(500);
        LATC3 = 1;
        __delay_ms(500);
    }
}

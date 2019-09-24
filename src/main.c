#include <xc.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"

void ledBlink(){
    TRISAbits.TRISA5 = 0;
    LATA5 = 1;
    __delay_ms(50);
    LATA5 = 0;
}

void main(void){
    // initialize the device
    MCU_Initialize();
    
    EUSART_Initialize();
    while (1){
        ledBlink();
        EUSART_SendString("EUSART test\n");
        __delay_ms(500);
    }
}

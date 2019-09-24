#include <xc.h>
#include <stdio.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage;

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
        adcResult = ADC_GetSingleConversion(RC5_channel);
        batteryVoltage = (((2.048 * adcResult) / 4096) * 2);
        sprintf(msg, "Voltage: %.3f V\n", batteryVoltage);
        EUSART_SendString(msg);
        __delay_ms(500);
    }
}

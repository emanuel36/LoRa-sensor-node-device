#include <xc.h>
#include <stdio.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/Peripheral Drivers/sht30.h"
#include "../inc/Peripheral Drivers/max44009.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage, airTemperature, airHumidity, lightness;

void ledBlink(){
    TRISAbits.TRISA5 = 0;
    LATA5 = 1;
    __delay_ms(50);
    LATA5 = 0;
}

void main(void){
    // initialize the device
    SYSTEM_Initialize();
    
    EUSART_Initialize();
           
    while (1){
        ledBlink();
        max44009Read(&lightness);
        sprintf(msg, "max44009: %.3f\n", lightness);
        EUSART_SendString(msg);
        __delay_ms(500);
    }
}

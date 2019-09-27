#include <xc.h>
#include <stdio.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/Peripheral Drivers/battery.h"
#include "../inc/Peripheral Drivers/sht30.h"
#include "../inc/Peripheral Drivers/max44009.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage, soilTemperature, airTemperature, airHumidity, lightness;

void ledBlink(){
    TRISAbits.TRISA5 = 0;
    LATA5 = 1;
    __delay_ms(50);
    LATA5 = 0;
}

void main(void){
    // initialize the device
    SYSTEM_Initialize();
    
    //EUSART_Initialize();
           
    while (1){
        ledBlink();
        __delay_ms(200);
    }
}

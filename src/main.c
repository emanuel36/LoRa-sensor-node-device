#include <xc.h>
#include <stdio.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/Peripheral Drivers/sht30.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage, airTemperature, airHumidity;

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
        SHT30Read(&airTemperature, &airHumidity);
        sprintf(msg, "Temp: %.3f | Humi: %.3f\n", airTemperature, airHumidity);
        EUSART_SendString(msg);
        __delay_ms(500);
    }
}

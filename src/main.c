#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/MCC Drivers/timer.h"
#include "../inc/Peripheral Drivers/battery.h"
#include "../inc/Peripheral Drivers/sht30.h"
#include "../inc/Peripheral Drivers/max44009.h"
#include "../inc/Peripheral Drivers/ds18b20.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage, soilTemperature, airTemperature, airHumidity, lightness;

void main(void){
    // initialize the device
    SYSTEM_Initialize();
    EUSART_Initialize();
    
    while (1){
        ledBlink();
        ds18b20Read(&soilTemperature);
        sprintf(msg, "DS18B20: %.3f\n", soilTemperature);
        EUSART_SendString(msg);
        __delay_ms(250);
    }
    
}

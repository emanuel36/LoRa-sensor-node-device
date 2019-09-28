#include <xc.h>
#include <stdio.h>
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/Peripheral Drivers/battery.h"
#include "../inc/Peripheral Drivers/sht30.h"
#include "../inc/Peripheral Drivers/max44009.h"
#include "../inc/MCC Drivers/timer.h"

char msg[30];
uint16_t adcResult;
float batteryVoltage, soilTemperature, airTemperature, airHumidity, lightness;

void main(void){
    // initialize the device
    SYSTEM_Initialize();
    EUSART_Initialize();
    
    while (1){
        
    }
    
}

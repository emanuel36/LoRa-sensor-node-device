#include "battery.h"
#include <xc.h>

void batteryPinInicialize(){
    ANSC3 = 1;
    TRISC3 = 1;
}

void getBatteryVoltage(float *voltage){
    uint16_t adcResult;
    adcResult = ADC_GetSingleConversion(RC3_channel);
    *voltage = (((2.048 * (float) adcResult) / 4096.0) * 2.0);
}
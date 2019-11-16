#include <xc.h>
#include "supplyVoltage.h"

void supplyPinInicialize(){
    ANSC3 = 1;
    TRISC3 = 1;
}

void getSupplyVoltage(float *voltage){
    uint16_t adcResult;
    adcResult = ADC_GetSingleConversion(RC3_channel);
    *voltage = (((2.048 * (float) adcResult) / 4096.0) * 2.0);
}
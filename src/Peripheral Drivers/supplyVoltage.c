#include <xc.h>
#include "supplyVoltage.h"

void supplyPinInicialize(){
    ANSA5 = 1;
    TRISA5 = 1;
}

void getSupplyVoltage(float *voltage){
    uint16_t adcResult;
    adcResult = ADC_GetSingleConversion(RA5_channel);
    *voltage = (((2.048 * (float) adcResult) / 4096.0) * 2.0);
}
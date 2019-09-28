#include "../../inc/Peripheral Drivers/battery.h"

void getBatteryVoltage(float *voltage){
    uint16_t adcResult;
    adcResult = ADC_GetSingleConversion(RC5_channel);
    *voltage = (((2.048 * (float) adcResult) / 4096.0) * 2.0);
}
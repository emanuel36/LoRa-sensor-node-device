#include "../../inc/Peripheral Drivers/battery.h"

void getBatteryVoltage(float *voltage){
    uint16_t adcResult;
    adcResult = ADC_GetSingleConversion(RC5_channel);
    *voltage = (((2.048 * adcResult) / 4096) * 2);
}
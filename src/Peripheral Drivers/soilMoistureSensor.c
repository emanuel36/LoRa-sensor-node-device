#include <xc.h>
#include "../../inc/MCC Drivers/adc.h"
#include "../../inc/Peripheral Drivers/soilMoistureSensor.h"
#include "../../inc/Peripheral Drivers/battery.h"

void soilMoistureSensorPinInicialize(){
    ANSA5 = 1;
    TRISA5 = 1;
}

void soilMoistureSensorRead(float *moisture){
    float supplyVoltage, sensorVoltage;
    uint16_t adcResult;
            
    getBatteryVoltage(&supplyVoltage);
    adcResult = ADC_GetSingleConversion(RA5_channel);
    sensorVoltage = (((2.048 * (float) adcResult) / 4096.0) * 2.0);
    
    *moisture = sensorVoltage/supplyVoltage;
    return;
    
}
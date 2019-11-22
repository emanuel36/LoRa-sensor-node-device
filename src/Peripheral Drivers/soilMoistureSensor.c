#include <xc.h>
#include "adc.h"
#include "soilMoistureSensor.h"
#include "supplyVoltage.h"

void soilMoistureSensorPinInicialize(){
    ANSC0 = 1;
    TRISC0 = 1;
}

void soilMoistureSensorRead(float *moisture){
    float supplyVoltage, sensorVoltage;
    uint16_t adcResult;
    int moistureLevel;
            
    getSupplyVoltage(&supplyVoltage);
    ADC_use_fvr(0);
    adcResult = ADC_GetSingleConversion(RC0_channel);
    ADC_use_fvr(1);
    sensorVoltage = (supplyVoltage * adcResult) / 4096.0;
    
    *moisture = sensorVoltage/supplyVoltage;
    
//    moistureLevel = (0.80 - (sensorVoltage/supplyVoltage)) * 100;   
//    
//    if(moistureLevel < 0)   moistureLevel = 0;
//    if(moistureLevel > 40)  moistureLevel = 40;
//    
//    *moisture = moistureLevel;
}
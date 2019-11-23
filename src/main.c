#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "mcu.h"
#include "supplyVoltage.h"
#include "sht30.h"
#include "max44009.h"
#include "ds18b20.h"
#include "soilMoistureSensor.h"
#include "sx1276.h"

char packet[30]; 
float supplyVoltage, 
      soilTemperature, 
      soilMoistureLevel,
      airTemperature, 
      airHumidity, 
      lightness;

void setSystemStatus(bool state){
    systemStatus = state;
}

bool getSystemStatus(){
    return systemStatus;
}

void variablesReset(){
    supplyVoltage = 0.0;
    soilTemperature = 0.0;
    airTemperature = 0.0;
    airHumidity = 0.0;
    lightness = -1.0;
    soilMoistureLevel = 0;
}

bool lightnessCheck(){
    if(lightness > 189000.0 || lightness < 0.0)                         return false;
    return true;
}

bool temperatureCheck(){
    if(airTemperature > 80.0 || airTemperature < 0.1)                return false;
    if(soilTemperature > 80.0 || soilTemperature < 0.1)              return false;
    return true;
}

bool humidityCheck(){
    if(airHumidity > 100.0 || airHumidity < 0.1)                     return false;
    return true;
}

bool dataCheck(){
    if(temperatureCheck() && humidityCheck() && lightnessCheck())     return true;
    return false;
}

bool voltageCheck(){
    if(supplyVoltage < 2.5 || supplyVoltage > 3.5)                  return false;
    return true;
}

bool systemCheck(){
    if(dataCheck() && voltageCheck()){
        setSystemStatus(NORMAL);
    }else{
        setSystemStatus(WARNING);
    }
}

void sensorsRead(){
    variablesReset();
    getSupplyVoltage(&supplyVoltage);
    SHT30Read(&airTemperature, &airHumidity);
    max44009Read(&lightness);
    ds18b20Read(&soilTemperature);
    soilMoistureSensorRead(&soilMoistureLevel);
}

void pktBuild(){
    packet[0] = '\0';
    sprintf(packet, "%d|%.3f|%.2f|%.2f|%.2f|%.1f|%.1f", getSystemStatus(), supplyVoltage, airTemperature, soilTemperature, airHumidity, soilMoistureLevel, lightness);
}

void SX1276Transmit(){
    while(beginPacket(false) == 0){
        setSystemStatus(WARNING);
        __delay_ms(250);
    }
    
    beginPacket(false);
    SX1276WriteString(packet);
    endPacket(false);
}

void callBack(){
    sensorsRead();
    systemCheck();
    pktBuild();
    SX1276Transmit();
}

void main(void){
    SYSTEM_Initialize();
    while(1){
        callBack();
        __delay_ms(100);
    }
}

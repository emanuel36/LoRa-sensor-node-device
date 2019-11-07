#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "mcu.h"
#include "eusart.h"
#include "adc.h"
#include "timer.h"
#include "battery.h"
#include "sht30.h"
#include "max44009.h"
#include "ds18b20.h"
#include "soilMoistureSensor.h"
#include "spi.h"

char msg[60];
float soilMoistureLevel;
float supplyVoltage, 
      soilTemperature, 
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
    lightness = 0.0;
    soilMoistureLevel = 0;
}

bool lightnessCheck(){
    if(lightness > 189.0 | lightness < 0.0)                         return false;
    return true;
}

bool temperatureCheck(){
    if(airTemperature > 50.0 | airTemperature < 0.1)                return false;
    if(soilTemperature > 50.0 | soilTemperature < 0.1)              return false;
    return true;
}

bool humidityCheck(){
    if(airHumidity > 100.0 | airHumidity < 0.1)                     return false;
    return true;
}

bool dataCheck(){
    if(temperatureCheck() & humidityCheck() & lightnessCheck())     return true;
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
    getBatteryVoltage(&supplyVoltage);
    SHT30Read(&airTemperature, &airHumidity);
    max44009Read(&lightness);
    //ds18b20Read(&soilTemperature);
    //soilMoistureSensorRead(&soilMoistureLevel);
}

void msgBuild(){
    sprintf(msg, "Battery: %.3f V\nSHT30: %.2fC/%.2f%%\nDS18B20: %.2fC\nmax44009: %.2flm\nCapacitive Sensor: %.2f\n\n", supplyVoltage, airTemperature, airHumidity, soilTemperature, lightness, soilMoistureLevel);
}

void bluetoothSend(){
    EUSART_SendString(msg);
}

void callBack(){
    sensorsRead();
    systemCheck();
    msgBuild();
    bluetoothSend();
}

void main(void){
    SYSTEM_Initialize();
    while(1){ 
        callBack();
        __delay_ms(500);
    }
}

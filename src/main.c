#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "mcu.h"
#include "eusart.h"
#include "supplyVoltage.h"
#include "sht30.h"
#include "max44009.h"
#include "ds18b20.h"
#include "soilMoistureSensor.h"
#include "sx1276.h"

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

void msgBuild(){
    msg[0] = '\0';
    if(getSystemStatus() == NORMAL){
       sprintf(msg, "Status: Normal\n%.3f V\n%.2fC/%.2f%%\n%.2fC\n%.2flm\n%.3fL\n\n", supplyVoltage, airTemperature, airHumidity, soilTemperature, lightness, soilMoistureLevel);
    }else{
       sprintf(msg, "Status: Erro\n%.3f V\n%.2fC/%.2f%%\n%.2fC\n%.2flm\n%.3fL\n\n", supplyVoltage, airTemperature, airHumidity, soilTemperature, lightness, soilMoistureLevel); 
    }
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
        while(beginPacket(false) == 0){
            setSystemStatus(WARNING);
            __delay_ms(250);
        }
        beginPacket(false);
        SX1276sendString("UFC - CAMPUS QUIXADA");
        endPacket(false);
    }
}

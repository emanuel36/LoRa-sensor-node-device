#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "../inc/main.h"
#include "../inc/MCC Drivers/mcc.h"
#include "../inc/MCC Drivers/eusart.h"
#include "../inc/MCC Drivers/adc.h"
#include "../inc/MCC Drivers/timer.h"
#include "../inc/Peripheral Drivers/battery.h"
#include "../inc/Peripheral Drivers/sht30.h"
#include "../inc/Peripheral Drivers/max44009.h"
#include "../inc/Peripheral Drivers/ds18b20.h"

char msg[50];
float batteryVoltage, soilTemperature, airTemperature, airHumidity, lightness;

void setSystemStatus(bool state){
    systemStatus = state;
}

bool getSystemStatus(){
    return systemStatus;
}

void variablesReset(){
    batteryVoltage = 0.0;
    soilTemperature = 0.0;
    airTemperature = 0.0;
    airHumidity = 0.0;
    lightness = 0.0;
}

bool lightnessCheck(){
    if(lightness > 189.0 | lightness < 0.01)   return false;
    return true;
}

bool temperatureCheck(){
    if(airTemperature > 50.0 | airTemperature < 0.1)       
        return false;
    return true;
}

bool humidityCheck(){
    if(airHumidity > 100.0 | airHumidity < 0.1)   return false;
    return true;
}

bool dataCheck(){
    if(temperatureCheck() & humidityCheck() & lightnessCheck())    return true;
    return false;
}

void sensorsRead(){
    variablesReset();
    getBatteryVoltage(&batteryVoltage);
    SHT30Read(&airTemperature, &airHumidity);
    ds18b20Read(&soilTemperature);
    max44009Read(&lightness);
    if(dataCheck() == false){
        setSystemStatus(WARNING);
    }else{
        setSystemStatus(NORMAL);
    }
}

void msgBuild(){
    sprintf(msg, "Battery: %.3f V\nSHT30: %.2fC/%.2f%%\nDS18B20: %.2fC\nmax44009: %.2flm\n\n", batteryVoltage, airTemperature, airHumidity, soilTemperature, lightness);
}

void bluetoothSend(){
    EUSART_SendString(msg);
}

void callBack(){
    sensorsRead();
    msgBuild();
    bluetoothSend();
}

void main(void){
    // initialize the device
    SYSTEM_Initialize();
    EUSART_Initialize();
    
    while (1){ 
        callBack();
        __delay_ms(1000);
    }
}

#ifndef MAIN_H
#define	MAIN_H

#include <stdbool.h>

bool systemStatus;
enum system_status {NORMAL = 0, WARNING} status;


void setSystemStatus(bool state);
bool getSystemStatus();
void variablesReset();
bool lightnessCheck();
bool temperatureCheck();
bool humidityCheck();
bool dataCheck();
bool voltageCheck();
bool systemCheck();
void sensorsRead();
void msgBuild();
void bluetoothSend();
void callBack();

#endif	/* MAIN_H */


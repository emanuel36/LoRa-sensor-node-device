#ifndef MAIN_H
#define	MAIN_H

#include <stdbool.h>

enum system_status {NORMAL = 0, WARNING} status;
bool systemStatus = NORMAL;

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
void pktBuild();
void bluetoothSend();
void callBack();

#endif	/* MAIN_H */


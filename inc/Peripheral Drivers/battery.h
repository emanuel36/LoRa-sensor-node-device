#ifndef BATTERY_H
#define	BATTERY_H

#include "adc.h"
#include <stdint.h>

void getBatteryVoltage(float *voltage);
void batteryPinInicialize();

#endif	/* BATTERY_H */

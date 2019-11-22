#ifndef STATUSLED_H
#define	STATUSLED_H

#include <xc.h>
#include <stdbool.h>
#include "main.h"

#define NORMAL_LED      LATC1
#define NORMAL_LED_PIN  TRISC1
#define WARNING_LED     LATC2
#define WARNING_LED_PIN TRISC2

void statusLed_Inicialize();
void swapLedState();

#endif	/* STATUSLED_H */


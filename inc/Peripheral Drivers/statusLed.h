#ifndef STATUSLED_H
#define	STATUSLED_H

#include <xc.h>
#include <stdbool.h>
#include "main.h"

#define NORMAL_LED      LATA0
#define NORMAL_LED_PIN  TRISA0
#define WARNING_LED     LATA2
#define WARNING_LED_PIN TRISA2

void statusLed_Inicialize();
void swapLedState();

#endif	/* STATUSLED_H */


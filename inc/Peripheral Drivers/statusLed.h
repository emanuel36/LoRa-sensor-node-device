#ifndef STATUSLED_H
#define	STATUSLED_H

#include <xc.h>
#include <stdbool.h>
#include "../../inc/main.h"

#define NORMAL_LED      LATA5
#define NORMAL_LED_PIN  TRISA5
#define WARNING_LED     LATA4
#define WARNING_LED_PIN TRISA4

void statusLed_Inicialize();
void swapLedState();

#endif	/* STATUSLED_H */


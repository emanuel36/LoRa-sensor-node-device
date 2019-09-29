#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

enum periods {T5_MINUTES = 0,
        T10_MINUTES,
        T15_MINUTES,
        T20_MINUTES,
        T25_MINUTES,
        T30_MINUTES,
        T35_MINUTES,
        T40_MINUTES,
        T45_MINUTES,
        T50_MINUTES,
        T55_MINUTES,
        T60_MINUTES,
        T65_MINUTES,
        T70_MINUTES,
        T75_MINUTES,
        T80_MINUTES} period;

void TMR0_Initialize(uint8_t period);
void TMR2_Initialize();
void TMR2_Counter8BitSet(uint8_t timerVal);
void TMR2_CounterReset();
void TMR2_Start();
void TMR2_Stop();
void TMR0_ISR();
void TMR2_ISR();

#endif	/* TIMER_H */


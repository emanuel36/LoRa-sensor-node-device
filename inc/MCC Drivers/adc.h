#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define RA0_channel 0x00
#define RA1_channel 0x01
#define RA2_channel 0x02
#define RA3_channel 0x03
#define RA4_channel 0x04
#define RA5_channel 0x05
#define RC0_channel 0x10
#define RC1_channel 0x11
#define RC2_channel 0x12
#define RC3_channel 0x13
#define RC4_channel 0x14
#define RC5_channel 0x15

#include "../../inc/MCC Drivers/adc.h"

void ADC_Initialize();
void ADCC_StartConversion(uint8_t channel);
bool ADCC_IsConversionDone();
uint16_t ADCC_GetConversionResult();
uint16_t ADC_GetSingleConversion(uint8_t channel);

#endif	/* ADC_H */

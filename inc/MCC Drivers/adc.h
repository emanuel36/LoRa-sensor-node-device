#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define RC5_channel 0x15

#include "../../inc/MCC Drivers/adc.h"

void ADC_Initialize();
void ADCC_StartConversion(uint8_t channel);
bool ADCC_IsConversionDone();
uint16_t ADCC_GetConversionResult();
uint16_t ADC_GetSingleConversion(uint8_t channel);

#endif	/* ADC_H */

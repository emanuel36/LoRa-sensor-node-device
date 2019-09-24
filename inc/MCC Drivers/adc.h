#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>

#define RC5_channel 0x15

void ADC_Initialize();
uint16_t ADC_GetSingleConversion(uint8_t channel);

#endif	/* ADC_H */

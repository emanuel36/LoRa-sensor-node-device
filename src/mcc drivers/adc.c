#include "../../inc/MCC Drivers/adc.h"

void ADC_Initialize(){
    FVRCONbits.ADFVR = 0x2;     //2.048 V Vref
    FVRCONbits.FVREN = 0x1;     //FVR Enable
    ADREFbits.PREF = 0x3;
    ADCON0bits.FM = 0x1;
    ADCON0bits.ON = 0x1;    
}

uint16_t ADC_GetSingleConversion(uint8_t channel){
    // select the A/D channel
    ADPCH = channel;  

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
	
    //Disable the continuous mode.
    ADCON0bits.ADCONT = 0;    

    // Start the conversion
    ADCON0bits.ADGO = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.ADGO);
    
    // Conversion finished, return the result
    return (ADRESH << 8) + ADRESL;
}

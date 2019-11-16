#include "adc.h"
#include <stdbool.h>

void ADC_Initialize(){
    FVRCON = 0x82;
    // ADLTH 0; 
    ADLTHL = 0x00;
    // ADLTH 0; 
    ADLTHH = 0x00;
    // ADUTH 0; 
    ADUTHL = 0x00;
    // ADUTH 0; 
    ADUTHH = 0x00;
    // ADSTPT 0; 
    ADSTPTL = 0x00;
    // ADSTPT 0; 
    ADSTPTH = 0x00;
    // ADACC 0; 
    ADACCU = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADACQ 0; 
    ADACQL = 0x00;
    // ADACQ 0; 
    ADACQH = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPREL = 0x00;
    // ADPRE 0; 
    ADPREH = 0x00;
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADMATH registers not updated; 
    ADSTAT = 0x00;
    // ADNREF VSS; ADPREF FVR; 
    ADREF = 0x03;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADCS FOSC/64; 
    ADCLK = 0x1F;
    // ADGO stop; ADFM right; ADON enabled; ADCS FOSC/ADCLK; ADCONT disabled; 
    ADCON0 = 0x84; 
}

void ADCC_StartConversion(uint8_t channel){
    // select the A/D channel
    ADPCH = channel;      
  
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Start the conversion
    ADCON0bits.ADGO = 1;
}

bool ADCC_IsConversionDone(){
    // Start the conversion
    return ((unsigned char)(!ADCON0bits.ADGO));
}

uint16_t ADCC_GetConversionResult(){
    // Return the result
    return ((uint16_t)((ADRESH << 8) + ADRESL));
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

void ADC_use_fvr(bool flag){
    if(flag){
        ADCON0bits.ON = 0;
        ADREF = 0x03;
        ADCON0bits.ON = 1;
    }else{
        ADCON0bits.ON = 0;
        ADREF = 0x00;
        ADCON0bits.ON = 1;
    }
}
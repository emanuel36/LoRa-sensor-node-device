#include "../../inc/MCC Drivers/eusart.h"

void EUSART_Initialize(){
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN disabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x80;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

    // SP1BRGL 64; 
    SP1BRGL = 0x40;

    // SP1BRGH 3; 
    SP1BRGH = 0x03;
}

uint8_t EUSART_Read(){
    while(!PIR3bits.RC1IF);
    return RC1REG;
}

void EUSART_Write(uint8_t txData){
    while(!PIR3bits.TX1IF);
    TX1REG = txData;   
    while(!TX1STAbits.TRMT);
}

void EUSART_SendString(uint8_t *string){
    while(*string != '\0'){            
        EUSART_Write(*string);
        string++;
   }
}
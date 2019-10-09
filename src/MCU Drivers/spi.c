#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "spi.h"

#pragma warning disable 520     

void (*spi_interruptHandler)(void);   

inline void spi_close(void){
    SSPEN2 = 0;
}

//con1 == SSPxCON1, stat == SSPxSTAT, add == SSPxADD, operation == Master/Slave
typedef struct { uint8_t con1; uint8_t stat; uint8_t add; uint8_t operation; } spi2_configuration_t;
static const spi2_configuration_t spi2_configuration[] = {
    { 0xa, 0x40, 0x3f, 0 }
};

//Setup SPI
bool spi_open(spi2_modes spiUniqueConfiguration){
    TRISC0 = 0;
    LATC0 = 1;
    if(!SSPEN2){
        //setup PPS pins
        SSP2CLKPPS = 2;
        SSP2DATPPS = 0;
        RA2PPS = 21;
        RA1PPS = 22;

        //setup SPI
        SSP2STAT = spi2_configuration[spiUniqueConfiguration].stat;
        SSP2CON1 = (uint8_t)(spi2_configuration[spiUniqueConfiguration].con1 | 0x20);
        SSP2CON2 = 0x00;
        SSP2ADD  = (uint8_t)(spi2_configuration[spiUniqueConfiguration].add);

        TRISA2 = (uint8_t)(spi2_configuration[spiUniqueConfiguration].operation);
        return true;
    }
    return false;
}

// Full Duplex SPI Functions
uint8_t spi_exchangeByte(uint8_t b){
    chipEnable();
    SSP2BUF = b;
    while(!SSP2IF);
    SSP2IF = 0;
    chipDisable();
    return SSP2BUF;
}

void spi_exchangeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data = spi_exchangeByte(*data );
        data++;
    }
}

// Half Duplex SPI Functions
void spi_writeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        spi_exchangeByte(*data++);
    }
}

void spi_readBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data++ = spi_exchangeByte(0);
    }
}

void spi_writeByte(uint8_t byte){
    SSP2BUF = byte;
}

uint8_t spi_readByte(void){
    return SSP2BUF;
}

void chipEnable(){
    LATC0 = 0;
}

void chipDisable(){
    LATC0 = 1;
}

/**
 * Interrupt from MSSP on bit 8 received and SR moved to buffer
 * If interrupts are not being used, then call this method from the main while(1) loop
 */
void spi_isr(void){
    if(SSP2IF == 1){
        if(spi_interruptHandler){
            spi_interruptHandler();
        }
        SSP2IF = 0;
    }
}

void spi_setSpiISR(void(*handler)(void)){
    spi_interruptHandler = handler;
}
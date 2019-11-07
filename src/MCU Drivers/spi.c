#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "spi.h"
#include "mcu.h"

void SPI2_Initialize(void)
{
    // Set the SPI2 module to the options selected in the User Interface
    ANSA0 = 0;
    ANSA1 = 0;
    ANSA2 = 0;
    
    TRISA0 = 1;
    TRISA1 = 0;
    TRISA2 = 0;
    TRISC0 = 0;
    
    LATC0 = 1;
    
    SSP2STAT = 0x40;
    SSP2CON1 = 0x21;
    SSP2ADD = 0x00;
}

uint8_t SPI2_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP2CON1bits.WCOL = 0;

    SSP2BUF = data;

    while(SSP2STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSP2BUF);
}

uint8_t SPI2_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    SPI2_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI2_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI2_Exchange8bit(SPI2_DUMMY_DATA);

                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

bool SPI2_IsBufferFull(void)
{
    return (SSP2STATbits.BF);
}

bool SPI2_HasWriteCollisionOccured(void)
{
    return (SSP2CON1bits.WCOL);
}

void SPI2_ClearWriteCollisionStatus(void)
{
    SSP2CON1bits.WCOL = 0;
}
/**
 End of File
*/

void chipEnable(){
    LATC0 = 0;
}

void chipDisable(){
    LATC0 = 1;
}
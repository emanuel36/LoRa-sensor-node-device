#ifndef SPI_H
#define SPI_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define INLINE  inline 

typedef enum { 
    SPI_DEFAULT
} spi2_modes;

/* arbitration interface */
INLINE void spi_close(void);

bool spi_open(spi2_modes spiUniqueConfiguration);
/* SPI native data exchange function */
uint8_t spi_exchangeByte(uint8_t b);
/* SPI Block move functions }(future DMA support will be here) */
void spi_exchangeBlock(void *block, size_t blockSize);
void spi_writeBlock(void *block, size_t blockSize);
void spi_readBlock(void *block, size_t blockSize);

void spi_writeByte(uint8_t byte);
uint8_t spi_readByte(void);
void chipDisable();
void chipEnable();

void spi_isr(void);
void spi_setSpiISR(void(*handler)(void));

#endif // SPI_H

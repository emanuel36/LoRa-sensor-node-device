#ifndef _SPI2_H
#define _SPI2_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SPI2_DUMMY_DATA 0x0
#define SPI_RX_IN_PROGRESS 0x0

void SPI2_Initialize(void);
void chipDisable();
void chipEnable();
uint8_t SPI2_Exchange8bit(uint8_t data);
uint8_t SPI2_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
bool SPI2_IsBufferFull(void);
bool SPI2_HasWriteCollisionOccured(void);
void SPI2_ClearWriteCollisionStatus(void);

#endif // _SPI2_H
/**
 End of File
*/

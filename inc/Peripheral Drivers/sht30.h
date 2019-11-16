#ifndef SHT30_H
#define	SHT30_H

#include <stdbool.h>

#define SHT30_ADRESS 0x88
#define COMMAND_BYTE_1 0x24
#define COMMAND_BYTE_2 0x00

void SHT30Setup();
bool SHT30Read(float *temp, float *humi);

#endif	/* SHT30_H */

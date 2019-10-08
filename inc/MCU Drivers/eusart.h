#ifndef EUSART_H
#define	EUSART_H

#include <xc.h>
#include <stdint.h>

void EUSART_Initialize();
uint8_t EUSART_Read();
void EUSART_Write(uint8_t txData);
void EUSART_SendString(uint8_t *string);

#endif	/* EUSART_H */
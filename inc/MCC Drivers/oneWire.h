#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include <stdlib.h>
#include <math.h>
#include <xc.h>

// This configuration is required to make a PIC be in open drain 
#define BUSDIR LATAbits.LATA4 // Set direction: input or output
#define BUSOUT TRISAbits.TRISA4 // Set output: high or low 
#define BUSIN PORTAbits.RA4 // Read input 

unsigned int OneWireReset(void); // Sends a reset pulse to the sensor 
void OneWireWriteBit(unsigned char); // write a single bit to the OneWire
unsigned char OneWireReadBit(void); // reads a single bit 
void OneWireWriteByte(unsigned char); // writes a byte 
unsigned char OneWireReadByte(void); // reads a byte 
unsigned char OneWireRead(void); // reads the current status of the bus
void OneWireHigh(void); // sets the bus high
void OneWireRelease(void); // releases the bus 

#endif	/* ONEWIRE_H */


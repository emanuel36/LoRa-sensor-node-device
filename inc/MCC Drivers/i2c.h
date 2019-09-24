#ifndef I2C_H
#define	I2C_H

#define ACK 0
#define NACK 1

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../inc/MCC Drivers/mcc.h"

void I2C_Initialize();
void I2C_Ready();
void I2C_Ack();
void I2C_Nack();
bool I2C_Write(uint8_t data);
uint8_t I2C_Read(bool flag);
bool I2C_Start(uint8_t slave_write_address);
bool I2C_Stop();

#endif	/* I2C_H */

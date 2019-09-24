#include "../../inc/Peripheral Drivers/sht30.h"
#include "../../inc/MCC Drivers/i2c.h"

void SHT30Read(float *temp, float *humi){
    unsigned int dataT = 0, dataRH = 0;
    char checksumTemp = 0, checksumHumi = 0;
    
    I2C_Start(SHT30_ADRESS);
    I2C_Write(COMMAND_BYTE_1);
    I2C_Write(COMMAND_BYTE_2);
    I2C_Stop();
    
    I2C_Start(SHT30_ADRESS + 1);
    dataT = I2C_Read(ACK) << 8;
    dataT |= I2C_Read(ACK);
    checksumTemp = I2C_Read(0);
    dataRH = I2C_Read(ACK) << 8;
    dataRH |= I2C_Read(ACK);
    checksumHumi = I2C_Read(NACK);
    I2C_Stop();       
        
    *temp = (( (float) dataT * 175.0) / 65535.0) - 45.0;
    *humi = ( (float) dataRH * 100.0) / 65535.0;  
}

#include "max44009.h"

bool max44009Setup(){
    if(!(I2C_Start(MAX44009_ADDR)))      return false;
    if(!(I2C_Write(CONFIG_REGISTER)))    return false;
    if(!(I2C_Write(DEFAULT_CONFIG)))     return false;
    if(!(I2C_Stop()))                    return false;
}

bool max44009Read(float *lux){
    uint8_t dataH;
    uint8_t dataL;
    
    if(!(I2C_Start(MAX44009_ADDR)))      return false;
    I2C_Write(REQUEST_COMMAND);
    I2C_Stop();
    
    I2C_Start(MAX44009_ADDR + 1);
    dataH = I2C_Read(ACK);
    dataL = I2C_Read(NACK);
    I2C_Stop();
    
    uint8_t exponent = (dataH & 0xF0) >> 4;
    uint8_t mantissa = ((dataH & 0x0F) << 4) | (dataL & 0x0F);
    
    *lux = (float) (((0x00000001 << exponent) * (float) mantissa) * 0.045);
    
    return true;
}

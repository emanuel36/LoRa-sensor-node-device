#include <xc.h>
#include "main.h"
#include "mcu.h"
#include "adc.h"
#include "i2c.h"
#include "timer.h"
#include "oneWire.h"
#include "interrupt.h"
#include "supplyVoltage.h"
#include "max44009.h"
#include "sht30.h"
#include "ds18b20.h"
#include "statusLed.h"
#include "soilMoistureSensor.h"
#include "spi.h"
#include "sx1276.h"

void SYSTEM_Initialize(){
    OSCILLATOR_Initialize();
    SLEEP_Inicialize();
    PIN_MANAGER_Initialize();
    TMR0_Initialize(T5_MINUTES);
    TMR2_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    statusLed_Inicialize();
    ADC_Initialize();
    I2C_Initialize();
    SPI2_Initialize();
    oneWirePinInicialize();
    supplyPinInicialize();
    soilMoistureSensorPinInicialize();
    max44009Setup();
    SHT30Setup();
    ds18b20Setup();
    while(!begin(915000000)){
        __delay_ms(500);
        setSystemStatus(WARNING);
    }
    setSystemStatus(NORMAL);
}

void SLEEP_Inicialize(){
    VREGCONbits.VREGPM = 1;
    CPUDOZEbits.IDLEN = 0;
}

void OSCILLATOR_Initialize(){
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x06;
    // HFTUN 0; 
    OSCTUNE = 0x00;
}

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x3F;
    TRISC = 0x3B;

    /**
    ANSELx registers
    */
    ANSELC = 0x0F;
    ANSELA = 0x37;

    /**
    WPUx registers
    */
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONC = 0x3F;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLC = 0x3F;
    
    
    ANSA0 = 0;
    ANSA1 = 0;
    //RC3PPS = 0x0F;   //RC3->EUSART1:TX1; 
    SSP2DATPPS = 0x03;   //RA3->MSSP2:SDI2;    
    RC4PPS = 0x15;   //RC4->MSSP2:SCK2;    
    RC5PPS = 0x16;   //RC5->MSSP2:SDO2;      
    RA1PPS = 0x13;   //RA1->MSSP1:SCL1;    
    RA0PPS = 0x14;   //RA0->MSSP1:SDA1;    
    SSP1DATPPS = 0x00;   //RA0->MSSP1:SDA1;   
    SSP1CLKPPS = 0x01;   //RA1->MSSP1:SCL1;
}
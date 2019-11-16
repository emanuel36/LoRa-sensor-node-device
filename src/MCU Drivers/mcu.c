#include <pic16f18426.h>

#include "main.h"
#include "mcu.h"
#include "adc.h"
#include "i2c.h"
#include "timer.h"
#include "eusart.h"
#include "oneWire.h"
#include "interrupt.h"
#include "supplyVoltage.h"
#include "max44009.h"
#include "sht30.h"
#include "ds18b20.h"
#include "statusLed.h"
#include "soilMoistureSensor.h"
#include "spi.h"

void SYSTEM_Initialize(){
    OSCILLATOR_Initialize();
    SLEEP_Inicialize();
    PIN_MANAGER_Initialize();
    statusLed_Inicialize();
    setSystemStatus(NORMAL);
    ADC_Initialize();
    EUSART_Initialize();
    oneWirePinInicialize();
    supplyPinInicialize();
    I2C_Initialize();
    max44009Setup();
    SHT30Setup();
    ds18b20Setup();
//    SPI2_Initialize();
    TMR0_Initialize(T5_MINUTES);
    TMR2_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
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
    
//	SSP2DATPPS = 0x00;   //RA0->MSSP2:SDI2;    
//    RA1PPS = 0x16;   //RA1->MSSP2:SDO2;    
//    RA2PPS = 0x15;   //RA2->MSSP2:SCK2;    
//    SSP2CLKPPS = 0x02;   //RA2->MSSP2:SCK2; 
    
    ANSA5 = 0;
    ANSA4 = 0;
    RC0PPS = 0x0F;   //RC0->EUSART1:TX1;   
    SSP1CLKPPS = 0x05;   //RA5->MSSP1:SCL1; 
    RA5PPS = 0x13;   //RA5->MSSP1:SCL1;
    SSP1DATPPS = 0x04;   //RA4->MSSP1:SDA1; 
    RA4PPS = 0x14;   //RA4->MSSP1:SDA1; 
}
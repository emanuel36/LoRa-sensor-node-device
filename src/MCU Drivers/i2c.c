#include "i2c.h"
#include "mcu.h"

void I2C_Initialize(){
    //configurar canais como saida
    SSP1STATbits.SMP = 0x1;
    SSP1CON1bits.SSPEN = 0x1;
    SSP1CON1bits.SSPM = 0x8;
    SSP1ADD = ((_XTAL_FREQ/4000)/100) - 1;
}

void I2C_Ready(){
    while(!SSP1IF);	/* Wait for operation complete */
    SSP1IF = 0;		/* Clear SSPIF interrupt flag*/
}

void I2C_Ack(){
    ACKDT1 = 0;		/* Acknowledge data 1:NACK,0:ACK */
    ACKEN1 = 1;		/* Enable ACK to send */
    while(ACKEN1);
 }

void I2C_Nack(){
    ACKDT1 = 1;		/* Acknowledge data 1:NACK,0:ACK */
    ACKEN1 = 1;		/* Enable ACK to send */
    while(ACKEN1);
}

bool I2C_Write(uint8_t data){
    SSP1BUF = data;	/* Write data to SSPBUF*/
    I2C_Ready();
    if(ACKSTAT1)	/* Check for acknowledge bit*/
        return false;   /* Return 1 to indicate write failed */
    else
        return true;
}

uint8_t I2C_Read(bool flag){
    uint8_t buffer = 0;
    RCEN1 = 1;			/* Enable receive */

	/* Wait for buffer full flag which when complete byte received */
    while(!SSP1STATbits.BF);
    buffer = SSP1BUF;		/* Copy SSPBUF to buffer */

	/* Send acknowledgment or negative acknowledgment after read to 
	continue or stop reading */
    if(flag == 0)
        I2C_Ack();
    else
        I2C_Nack();
    I2C_Ready();
    return buffer;
}

bool I2C_Start(uint8_t slave_write_address){   
    SSP1CON2bits.SEN = 1;		/* Send start pulse */
    while(SSP1CON2bits.SEN);	/* Wait for completion of start pulse */
    SSP1IF = 0;
    if(!SSP1STATbits.S)		/* Check whether START detected last */
        return false;			/* Return 1 to indicate start failed */   
    return (I2C_Write(slave_write_address));	/* Write slave device address with write to communicate */
}

bool I2C_Stop(){
    PEN1 = 1;		/* Stop communication*/
    while(PEN1);		/* Wait for end of stop pulse*/
    I2C_Ready();
    if(!SSP1STATbits.P) /* Check whether STOP is detected last */
        return false;	/* If not return 0 to indicate start failed*/   
    return true;
}

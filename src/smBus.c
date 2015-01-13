#include "smBus.h"

/**
 * Definitions
 */
sbit SDA = P0 ^ 0; // SDA on pin 0.0
sbit SCL = P0 ^ 1; // SCL on pin 0.1

/**
 * Initialize SMBus
 */
void initializeSmBus(void)
{
    unsigned char i;
    while (!SDA) {
        SCL = 0;                   // Drive the clock low
        for (i = 0; i < 255; i++); // Hold the clock low
        SCL = 1;                   // Release the clock
        while (!SCL);              // Wait for open-drain clock output to rise
        for (i = 0; i < 10; i++);  // Hold the clock high
    }

    SMB0CF = 0x5d;  // Use Timer1 overflows as SMBus clock source
    SMB0CF |= 0x80; // Enable SMBus
    initializeTimer1(SYSTEM_CLOCK / SM_BUS_FREQUENCY / 4 / 3);
}

/**
 * Run SMBus
 */
void runSmBus(void)
{
    SI = 0;
    while (!SI);
}

/**
 * Start SMBus transmission
 */
void startSmBus(void)
{
    STA = 1;
    runSmBus();
    STA = 0;
}

/**
 * Acknowledge SMBus
 */
void acknowledgeSmBus(void)
{
    ACK = 1;
}

/**
 * Not acknowledge SMBus
 */
void notAcknowledgeSmBus(void)
{
    ACK = 0;
}

/**
 * Stop SMBus transmission
 */
void stopSmBus(void)
{
    STO = 1;
    while (!SI);
    STO = 0;
}

/**
 * Target an address on the SMBus
 */
void addressSmBus(unsigned char address, bit read)
{
    startSmBus();
    SMB0DAT = address << 1;
    if (read) {
        SMB0DAT |= 0x01;
    }
    runSmBus();
}

/**
 * Target a register on the SMBus
 */
void registerSmBus(unsigned char address, unsigned char registerAddress)
{   
    addressSmBus(address, 0);
    SMB0DAT = registerAddress;
    runSmBus();
}

/**
 * Write data on the SMBus
 */
void writeOnSmBus(unsigned char message)
{
    SMB0DAT = message;
    runSmBus();
}

/**
 * Read data from the SMBus
 */
unsigned char readFromSmBus()
{
    runSmBus();

    return SMB0DAT;
}

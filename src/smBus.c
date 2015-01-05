#include "smBus.h"

/**
 * Definitions
 */
sbit SDA = P0 ^ 0;             // SDA on pin 0.0
sbit SCL = P0 ^ 1;             // SCL on pin 0.1
bit smBusBusy;                 // 1 if the SMBus is being used, 0 otherwise
bit smBusMode;                 // 1 if the SMBus is in write mode, 0 otherwise
bit subAddressSent;            // 1 if the sub address has been sent
bit dataSent;                  // 1 if the data has been sent
bit smBusFailed;               // 1 if the transfer failed
unsigned char smBusAddress;    // SMBus address container
unsigned char smBusSubAddress; // SMBus sub-address container
unsigned char smBusData = 0;   // SMBus data container

/**
 * Initialize SMBus
 */
void initializeSmBus(void)
{
	unsigned char i;
    while (!SDA) {
        XBR1 = 0x40;              // Enable Crossbar
        SCL = 0;                  // Drive the clock low
        for(i = 0; i < 255; i++); // Hold the clock low
        SCL = 1;                  // Release the clock
        while(!SCL);              // Wait for open-drain clock output to rise
        for(i = 0; i < 10; i++);  // Hold the clock high
        XBR1 = 0x00;              // Disable Crossbar
    }

    SMB0CF = 0x5D;
    SMB0CF |= 0x80;
    EIE1 |= 0x01;
}

/**
 * Write data on the SMBus
 */
void writeOnSmBus(unsigned char address, unsigned char subAddress, unsigned char message, bit important)
{
    bit success = 0;
    while (!success) {
        claimSmBus(1);
        smBusAddress = address;
        smBusSubAddress = subAddress;
        smBusData = message;
        STA = 1;
        freeSMBus();

        if (!important) {
            success = 1;
        } else {
            success = !smBusFailed;
        }
    }
}

/**
 * Read data from the SMBus
 */
unsigned char readFromSmBus(unsigned char address, unsigned char subAddress, bit important)
{
    bit success = 0;
    while (!success) {
        claimSmBus(0);
        smBusAddress = address;
        smBusSubAddress = subAddress;
        STA = 1;
        freeSMBus();

        if (!important) {
            success = 1;
        } else {
            success = !smBusFailed;
        }
    }

    return smBusData;
}

/**
 * Claim the SMBus
 */
void claimSmBus(bit mode)
{
	while (!smBusBusy);
    smBusBusy = 1;
    smBusMode = mode;
}

/**
 * Free the SMBus
 */
void freeSmBus(void)
{
    while (!smBusBusy);
}

/**
 * SMBus Interrupt Service Routine
 */
void smBusInterruptServiceRoutine(void) interrupt 7
{
    bit failed = 0;

    if (ARBLOST == 0) {
        switch (SMB0CN & 0xF0) {

            case SMB_MTSTA:
                SMB0DAT = smBusAddress; // Load address of the target slave
                SMB0DAT &= 0xFE;        // Clear the LSB of the address for the R/W bit
                SMB0DAT |= smBusMode;   // Load R/W bit
                subAddressSent = 0;     // Sub address not sent yet
                dataSent = 0;           // Data not sent yet
                smBusFailed = 0;        // Transfer has not failed yet
                STA = 0;                // Manually clear START bit
            break;

            case SMB_MTDB:
                if (ACK) {
                    if (subAddressSent) {
                        if (smBusMode) {
                            if (dataSent) {
                                STO = 1;       // Set STO to terminate transfer
                                smBusBusy = 0; // And free SMBus interface
                            } else {
                                SMB0DAT = smBusData;
                                dataSent = 1;
                            }
                        }
                    } else {
                        SMB0DAT = smBusSubAddress;
                        subAddressSent = 1;
                    }                 
                } else {
                    STO = 1; // Send STOP condition
                    STA = 1; // Send START condition
                    failed = 1;
                }
            break;

            case SMB_MRDB:
                smBusData = SMB0DAT;
                smBusBusy = 0;
                ACK = 0;
                STO = 1;
            break;

            default:
                failed = 1;
            break;
        }
    } else {
        failed = 1;
    }

    if (failed) {
        SMB0CF &= ~0x80; // Reset communication
        SMB0CF |= 0x80;
        STA = 0;
        STO = 0;
        ACK = 0;
        smBusBusy = 0;   // Free SMBus
        smBusFailed = 1; // Transfer failed
        failed = 0;
    }

    SI = 0; // Clear interrupt flag
}

/**
 * Timer 3 Interrupt Service Routine for the SMBus
 */
void timer3InterruptServiceRoutine(void) interrupt 14
{
    SMB0CF &= ~0x80; // Disable SMBus
    SMB0CF |= 0x80;  // Re-enable SMBus
    TMR3CN &= ~0x80; // Clear Timer3 interrupt-pending flag
    STA = 0;
    smBusBusy = 0;    // Free SMBus
}

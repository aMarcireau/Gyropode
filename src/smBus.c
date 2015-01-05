#include "smBus.h"

/**
 * Definitions
 */
sbit SDA = P0 ^ 0;
sbit SCL = P0 ^ 1;
bit smBusBusy;                                 // 1 if the SMBus is beaing used, 0 otherwise
bit smBusMode;                                 // 1 if the SMBus is in write mode, 0 otherwise
unsigned char smBusTarget;                     // SMBus target container
unsigned char smBusRead[SM_BUS_READ_LENGTH];   // SMBus readen data container 
unsigned char smBusWrite[SM_BUS_WRITE_LENGTH]; // SMBus data to be written container

/**
 * Initialize SMBus
 */
void initializeSmBus()
{
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
void writeOnSMBus(unsigned char target, unsigned char data)
{
    claimSMBus(1);
    smBusWrite = data;
    STA = 1;
    freeSMBus();
}

/**
 * Read data from the SMBus
 */
unsigned char readFromSMBus(unsigned char target)
{
    claimSMBus(0);
    smBusTarget = target;
    STA = 1;
    freeSMBus();

    return smBusRead;
}

/**
 * Claim the SMBus
 */
void claimSMBus(bit mode)
{
	while (!smBusBusy);
    smBusBusy = 1;
    smBusMode = mode;
}

/**
 * Free the SMBus
 */
void freeSMBus()
{
    while (!smBusBusy);
}

/**
 * SMBus Interrupt Service Routine
 */
void smBusInterruptServiceRoutine(void) interrupt 7
{
    bit failed = 0;
    static unsigned char readCounter;
    static unsigned char writeCounter;

    if (ARBLOST == 0) {
        switch (SMB0CN & 0xF0) {

            case SMB_MTSTA:
                SMB0DAT = smBusTarget; // Load address of the target slave
                SMB0DAT &= 0xFE;       // Clear the LSB of the address for the R/W bit
                SMB0DAT |= smBusMode;  // Load R/W bit
                STA = 0;               // Manually clear START bit
                readCounter = 1;       // Reset counter
                writeCounter = 1;      // Reset counter
            break;

            case SMB_MTDB:
                if (ACK) {
                    if (smBusMode == 1) {
                        if (writeCounter <= SM_BUS_WRITE_LENGTH) {
                            SMB0DAT = smBusWrite[writeCounter - 1];
                            writeCounter++;
                        } else {
                            STO = 1;       // Set STO to terminate transfer
                            smBusBusy = 0; // And free SMBus interface
                        }
                    }
                } else {
                    STO = 1; // Send STOP condition, followed
                    STA = 1; // By a START
                }
            break;

            case SMB_MRDB:
                if (readCounter < SM_BUS_READ_LENGTH) {
                    smBusRead[readCounter - 1] = SMB0DAT;
                    ACK = 1;
                    readCounter++;
                } else {
                    smBusRead[readCounter - 1] = SMB0DAT;
                    smBusBusy = 0;
                    ACK = 0;
                    STO = 1;
                }
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
        failed = 0;
    }

    SI = 0; // Clear interrupt flag
}

/**
 * Timer 3 Interrupt Service Routine for the SMBus
 */
void timer3InterruptServiceRoutine (void) interrupt 14
{
    SMB0CF &= ~0x80; // Disable SMBus
    SMB0CF |= 0x80;  // Re-enable SMBus
    TMR3CN &= ~0x80; // Clear Timer3 interrupt-pending flag
    STA = 0;
    smBusBusy = 0;    // Free SMBus
}

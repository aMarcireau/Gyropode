#ifndef __SEGWAY__SM_BUS__
#define __SEGWAY__SM_BUS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#define  SMB_MTSTA 0xE0  	  // (MT) start transmitted
#define  SMB_MTDB 0xC0  	  // (MT) data byte transmitted
#define  SMB_MRDB 0x80        // (MR) data byte received
#define SM_BUS_READ_LENGTH 8  // 
#define SM_BUS_WRITE_LENGTH 8 //

void initializeSmBus();               	 					                      // Initialize the SMBus
void writeOnSMBus(unsigned char target, unsigned char data[SM_BUS_WRITE_LENGTH]); // Write data on the SMBus
unsigned char readFromSMBus(unsigned char target);       	 					  // Read data from the SMBus
void claimSMBus();											 					  // Claim the SMBus
void freeSMBus();											 				      // Free the SMBus

#endif // __SEGWAY__SM_BUS__

#ifndef __SEGWAY__SM_BUS__
#define __SEGWAY__SM_BUS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#define  SMB_MTSTA 0xE0 // (MT) start transmitted
#define  SMB_MTDB 0xC0  // (MT) data byte transmitted
#define  SMB_MRDB 0x80  // (MR) data byte received

void initializeSmBus(void);               	 					                                           // Initialize the SMBus
void writeOnSMBus(unsigned char address, unsigned char subAddress, unsigned char data, bit important = 1); // Write data on the SMBus
unsigned char readFromSMBus(unsigned char address, unsigned char subAddress, bit important = 1);   		   // Read data from the SMBus
void claimSMBus(void);   									 					                           // Claim the SMBus
void freeSMBus(void);	    								 				                               // Free the SMBus

#endif // __SEGWAY__SM_BUS__

#ifndef __SEGWAY__SM_BUS__
#define __SEGWAY__SM_BUS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "timers.h"

#define SYSTEM_CLOCK 24500000
#define SM_BUS_FREQUENCY 10000

void initializeSmBus(void);                                               // Initialize SMBus
void runSmBus(void);                                                      // Run SMBus
void startSmBus(void);                                                    // Start SMBus
void acknowledgeSmBus(void);                                              // Acknowledge SMBus
void notAcknowledgeSmBus(void);                                           // Not acknowledge SMBus
void stopSmBus(void);                                                     // Stop SMBus transmission
void addressSmBus(unsigned char address, bit read);                       // Target an address on the SMBus
void registerSmBus(unsigned char address, unsigned char registerAddress); // Target a register on the SMBus
void writeOnSmBus(unsigned char message);                                 // Write data on the SMBus
unsigned char readFromSmBus();                                            // Read data from the SMBus

#endif // __SEGWAY__SM_BUS__

#ifndef __SEGWAY__UART__
#define __SEGWAY__UART__

#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <stdio.h>

void initializeUart(void);	     // Initialize UART output
void Put_char_(unsigned char c); // Surcharge Put_char_ stdio method

#endif // __SEGWAY__UART__

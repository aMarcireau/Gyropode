#include "uart.h"

/**
 * Initialize UART
 */
void initializeUart(void) {
    REN0 = 1;     // UART reception enabled
    SBUF0 = '\n'; // Initialize connection with a first character
}

/**
 * Surcharge Put_char_ stdio method
 */
void Put_char_(unsigned char c) {
    while (TI0 == 0);
    TI0 = 0;
    SBUF0 = c;
}

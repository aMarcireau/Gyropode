#include "uart.h"

/**
 * Initialize UART output
 */
void initializeUart(void) {
	TH1 = -213;
	TMOD |= 0x20;
	CKCON |= 0x08;
	TR1 = 1;
	REN0 = 1;
	SBUF0 = '\n';
}

/**
 * Surcharge Put_char_ stdio method
 */
void Put_char_(unsigned char c) {
	while (TI0 == 0);
	TI0 = 0;
	SBUF0 = c;
}

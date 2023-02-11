#include "watchdog.h"

void WatchdogInit()
{
	// enable watchdog interrupt mode
	// disable watchdog
	wdt_disable();
	//// reset watchdog timer
	//wdt_reset();
	//// start timed watchdog setup sequence
	//WDTCSR |= (1 << WDCE) | (1 << WDE);
	//// set 250 ms watchdog timeout and enable interrupt
	//WDTCSR = (1 << WDIE) | (1 << WDP2);
}

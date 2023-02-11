#pragma once

#include "stdbool.h"

#include <avr/wdt.h>

void WatchdogInit();

inline void HandleReset()
{
	if (MCUSR & (1 << PORF)) { // power-on reset
		MCUSR = 0;
	} else if (MCUSR & (1 << EXTRF)) { // external reset
		MCUSR = 0;
	} else if (MCUSR & (1 << BORF)) { // brown-out reset
		MCUSR = 0;
	} else if (MCUSR & (1 << WDRF)) { // watchdog reset
		MCUSR = 0;
	}
}

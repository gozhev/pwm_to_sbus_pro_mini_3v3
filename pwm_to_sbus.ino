#include "gpio.h"
#include "pwm.h"
#include "sbus.h"
#include "timers.h"
#include "watchdog.h"

#include <util/delay.h>

#if !defined (__AVR_ATmega328P__) && !defined (__AVR_ATmega328__)
#error Unsupported platform
#endif

int main()
{
	WatchdogInit();
	GpioInit();
	PwmInit();
	SbusInit();
	TimersInit();
	sei();
	while (true) {
		PwmProcessBuffer();
		SbusBuildPacket();
		SbusWrite();
		_delay_ms(8);
	}

	return 0;
}

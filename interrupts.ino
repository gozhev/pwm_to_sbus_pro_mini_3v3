#include "gpio.h"
#include "pwm.h"

#include <avr/interrupt.h>

ISR(PCINT0_vect, ISR_ALIASOF(PCINT2_vect));

ISR(PCINT2_vect)
{
	pwm_buffer_write->ticks = PwmGetTicks();
	pwm_buffer_write->pins = GpioGetPinsState();
	pwm_buffer_write = PwmBufferFrameNext(pwm_buffer_write);
}

#pragma once

void GpioInit();

inline void GpioInterruptsClear()
{
	PCIFR |= ((1 << PCIF2) | (1 << PCIF0));
}

inline uint8_t GpioGetPinsState()
{
	return ((PIND & 0b11111100) | (PINB & 0b00000011));
}

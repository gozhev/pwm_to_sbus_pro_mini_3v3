#include "gpio.h"

#include <avr/io.h>

void GpioInit()
{
	// switch off led
	DDRB |= (1 << 5);
	PORTB &= ~(1 << 5);

	// pwm input pins
	DDRD &= ~0b11111100;
	DDRB &= ~0b00000011;

	// activate pull-ups on all input pins
	PORTD |= 0b11111100;
	PORTB |= 0b00000011;

	// set input interrupt pin mask to all pwm input channels
	PCMSK2 |= 0b11111100;
	PCMSK0 |= 0b00000011;

	// enable pwm input interrupt
	PCICR |= ((1 << PCIE2) | (1 << PCIE0));

	// disable usart0 (free D1 and D0 pins)
	UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));

	// set PORTD1 as sbus output
	PORTD &= ~(1 << 1);
	DDRD |= (1 << 1);
}

#include "timers.h"

void Timer0Init()
{
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;
	TIFR0 = 0;
	TCNT0 = 0;
	OCR0A = 0;
	OCR0B = 0;
}

void Timer1Init()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 = 0;
	TIFR1 = 0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;

	// set prescaler & enable timer
	TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
}

void Timer2Init()
{
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	TIFR2 = 0;
	TCNT2 = 0;
	OCR2A = 79;
	OCR2B = 0;

	// select mode of operation
	TCCR2B |= (0 << WGM22);
	TCCR2A |= (1 << WGM21) | (0 << WGM20);
	// select pwm port mode
	TCCR2A |= (0 << COM2A1) | (0 << COM2A0);
	TCCR2A |= (0 << COM2B1) | (0 << COM2B0);
	// select interrupts
	TIMSK2 |= (0 << OCIE2B) | (0 << OCIE2A) | (0 << TOIE2);
	// select prescaler & enable timer
	TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
}

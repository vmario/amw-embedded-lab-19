#include "gpio.hpp"

#include <avr/io.h>
#include <util/delay.h>

const Gpio gpio;

void Gpio::initialize() const
{
	// SPI
	DDRB |= _BV(PB5) | _BV(PB3);
	DDRD |= _BV(PD1);
	PORTD |= _BV(PD1);

	// FSYNC
	DDRD |= _BV(PD0);
}

void Gpio::chipSelect(bool state) const
{
	if (state) {
		PORTD &= ~_BV(PD1);
		_delay_us(1);
	} else {
		_delay_us(1);
		PORTD |= _BV(PD1);
	}
}

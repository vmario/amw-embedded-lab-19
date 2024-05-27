#include "spi.hpp"

#include "gpio.hpp"

#include <avr/io.h>
#include <util/delay.h>

const Spi spi;

void Spi::initialize() const
{
}

uint8_t Spi::transfer(uint8_t byte=0) const
{
	return 0;
}

uint8_t Spi::readRegister(uint8_t address) const
{
	return 0;
}

int16_t Spi::readRegisterWord(uint8_t address) const
{
	return 0;
}

void Spi::writeRegister(uint8_t address, uint8_t value) const
{
	gpio.chipSelect(true);

	transfer(address);
	transfer(value);

	gpio.chipSelect(false);
}

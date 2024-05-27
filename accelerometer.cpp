#include "accelerometer.hpp"

#include "gpio.hpp"
#include "spi.hpp"

#include <avr/io.h>
#include <util/delay.h>

const Accelerometer accelerometer;

/**
 * Adresy rejestrów akcelerometru.
 */
enum REGISTER {
	REGISTER_SMPLRT_DIV = 25,
	REGISTER_CONFIGURATION = 26,
	REGISTER_ACCEL_CONFIG_2 = 29,
	REGISTER_ACCEL_XOUT_H = 59,
	REGISTER_SIGNAL_PATH_RESET = 104,
	REGISTER_USER_CTRL = 106,
	REGISTER_POWER_MGMT_1 = 107,
	REGISTER_WHO_AM_I = 117,
};

/**
 * Wybrane nastawy czujnika.
 */
enum {
	DEVICE_RESET = _BV(7) | _BV(0),
	SIGNAL_RESET = _BV(2) | _BV(1) | _BV(0),
};

void Accelerometer::initialize() const
{
	gpio.initialize();
	spi.initialize();

	spi.writeRegister(REGISTER_POWER_MGMT_1, DEVICE_RESET);
	_delay_ms(100);

	spi.writeRegister(REGISTER_SIGNAL_PATH_RESET, SIGNAL_RESET);
	_delay_ms(100);

	spi.writeRegister(REGISTER_CONFIGURATION, 6);
	spi.writeRegister(REGISTER_ACCEL_CONFIG_2, 6);
}

uint8_t Accelerometer::whoAmI() const
{
	return 0;
}

int16_t Accelerometer::measure() const
{
	return 0;
}

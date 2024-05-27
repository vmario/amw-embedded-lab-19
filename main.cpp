#include "adc.hpp"
#include "keypad.hpp"
#include "lcdDisplay.hpp"
#include "menu.hpp"
#include "thermostat.hpp"

#include <util/atomic.h>

#include <stdio.h>

/**
 * Obsługuje wyświetlacz i logikę termostatu.
 */
void mainLoop()
{
	char buf[DISPLAY_LENGTH + 1];

	double temperature;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		keypad.measure(keyboardAdc);
		temperature = 1.1 * temperatureAdc / 1024 * 100;
	}

	lcdDisplay.goTo(0, 0);
	lcdDisplay.write("test");
}

/**
 * Funkcja główna.
 */
int main()
{
	constexpr uint8_t DEGREE[] = {
		0b00000010,
		0b00000101,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	};

	constexpr uint8_t NEGATIVE_ARROW[] = {
		0b00011111,
		0b00011011,
		0b00011101,
		0b00000000,
		0b00011101,
		0b00011011,
		0b00011111,
		0b00000000,
	};

	constexpr uint8_t ELLIPSIS[] = {
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00010101,
		0b00000000,
	};

	lcdDisplay.initialize();
	lcdDisplay.addSymbol(DEGREE, DISPLAY_CODE_DEGREE);
	lcdDisplay.addSymbol(NEGATIVE_ARROW, DISPLAY_CODE_NEGATIVE_ARROW);
	lcdDisplay.addSymbol(ELLIPSIS, DISPLAY_CODE_ELLIPSIS);

	adc.initialize();
	sei();

	while (true) {
		mainLoop();
	}
}

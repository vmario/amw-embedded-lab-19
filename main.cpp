#include "lcdDisplay.hpp"
#include "menu.hpp"
#include "accelerometer.hpp"

#include <stdio.h>

/**
 * Obsługuje wyświetlacz i pomiar położenia.
 */
void mainLoop()
{
	char buf[DISPLAY_LENGTH + 1];
	int16_t value{accelerometer.measure()};

	lcdDisplay.goTo(1, 3);
	snprintf(buf, sizeof(buf), "0x%04x=%6d", value, value);
	lcdDisplay.write(buf);

	lcdDisplay.goTo(0, 7);
	lcdDisplay.write("||");
}

/**
 * Funkcja główna.
 */
int main()
{
	lcdDisplay.initialize();
	menu.initialize();
	accelerometer.initialize();

	uint8_t value{accelerometer.whoAmI()};

	lcdDisplay.goTo(1, 0);
	char buf[DISPLAY_LENGTH + 1];
	snprintf(buf, sizeof(buf), "%02x", value);
	lcdDisplay.write(buf);

	while (true) {
		mainLoop();
	}
}

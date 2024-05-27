#include "menu.hpp"

#include "lcdDisplay.hpp"

#include <util/delay.h>

Menu menu;

void Menu::initialize() const
{
	lcdDisplay.clear();
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write(" Initializing   ");
	showProgress();
	lcdDisplay.clear();
}

void Menu::showProgress() const
{
	lcdDisplay.goTo(1, 0);
	for (int i{0}; i < DISPLAY_LENGTH; ++i) {
		lcdDisplay.write('\xff');
		_delay_ms(40);
	}
}

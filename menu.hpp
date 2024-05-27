#pragma once

#include <stdint.h>

constexpr uint8_t DISPLAY_LENGTH{16}; ///< Szerokość wyświetlacza.

/**
 * Menu wyświetlacza.
 */
struct Menu {
	/**
	 * Inicjalizacja menu.
	 */
	void initialize() const;

	/**
	 * Pasek postępu.
	 */
	void showProgress() const;
};

extern Menu menu; ///< Globalna instancja menu.

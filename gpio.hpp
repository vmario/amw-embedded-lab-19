#pragma once

/**
 * Sterownik GPIO
 */
struct Gpio {
	/**
	 * Inicjalizuje sterownik.
	 */
	void initialize() const;

	/**
	 * Ustawia linię CS.
	 *
	 * @param state Czy linia ma być aktywna?
	 */
	void chipSelect(bool state) const;
};

extern const Gpio gpio; ///< Instancja sterownika GPIO.

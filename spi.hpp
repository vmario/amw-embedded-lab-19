#pragma once

#include <stdint.h>

/**
 * Sterownik magistrali SPI dla czujnika MPU-6500.
 */
struct Spi {
	/**
	 * Inicjalizuje magistralę.
	 */
	void initialize() const;

	/**
	 * Wysyła i odczytuje pojedynczy bajt.
	 *
	 * @param byte Bajt do wysłania.
	 *
	 * @return Odczytany bajt.
	 */
	uint8_t transfer(uint8_t byte) const;

	/**
	 * Odczytuje wartość wskazanego rejestru.
	 *
	 * @param address Adres rejestru.
	 *
	 * @return Wartość odczytana z rejestru.
	 */
	uint8_t readRegister(uint8_t address) const;

	/**
	 * Odczytuje 16-bitowe słowo ze znakiem z rejestru.
	 *
	 * @param address Adres rejestru.
	 *
	 * @return Wartość odczytana z rejestru.
	 */
	int16_t readRegisterWord(uint8_t address) const;

	/**
	 * Zapisuje wartość do rejestru.
	 *
	 * @param address Adres rejestru.
	 * @param value Bajt do zapisania.
	 */
	void writeRegister(uint8_t address, uint8_t value) const;
};

extern const Spi spi; ///< Instancja sterownika SPI.

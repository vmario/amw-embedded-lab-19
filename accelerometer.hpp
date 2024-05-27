#pragma once

#include <stdint.h>

/**
 * Sterownik akcelerometru/żyroskopu MPU-6500.
 */
struct Accelerometer {
	/**
	 * Inicjalizuje akcelerometr i szynę danych.
	 */
	void initialize() const;

	/**
	 * Odczytuje identyfikator układu scalonego.
	 *
	 * @return Identyfikator.
	 */
	uint8_t whoAmI() const;

	/**
	 * Odczytuje pomiar.
	 *
	 * @return Wynik pomiaru.
	 */
	int16_t measure() const;
};

/**
 * Instancja sterownika akcelerometru.
 */
extern const Accelerometer accelerometer;

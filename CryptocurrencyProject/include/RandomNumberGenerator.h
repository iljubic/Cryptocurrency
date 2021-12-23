#pragma once

#include <random>


class RandomNumberGenerator {
private:
	// Inputted
	int minimum;
	int maximum;
	int seedInt;

	int randomNumber;
public:
	RandomNumberGenerator(int min, int max, int seed);

	void refreshNumber();

	// Getters
	int getRandomNumber();	// Returns the calculated randomNumber from the RNG constructor
};

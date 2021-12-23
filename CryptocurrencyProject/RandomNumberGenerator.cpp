#include "RandomNumberGenerator.h"


RandomNumberGenerator::RandomNumberGenerator(int min, int max, int seed) {
	minimum = min;
	maximum = max;
	seedInt = seed;

	std::mt19937 rng(seedInt);									// Inputting the seed
	std::uniform_int_distribution<int> gen(minimum, maximum);	// Uniform, unbiased RNG

	int randomNumber = gen(rng);
}

void RandomNumberGenerator::refreshNumber() {
	std::mt19937 rng(seedInt);									// Inputting the seed
	std::uniform_int_distribution<int> gen(minimum, maximum);	// Uniform, unbiased RNG

	gen(rng);
	int randomNumber = gen(rng);
}

int RandomNumberGenerator::getRandomNumber() {
	return randomNumber;
}

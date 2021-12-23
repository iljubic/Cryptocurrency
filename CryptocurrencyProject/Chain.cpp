#include "Chain.h"


Chain::Chain(std::string n, std::time_t t) {
	// Set Inputted Data
	name = n;
	timestamp = t;

	// Set Generated Data
	hash = generateHash();

	// Create the genesis shard and put it into the cahin
	Shard genesis = generateGenesisShard();
	chain.push_back(genesis);
}

// Generates the genesis shard (the first shard in the chain)
Shard Chain::generateGenesisShard() {
	time_t current;

	Shard genesis(0, time(&current));
	return genesis;
}

// Generates a Blockchain hash with the name and time that was inputted in the constructor
std::string Chain::generateHash() {
	SHA512 sha;
	return sha.hash(std::to_string(timestamp) + name);
}

// Getters
std::vector<Shard> Chain::getChain() {
	return chain;
}

#pragma once

#include <vector>
#include <ctime>
#include <string>
#include "Shard.h"


class Chain {
private:
	// Inputted Data
	std::string name;			// The name of the Blockchain
	std::time_t timestamp;		// The time the Blockchain was created

	// Generated Data
	std::string hash;			// Unique Blockchain Identifier
	std::vector<Shard> chain;	// The Entire Blockchain/Shardchain

	// Generator Functions
	std::string generateHash();		// Generates the Blockchain hash
	Shard generateGenesisShard();	// Generates the genesis shard
public:
	Chain(std::string n, std::time_t t);

	// Getters
	std::vector<Shard> getChain();
};

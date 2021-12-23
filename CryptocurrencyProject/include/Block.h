#pragma once

#include <vector>
#include <string>
#include <ctime>
#include "Signature.h"
#include "SHA512.h"


class Block {
private:
	int index;						// The index of the block in the shard it is in
	double shardIndex;				// The index of the shard the block is in
	Signature signature;			// The transaction signature
	std::string hash;				// The block hash
	std::string prevHash;			// The previous blocks hash
	std::string shardHash;			// The hash of the shard the block is in
	
	std::string generateHash();		// Hash Generator Function
public:
	Block(int i, int sI, Signature s, std::string pH, std::string sH);

	// Getters
	Signature getSignature();		// Gets the block signature
	std::string getHash();			// Gets the block hash
};

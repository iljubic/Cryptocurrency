#include "Block.h"


Block::Block(int i, int sI, Signature s, std::string pH, std::string sH) {
	index = i;
	shardIndex = sI;
	signature = s;
	prevHash = pH;
	shardHash = sH;

	hash = generateHash();
}

// Generates a Block hash with the index, shardIndex, prevHash and shardHash that was inputted in the constructor
std::string Block::generateHash() {
	SHA512 sha;
	return sha.hash(
		std::to_string(index) + 
		std::to_string(shardIndex) + 
		prevHash + 
		shardHash);
}

// Getters
Signature Block::getSignature() {
	return signature;
}

std::string Block::getHash() {
	return hash;
}

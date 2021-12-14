#include "Block.h"


Block::Block(int i, TransactionData d, std::size_t pBH) {
	index = i;
	data = d;
	prevBlockHash = pBH;

	blockHash = generateBlockHash();
}


std::size_t Block::generateBlockHash() {
	// Creating hashes to be added into the finalHash
	std::hash<std::string> hash1;
	std::hash<std::size_t> hash2;
	std::hash<std::size_t> hash3;
	std::hash<std::size_t> finalHash;

	// Converting TransactionData variables into hashable data
	std::string toHash0 = std::to_string(data.amount) + std::to_string(data.timestamp);
	std::size_t toHash1 = data.receiverAddress + data.senderAddress;

	return finalHash(hash1(toHash0) + hash2(toHash1) + hash3(prevBlockHash));	// Combining all data into one hash and returning it
}

bool Block::isHashValid() {
	return generateBlockHash() == blockHash;	// Returns true if the generateBlockHash() output is the same as the blockHash
}


// Getter Functions
int Block::getIndex()
{
	return index;
}

std::size_t Block::getBlockHash() {
	return blockHash;
}

std::size_t Block::getPrevBlockHash() {
	return prevBlockHash;
}

TransactionData Block::getTransactionData() {
	return data;
}

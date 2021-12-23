#pragma once

#include <vector>
#include "Stake.h"
#include "Block.h"


class Node : public Stake {
private:
	std::vector<Block> pendingBlocks;
	std::size_t verifiedKey;

	std::size_t walletPrivateKey;			// Wallet Private Key

	std::size_t generateVerifiedKey();		// Generates a verified hash/key after a block has been validated using data from the block and verification process
public:
	Node();

	// Adds an unverifiedBlock to the pendingBlocks vector
	void addUnverifiedBlock(std::size_t pendingBlockhash);
	// Returns true if the oldest block in pendingBlocks is true
	bool isBlockValid(std::size_t pendingBlockHash);
	// Sends the verified block to the blockchain
	void sendVerifiedBlock(std::size_t pendingBlockHash, std::size_t verifiedKey);
};

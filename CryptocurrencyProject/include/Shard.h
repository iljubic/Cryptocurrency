#pragma once

#include <vector>
#include <ctime>
#include "Block.h"


class Shard {
private:
	int index;							// The position of the shard in regards to the overall Blockchain
	std::time_t time;					// The time the shard was created
	std::size_t hash;					// The unique hash for the shard
	std::vector<Block> chain;			// The chain of blocks in the shard
	const int blocksPerShard = 100;		// The max amount of blocks per shard

	std::size_t generateHash();			// Hash Generator
	void generateGenesisBlock();		// Generates a genesis block if this is the first shard ever created
public:
	Shard(int i, std::time_t t);

	// Adds a block to the chain of blocks on the shard (only if the block is verified by the majority of nodes that are staking currency)
	void addVerifiedBlock(Block block, std::size_t verificationKey);

	// Getters
	Block getBlock(int i);				// Gets the block related to the index inputted
	Shard getPrevShard();				// Gets the shard related to the index inputted
	std::vector<Block> getChain();		// Gets the chain of blocks in the shard
	std::size_t getHash();				// Gets the shard hash
};

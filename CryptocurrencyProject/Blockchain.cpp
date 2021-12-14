#include "Blockchain.h"


Blockchain::Blockchain()
{
	// Create the genesis block
	Block genesis0 = createGenesisBlock();
	blockChain.push_back(genesis0);

	// Create the genesis address
	Wallet genesis1 = createGenesisAddress();
	walletChain.push_back(genesis1);
}


// Genesis Generators
Block Blockchain::createGenesisBlock()
{
	time_t current;									// Temporary Timestamp
	TransactionData d(0, 0, 0, time(&current));		// Temporary TransactionData

	Block genesis(0, d, 0);							// Creating a genesis block with configured data
	return genesis;									// Returning the genesis block
}

Wallet Blockchain::createGenesisAddress()
{
	std::hash<int> hash;			// Temporary Hash
	time_t current;					// Temporary Timestamp

	Wallet genesis(0, time(&current), hash(0));		// Creating a genesis wallet with configured data
	return genesis;					// Returning the genesis wallet
}


std::vector<Block> Blockchain::getBlockChain() {
	return blockChain;
}

std::vector<Wallet> Blockchain::getWalletChain() {
	return walletChain;
}

// Adders
void Blockchain::addBlock(TransactionData data)
{
	Block newBlock(blockIndex, data, blockChain.back().getBlockHash());		// Creating a block;
	blockChain.push_back(newBlock);
	blockIndex = blockIndex + 1;	// Incrementing the blockIndex by 1
	int blockIndex = (int)blockChain.size();
}

void Blockchain::addWallet(time_t t)
{
	Wallet newWallet(walletIndex, t, walletChain.back().getAddressHash());
	walletChain.push_back(newWallet);
	walletIndex = walletIndex + 1;	// Incrementing the walletIndex by 1
}


// Validation
bool Blockchain::isChainValid()
{
	// Checking Block/Transaction Blockchain
	std::vector<Block>::iterator it0;
	int blockChainLen = (int)blockChain.size();
	for (it0 = blockChain.begin(); it0 != blockChain.end(); ++it0) {
		Block currentBlock = *it0;
		if (!currentBlock.isHashValid()) {
			return false;
		}
		if (blockChainLen > 2) {
			Block prevBlock = *(it0 - 1);
			if (currentBlock.getPrevBlockHash() != prevBlock.getBlockHash()) {
				return false;
			}
		}
	}

	// Checking wallet blockchain
	std::vector<Wallet>::iterator it1;
	int walletChainLen = (int)walletChain.size();
	for (it1 = walletChain.begin(); it1 != walletChain.end(); ++it1) {
		Wallet currentWallet = *it1;
		if (!currentWallet.isHashValid()) {
			return false;
		}
		if (walletChainLen > 2) {
			Wallet prevWallet = *(it1 - 1);
			if (currentWallet.getPrevAddressHash() != prevWallet.getAddressHash()) {
				return false;
			}
		}
	}

	return true;
}

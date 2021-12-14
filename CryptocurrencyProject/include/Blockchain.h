#pragma once

#include "Block.h"
#include "Wallet.h"
#include <ctime>
#include <vector>
#include <string>
#include <stdio.h>


class Blockchain {						         	// Blockchain Class
private:
	int blockIndex = 1;					         	// Keeps count of the number of blocks on the blockchain - starting from 1 (including genesis block)
	int walletIndex = 1;				         	// Keeps count of the number of wallets on the blockchain - starting from 1 (including genesis wallet)

	std::vector<Block> blockChain;		  	// Stores the blockchain
	std::vector<Wallet> walletChain;		  // Stores the wallets

	Block createGenesisBlock();		    		// Creates the genesis Block
	Wallet createGenesisAddress();		   	// Creates the genesis Address
public:
	Blockchain();

	std::vector<Block> getBlockChain();
	std::vector<Wallet> getWalletChain();

	void addBlock(TransactionData data);	// Adds a block to the blockchain
	void addWallet(time_t t);			      	// Adds a wallet to the blockchain

	bool isChainValid();			        		// BlockChain Validator
};

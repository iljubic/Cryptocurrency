#pragma once

#include "Wallet.h"
#include "TransactionData.h"
#include <vector>
#include <ctime>
#include <string>


class Block {							              	// Block Class
private:
	int index;							               	// Keeps count of the index of the block in the blockchain
	
	std::size_t blockHash;			        		// The hash for this block
	std::size_t prevBlockHash;		      		// The previous blocks hash
	TransactionData data;				      	    // The TransactionData stored in the block
  
	std::size_t generateBlockHash();	    	// Block Hash Generator
public:
	Block(int i, TransactionData d, std::size_t pBH);

	bool isHashValid();						          // Block Validator

	int getIndex();							            // Block index getter
	std::size_t getBlockHash();			      	// Block hash getter
	std::size_t getPrevBlockHash();	    		// Previous block hash getter
	TransactionData getTransactionData(); 	// TransactionData getter
};

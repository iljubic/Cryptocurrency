#include "Blockchain.h"
#include <ctime>
#include <vector>
#include <string>


int main() {
	Blockchain bChain;								        // Creating a blockchain
	time_t current;
	bChain.addWallet(time(&current));					// Creating the 1st wallet
	bChain.addWallet(time(&current));					// Creating the 2nd wallet

	
	time_t data0Time;
	TransactionData data0(1, 01, 02, time(&data0Time));	  // 1st Transaction - Configuring

	bChain.addBlock(data0);							// Adding the block with the configured TransactionData to the Blockchain

	return 0;
}

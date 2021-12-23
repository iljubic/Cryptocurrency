#pragma once

#include <string>
#include <Vector>
#include <ctime>
#include <algorithm>
#include "SHA512.h"
#include "RandomNumberGenerator.h"
#include "Signature.h"
#include "Chain.h"
#include "Shard.h"
#include "Block.h"


class TraceableRingSignature {
private:
	// Configurable Data
	int maxNumberOfDecoyAddresses = 19;			// The maximum number of decoy addresses in the signed ring signatures - making this too high will decrease speed when receiver decodes transactions
	int maxNumberOfDecoyShards = 5;				// The maximum number of shards used in the decoy address generation phase - if there is only 1 shard, it will take from that shard
	const int primeModulus = 2147483647;		// Large prime number (max for int type) - used in the Diffie Hellman Exchange
	const int generator = 3;					// Used with the primeModulus to implement the Diffie Hellman Exchange

	// Inputted Data
	double amount;								// The transaction amount - disguised using Diffie Hellman Exchange
	int transactionCounter;						// The number of transactions the wallet has completed
	int validationCounter;						// The number of blocks/transaction that the node linked to this wallet has validated
	std::string privateSenderKey;				// The senders private key - a key component in generation of the secretKey
	std::string publicSenderKey;				// The senders public key - a hash of their private key   + some readily available public data (data must be the same for both sender and receiver)
	std::string publicReceiverKey;				// The receivers public key - a hash of their private key + some readily available public data (data must be the same for both sender and receiver)
	std::time_t timestamp;						// The time the TraceableRingSignature was created

	// Generated Data
	std::vector<std::string> ring;				// The ring - includes the decoys and proper public addresses
	std::string keyImage;						// Key Image - designed to stop clone transactions occuring
	std::string secretKey;						// The key used in the block to disguise the receiver - receiver confirms transaction using a Diffie Hellman exchange
	std::string transactionHash;				// Hashed transaction data - amount, publicSenderKey and the publicReceiverKey

	// Generator Functions
	std::string generateKeyImage();				// Generates the keyImage
	unsigned int generateSecretKey();			// Generates the secretKey
	std::string generateTransactionHash();		// Generates the transaction hash

	// Big decoy key finding function - takes the 4 constants outlined at the top of this class and finds previous public addresses throughout the blockchain
	std::vector<std::string> findDecoyKeys(std::vector<Shard> chain);
public:
	// Constructor, takes in: amount, #ofTransactions, #ofValidations, wallet privateKey, wallet publicKey, receiverKey, time and the blockchain
	TraceableRingSignature(double a, int transactionCount, int validationCount, std::string pK, std::string sK, std::string rK, std::time_t t, Chain chain);
	
	Signature generateSignature();				// Returns a signature created using the data this class made
};

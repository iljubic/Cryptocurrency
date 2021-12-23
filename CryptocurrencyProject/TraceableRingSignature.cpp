#include "TraceableRingSignature.h"


TraceableRingSignature::TraceableRingSignature(double a, int transactionCount, int validationCount, std::string pK, std::string sK, std::string rK, std::time_t t, Chain chain) {
	amount = a;
	transactionCounter = transactionCount;
	validationCounter = validationCount;
	privateSenderKey = pK;
	publicSenderKey = sK;
	publicReceiverKey = rK;
	timestamp = t;

	keyImage = generateKeyImage();
	secretKey = generateSecretKey();
	transactionHash = generateTransactionHash();

	ring = findDecoyKeys(chain.getChain());
}

std::string TraceableRingSignature::generateKeyImage() {
	SHA512 sha;
	std::string input = privateSenderKey + publicSenderKey;
	return sha.hash(input);
}

unsigned int TraceableRingSignature::generateSecretKey() {
	unsigned long long int y;

	y = static_cast<int>(pow(static_cast<double>(stoi(publicReceiverKey)), stoi(privateSenderKey))); // Y^x
	return y % primeModulus;
}

std::string TraceableRingSignature::generateTransactionHash() {
	SHA512 sha;
	std::string input = std::to_string(amount) + publicSenderKey + publicReceiverKey + std::to_string(timestamp);
	return sha.hash(input);
}

// This function finds random publicKeys from the block data in random shards from the chain
std::vector<std::string> TraceableRingSignature::findDecoyKeys(std::vector<Shard> chain) {
	std::vector<int> selectedIndices;
	std::vector<int> selectedIndices1;
	std::vector<Shard> decoyShards;
	std::vector<Block> decoyBlocks;
	std::vector<std::string> decoyKeys;

	// Creating a unique seed by hashing dynamic, private data from the Wallet - generates a unique, untraceable seed
	SHA512 sha;
	std::string input = privateSenderKey + std::to_string(transactionCounter) + std::to_string(validationCounter);
	std::string seedString = sha.hash(input);
	int seed = stoi(seedString);

	// Find the minimum and maximum for the shard chain to find shards to take values from
	int minShard = 1;
	int maxShard = chain.size() - 1;	// Finding the length of the shard chain (with shards that are full) - this is the max value
	int numberOfShards = maxShard - minShard;

	// Selecting the shards
	if (numberOfShards < maxNumberOfDecoyShards) {	// If there are less than the optimum amount of decoy shards, only use what is available
		maxNumberOfDecoyShards = numberOfShards;

		// Making a dynamic array to check for duplicate random numbers
		

		// Must use std::any_of to see if randomNumber is in the array already, if it isnt, push randomNumber back into the array

		// Must make sure we dont get the same shard number multiple times
		for (int i = 0; i < maxNumberOfDecoyShards; i++) {
			// Create a random number between the minimum and maximum values with the seed
			RandomNumberGenerator shardNum(minShard, maxShard, seed);	// Create a RNG object
			int randomNumber = shardNum.getRandomNumber();				// Create a randomNumber int and store the output of the RNG object
			
			// Making sure randomNumber does not exist anywhere in selectedIndices
			while (std::any_of(selectedIndices.begin(), selectedIndices.end(), [randomNumber](int y) {return randomNumber == y; })) {
				shardNum.refreshNumber();
				randomNumber = shardNum.getRandomNumber();
			}

			// Adding random number into the selectedIndices vector
			selectedIndices.push_back(randomNumber);
			// Adding the shard that randomNumber reffers to into the decoyShards vector created at the start of the function
			decoyShards.push_back(chain[randomNumber]);
		}	// Succesfully filled decoyShards with non-duplicate indices
	}
	else {	// If there is enough decoy shards, use the optimal amount
		// Use the random seed to find how many shards to take blocks from
		for (int i = 0; i < maxNumberOfDecoyShards; i++) {
			// Create a random number between the minimum and maximum values with the seed
			RandomNumberGenerator shardNum(minShard, maxShard, seed);	// Create a RNG object
			int randomNumber = shardNum.getRandomNumber();				// Create a randomNumber int and store the output of the RNG object

			while (std::any_of(selectedIndices.begin(), selectedIndices.end(), [randomNumber](int y) {return randomNumber == y; })) {
				shardNum.refreshNumber();
				randomNumber = shardNum.getRandomNumber();
			}

			// Adding random number into the selectedIndices vector
			selectedIndices.push_back(randomNumber);
			// Adding the shard that randomNumber reffers to into the decoyShards vector created at the start of the function
			decoyShards.push_back(chain[randomNumber]);
		}	// Succesfully filled decoyShards with non-duplicate indices
	}

	// Selecting the Blocks
	// Find the minimum and maximum for the shard chain to find shards to take values from
	int blocksPerShard = ceil(maxNumberOfDecoyAddresses / decoyShards.size());	// Round the decimal up (if there is one)

	// If there is less than 20 blocks in existance, fill decoyBlocks with the first blocks available
	if (decoyShards.size() == 1 && decoyShards[0].getChain().size() < maxNumberOfDecoyAddresses) {
		for (int i = 0; i < decoyShards[0].getChain().size(); i++) {
			decoyBlocks.push_back(decoyShards[i].getBlock(i));
		}
	}
	else {		// If there is enough blocks, use the optimal amount
		for (int i = 0; i < decoyShards.size() * blocksPerShard; i++) {
			RandomNumberGenerator blockNum(0, 100, seed);
			int randomNumber = blockNum.getRandomNumber();

			while (std::any_of(selectedIndices1.begin(), selectedIndices1.end(), [randomNumber](int y) {return randomNumber == y; })) {
				blockNum.refreshNumber();
				randomNumber = blockNum.getRandomNumber();
			}

			selectedIndices1.push_back(randomNumber);
			decoyBlocks.push_back(decoyShards[i].getBlock(randomNumber));
		}
	}
	
	// Taking the publicAddresses from those blocks and adding them to the output
	for (int i = 0; i < maxNumberOfDecoyAddresses; i++) {
		RandomNumberGenerator rng(0, 19, seed);
		int signatureIndex = rng.getRandomNumber();

		ring[i] = decoyBlocks[i].getSignature().ring[signatureIndex];
	}
	
	// Add the actual publicKey/Address somewhere random in the ring
	RandomNumberGenerator rng(0, ring.size(), seed);
	int position = rng.getRandomNumber();
	ring.insert(position, publicReceiverKey);

	// Return the array/vector
	return ring;
}

Signature TraceableRingSignature::generateSignature() {
	Signature newSignature(ring, transactionHash, secretKey, keyImage);
	return newSignature;
}

#include "Wallet.h"


Wallet::Wallet(int i, time_t t, std::size_t pAH)
{
	index = i;
	prevAddressHash = pAH;
	birthTime = t;

	addressHash = generateAddressHash();
}

std::size_t Wallet::generateAddressHash()
{
	// Creating hashes to be added into the finalHash
	std::hash<std::string> hash1;
	std::hash<std::size_t> hash2;
	std::hash<std::size_t> finalHash;
	std::string toHash =
		std::to_string(index) +
		std::to_string(birthTime);

	return finalHash(hash1(toHash) + hash2(prevAddressHash));	// Combining all data into one hash and returning it
}

bool Wallet::isHashValid() {
	return generateAddressHash() == addressHash;	// Returns true if the generateAddressHash() output is the same as the addressHash
}


// Getters
int Wallet::getIndex() {
	return index;
}

std::size_t Wallet::getAddressHash()
{
	return addressHash;
}

std::size_t Wallet::getPrevAddressHash()
{
	return prevAddressHash;
}

time_t Wallet::getBirthTime() {
	return birthTime;
}

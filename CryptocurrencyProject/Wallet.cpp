#include "Wallet.h"


Wallet::Wallet(time_t t, std::string user, std::string pass) {

}

void Wallet::generatePrivateKey() {	// Private Key is generated from password, timestamp and username
	SHA512 sha;
	privateKey = sha.hash(username + password + std::to_string(timestamp));
}

void Wallet::generatePublicKey() {	// Public Key is generated from the private key combined with readily available public data on the Blockchain
	unsigned long long int x;
	
	x = static_cast<int>(pow(static_cast<double>(generator), stoi(privateKey))); // generator^privateKey
	publicKey = x % primeModulus;
}

void Wallet::sendTransaction(double amount, std::size_t receiverAddress) {


	transactionCounter++;
}

int Wallet::getTransactionCounter() {
	return transactionCounter;
}

int Wallet::getValidationCounter() {
	return validationCounter;
}

std::string Wallet::getPublicKey() {
	return publicKey;
}

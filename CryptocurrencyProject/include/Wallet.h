#pragma once

#include "Blockchain.h"
#include <ctime>
#include <vector>
#include <string>


class Wallet {								          // Wallet Class
private:
	int index;							             	// Keeps count of the wallets index in the blockchain

	std::size_t addressHash;				      // The address hash
	std::size_t prevAddressHash;			    // The previous address hash
	time_t birthTime;					           	// The time the address was created
	int balance;							            // The balance in the address

	std::size_t generateAddressHash();	  // Address Hash Generator
public:
	Wallet(int i, time_t t, std::size_t pAH);
	
	bool isHashValid();					         	// Wallet Validator

	int getIndex();						          	// Gets the wallet index
	std::size_t getAddressHash();		    	// Gets the address hash
	std::size_t getPrevAddressHash();	  	// Gets the previous address hash
	time_t getBirthTime();			      		// Gets the time the wallet was created
};

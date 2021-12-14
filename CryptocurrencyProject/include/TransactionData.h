#pragma once

#include <ctime>
#include <vector>


struct TransactionData {		  	// TransactionData Structure

	double amount;			      		// The amount sent from the sender to the receiver
	std::size_t receiverAddress;	// The receiver address hash
	std::size_t senderAddress;		// The sender address hash
	time_t timestamp;				      // The time the transaction/block was made

	TransactionData(double a, std::size_t rA, std::size_t sA, time_t tS) {
		amount = a;
		receiverAddress = rA;
		senderAddress = sA;
		timestamp = tS;
	};
};

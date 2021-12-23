#pragma once

#include <string>
#include <vector>


struct Signature {
	std::vector<std::string> ring;		// The ring - includes the decoys and proper public addresses
	std::string transactionData;		// Hashed transaction data - amount, publicSenderKey and the publicReceiverKey
	std::string secretKey;				// The receivers secret key
	std::string keyImage;				// Key Image - designed to stop clone transactions occuring

	Signature() {};

	Signature(std::vector<std::string> r, std::string tD, std::string sK, std::string kI) {
		ring = r;
		transactionData = tD;
		secretKey = sK;
		keyImage = kI;
	};
};

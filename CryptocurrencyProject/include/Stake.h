#pragma once


class Stake {
public:
	double stakingYieldPercentage;	// A value from 0-1 (basically a percentage return) - this value is dynamic based upon if the network needs stakers or doesnt
	double stakingPeriod;			// The time the tokens must be staked to receive a reward

	Stake();
};

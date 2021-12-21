# Week 1 Update: #
Some of the things that have been implemented (this stuff will all be uploaded before 23/12/2021):
* A working ring signature system!
* A Diffie-Hellman Key Exchange system to complement the ring signatures!
* The start of a working sharding system (the ring signature generator function had to be specially designed for the sharding system).
* Fully fledged wallet system with usernames and passwords!!!!

## TLDR / What this all means ##
The ring signatures and Diffie-Hellman Key Exchanges allow for completely private transactions* - the sender and receiver address/key and the transaction amounts are masked (like Monero). <br>

The sharding system allows for new wallets to not have to download the entire blockchain, instead only having to download the 5 most recent shards minimum (1000 blocks/transactions to be downloaded maximum).

The wallet usernames and passwords make it into a proper currency - you lose your username and password, you no longer have access to the crypto in that account!

## Future Additions ##
Over the next week:
* The sharding system is getting finalised
* The wallet class will be able to read the shardchain and blockchain and find any blocks/transactions that contain it as the recipient.
* The node class will be started and allow for people to stake their cryptocurrency
In the near future (over a week):
* A fully fledged staking system (minimum staking amount - all staked currency will be burnt if node validates false transactions - increasing the value of the cryptocurrency)
* A proper networking system to allow for proper peer-to-peer transactions over the internet (not just local transactions on one machine)
In the further future (over a month):
* A fully fledged wallet GUI system (cross platform - shouldnt be too hard as I have decent cross platform experience)

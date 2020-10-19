# DSFinalProject
Blockchain is a public ledger that can be used to store transactions and to ensure that these transactions are not tampered with. Our blockchain used two major components:
1. A transaction class that could represent all of the data of a given transaction, hash itself, and provide its date
2. A Merkle Tree class that links transaction classes together with hash pointers and inserts transactions into the tree based on their date 

## Implementing Blockchain With a Transaction Class
### Transaction class members: 
- The receiver of the money
- The sender of the money
- The amount of money
- The date of the transaction

An example of a transaction class object would be
'''
Receiver: Obi-Wan Kenobi
Sender: Luke Skywalker
Amount: $87.55
Date: 03/23/2019
'''

Throughout this whole process, hashing is an important element to ensure that the transaction history has not been tampered with after its publication in the ledger of blockchain. All of these elements come together to make one big public ledger that ensures secure transactions between different parties over the internet. 

Although there are many different ways to implement blockchain, some implementations are unnecessarily complex. The Merkle tree blockchain data structure is a simple solution to this.

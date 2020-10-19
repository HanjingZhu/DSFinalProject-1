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

## Cryptographic Hash Functions
A cryptographic hash function is an important component of blockchain technology. A hash function takes in a string and encrypts it to an encrypted string of a fixed length。
The cryptographic hash function we used here is **SHA-256** and we used this [unofficial C++ Implementation](https://gist.github.com/hak8or/8794351) for reference.
### Hash Function Implementation
* Test 1 *
Initial input string:  
SHA-256 Hashed string: 36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068

* Test 2 *
Initial input string: Hello!
SHA-256 Hashed string: 21c7a26677ef355f0af8b2958beaf352845633070902554c1a2d10728cba0986

* Test 3 *
Initial input string: Receiver: Obi-Wan Kenobi!
SHA-256 Hashed string: 79ac3b649cc3e0fe135953080021105ca5c2000c9d82809f74b503d8ceaed7d6

* Test 4 *
Initial input string: Obi-Wan Kenobi! Luke Skywalker $44.56 5/4/2020
SHA-256 Hashed string: 1d054e8658033d87c4f1e2f51e319d9254b7554739998b136370c4f87701e413

## Merkle Tree Blockchain


Throughout this whole process, hashing is an important element to ensure that the transaction history has not been tampered with after its publication in the ledger of blockchain. All of these elements come together to make one big public ledger that ensures secure transactions between different parties over the internet. 

Although there are many different ways to implement blockchain, some implementations are unnecessarily complex. The Merkle tree blockchain data structure is a simple solution to this.

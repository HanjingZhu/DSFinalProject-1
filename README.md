# Data Structures Final Project - Bloackchain Implementation in C++
##### by Bridget Goodwine, Hanjing Zhu
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
*Test 1*

**Initial input string:**  

**SHA-256 Hashed string:** 36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068

*Test 2*

**Initial input string:** Hello!

**SHA-256 Hashed string:** 21c7a26677ef355f0af8b2958beaf352845633070902554c1a2d10728cba0986

*Test 3*

**Initial input string:** Receiver: Obi-Wan Kenobi!

**SHA-256 Hashed string:** 79ac3b649cc3e0fe135953080021105ca5c2000c9d82809f74b503d8ceaed7d6

*Test 4*

**Initial input string:** Obi-Wan Kenobi! Luke Skywalker $44.56 5/4/2020

**SHA-256 Hashed string:** 1d054e8658033d87c4f1e2f51e319d9254b7554739998b136370c4f87701e413

## Merkle Tree Blockchain
Each node in the tree contains the hashes of its children.
### Merkle Tree Node Struct
So each node in the Merkle Tree contains:
1. A templated value, which will be the transaction class itself
2. Left and right pointers to its children
3. Left and right hashes of its children
4. A timestamp, which we can get with the getDate() method in the transaction class

![Merkle Tree Node](https://github.com/HanjingZhu/DSFinalProject-1/blob/master/Merkle%20Tree%20Node.png)

### Merkle Tree Class
Each node in the merkle tree is a merkle node struct. The insertion method for this merkle tree is the same as a binary search tree’s insertion method, but instead of the value being compared, it is the timestamp that is compared. Therefore, we can print the blockchain in chronological order by using a print in order algorithm.
![Merkle Tree with Merkle Nodes](https://github.com/HanjingZhu/DSFinalProject-1/blob/master/Merkle%20Tree.png)

So when we insert our transaction, it will be inserted into a tree like the graph above. The insert function will compare its timestamp to all the timestamps in the tree, and recurse down to the end spot where it should be. When it is inserted, the parent transaction will point to it, and the parent left or right hash will be modified to be a hash of the transaction that we inserted. 

## Conclusion
Throughout this whole process, hashing is an important element to ensure that the transaction history has not been tampered with after its publication in the ledger of blockchain. All of these elements come together to make one big public ledger that ensures secure transactions between different parties over the internet. 

Although there are many different ways to implement blockchain, some implementations are unnecessarily complex. For example, each node in the doubly linked list would contain a type of Merkle Tree, which would have many different transactions inside of it. This approach involves layers of data structures. Whereas the Merkle tree blockchain data structure is a simple solution to this. Three main benefits of Merkle Trees in blockchain are:
1. Easy to check if transactions have been tampered with
2. Uses fewer resources
3. Easy to verify if a specific transaction has been added to the block

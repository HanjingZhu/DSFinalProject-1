#include "Transaction.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>



/******
* Function: resize_block
* Resize the blocks from 64 8 bit sections to 16 32 bit sections
* Input: Vector of inidividual 8 bit ascii values
* Output: Vector of 32 bit words which are combined ascii values
*******/
std::vector<unsigned long> resize_block (std::vector<unsigned long> input){
    std::vector<unsigned long> output(16);
    // loop through the 64 sections by 4 steps and merge those 4 sections
    for (int i = 0; i < 64; i += 4){
        std::bitset<32> temp(0);
        // shift the blocks to their assigned spots and OR them with the original
        temp = (unsigned long) input[i] << 24;
        temp |= (unsigned long) input[i + 1] << 16;
        temp |= (unsigned long) input[i + 2] << 8;
        temp |= (unsigned long) input[i + 3];
        // puts the new 32 bit word into the correct output array location
        output[i/4] = temp.to_ulong();
    }
    return output;
}

/** Function: show_as_hex
* Shows the current contents of the block in hex
* Input: A 32 or less bit block
* Output: Contents of the block in hex as a string
**/
std::string show_as_hex(unsigned long input){
    std::bitset<32> bs(input);
    unsigned long n = bs.to_ulong();

    std::stringstream sstream;
    sstream << std::hex << std::setw(8) << std::setfill('0') << n;
    std::string temp;
    sstream >> temp;

    return temp;
}

/** Function: show_as_binary
* Shows the current contents of the block in hex
* Input: A 32 or less bit block
* Output: Contents of the block in binary as a string
***/
std::string show_as_binary(unsigned long input){
    std::bitset<8> bs(input);
	return bs.to_string();
}

/*** Function: convert_to_binary
* Takes the string and coverts all characters to their ASCII Binary equivilents
* Input: A string of any length
* Output: A vector consisting of one 8 bit value per ASCII character
****/
std::vector<unsigned long> convert_to_binary(const std::string input){
    std::vector<unsigned long> block;
    // for each character, convert the ASCII character to its binary representation.
    for (unsigned int i = 0; i < input.size(); ++i){
        std::bitset<8> b(input.c_str()[i]);
        block.push_back(b.to_ulong());
    }
    return block;
}

/**** Function: pad_to_512bits
* Takes the vector of ASCII values in binary and pad it, to get a total of 512 bits
* Input: Message in the form of a vector containing 8 bit binary ASCII values
* Output: A padded vector consisting of one 8 bit value per ASCII characters
****/
std::vector<unsigned long> pad_to_512bits(std::vector<unsigned long>block){
    // the length of the message in terms of bit
    unsigned long l = block.size() * 8;
    unsigned long k = 447 - l;
    unsigned long t1 = 0x80;
    block.push_back(t1);
    k = k - 7;
    for (unsigned long i = 0; i < k / 8; i++){
        block.push_back(0x00000000);
    }
    // add l in the binary form of eight 8 bit blocks
    std::bitset<64> big_64bit_blob(l);

    // split up that 64 bit blob into 8 bit sections.
    std::string big_64bit_string = big_64bit_blob.to_string();

    // Push the first block into the 56th position.
	std::bitset<8> temp_string_holder1(big_64bit_string.substr(0,8));
	block.push_back(temp_string_holder1.to_ulong());


	// Push all the rest of the 8 bit blocks in.
	for(int i = 8; i < 63; i=i+8)
	{
		std::bitset<8> temp_string_holder2(big_64bit_string.substr(i,8));
		block.push_back(temp_string_holder2.to_ulong());
	}
    return block;
}
// Taken from NIST spec. I find it amazing how this can all be done by just
// bit rotations.
// code from gitHub: https://gist.github.com/hak8or/8794351
  #define ROTRIGHT(word,bits) (((word) >> (bits)) | ((word) << (32-(bits))))
  #define SSIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
  #define SSIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
  #define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
  #define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
  #define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
  #define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
// hash function

std::string hash_compute(const std::vector<unsigned long> block){
    unsigned long k[64] = {
      0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
      0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
      0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
      0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
      0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
      0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
      0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
      0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
      0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
      0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
      0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
  };

  // initial hash values, first 32 bits of the fractional parts of
  // the square roots of the first eight prime numbers
  unsigned long static H0 = 0x6a09e667;
	unsigned long static H1 = 0xbb67ae85;
	unsigned long static H2 = 0x3c6ef372;
	unsigned long static H3 = 0xa54ff53a;
	unsigned long static H4 = 0x510e527f;
	unsigned long static H5 = 0x9b05688c;
	unsigned long static H6 = 0x1f83d9ab;
	unsigned long static H7 = 0x5be0cd19;

	unsigned long W[64];

	for(int t = 0; t <= 15; t++)
	{
		W[t] = block[t] & 0xFFFFFFFF;
	}

	for(int t = 16; t <= 63; t++)
	{
		// Also taken from spec.
		W[t] = SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];

		// Have to make sure we are still dealing with 32 bit numbers.
		W[t] = W[t] & 0xFFFFFFFF;
	}

	unsigned long temp1;
	unsigned long temp2;
	unsigned long a = H0;
	unsigned long b = H1;
	unsigned long c = H2;
	unsigned long d = H3;
	unsigned long e = H4;
	unsigned long f = H5;
	unsigned long g = H6;
	unsigned long h = H7;

	for( int t = 0; t < 64; t++)
	{
		// Seems the Official spec is wrong!? BSIG1 is incorrect.
		// Replacing BSIG1 with EP1.
		temp1 = h + EP1(e) + CH(e,f,g) + k[t] + W[t];

		// Seems the Official spec is wrong!? BSIG0 is incorrect.
		// Replacing BSIG0 with EP0.
		temp2 = EP0(a) + MAJ(a,b,c);

		// Do the working variables operations as per NIST.
		h = g;
		g = f;
		f = e;
		e = (d + temp1) & 0xFFFFFFFF; // Makes sure that we are still using 32 bits.
		d = c;
		c = b;
		b = a;
		a = (temp1 + temp2) & 0xFFFFFFFF; // Makes sure that we are still using 32 bits.
	}



	// Add up all the working variables to each hash and make sure we are still
	// working with solely 32 bit variables.
	H0 = (H0 + a) & 0xFFFFFFFF;
	H1 = (H1 + b) & 0xFFFFFFFF;
	H2 = (H2 + c) & 0xFFFFFFFF;
	H3 = (H3 + d) & 0xFFFFFFFF;
	H4 = (H4 + e) & 0xFFFFFFFF;
	H5 = (H5 + f) & 0xFFFFFFFF;
	H6 = (H6 + g) & 0xFFFFFFFF;
	H7 = (H7 + h) & 0xFFFFFFFF;

	// Append the hash segments together one after the other to get the full
	// 256 bit hash.
	return show_as_hex(H0) + show_as_hex(H1) + show_as_hex(H2) +
		   show_as_hex(H3) + show_as_hex(H4) + show_as_hex(H5) +
		   show_as_hex(H6) + show_as_hex(H7);
}

std::string hash (std::string message){
    std::vector<unsigned long> block;
    block = convert_to_binary(message);
    block = pad_to_512bits(block);
    block = resize_block(block);
    std::string result = hash_compute(block);
    return result;
}

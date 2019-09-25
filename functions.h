/*
 * functions.h
 *
 *  Created on: 25 сент. 2019 г.
 *      Author: alab
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "ecc.h"
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include "libbase58.h"
#include <string.h>
#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#define PUBLICKEYSIZE 33
#define PRIVATEKEYSIZE 32
#define BASE58WIFSIZE 38
#define SCRIPTHASHCONTARTSIZE 20
#define ACCOUNTMAXLENGTH 35
#define SHA256HASHSIZE 32
#define RIDEMD160HASHSIZE 20
bool SHA256_ossl(void* input, unsigned long length, unsigned char* md);
bool RIPEMD160_ossl(void* input, unsigned long length, unsigned char* md);
char *bin2hex(const unsigned char *bin, size_t len);
using namespace std;
/* neo account full information */
struct account
{
	string WIF;//Wallet Import Format
	std::array<uint8_t,PRIVATEKEYSIZE> privateKey;//private key;
	std::array<uint8_t,PUBLICKEYSIZE> publicKey;//public key;
	string account;//address
};

/* unspent transaction output */
struct UTXO
{
	string hash;//TX hash
	unsigned char position;//pos in TX
	unsigned long long amount;//amount in this UTXO
	std::array<uint8_t,PRIVATEKEYSIZE> privateKey;//private key for sign transaction
};

account accountByWIF( std::string wif);

#endif /* FUNCTIONS_H_ */

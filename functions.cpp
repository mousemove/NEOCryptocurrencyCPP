#include "functions.h"


char *bin2hex(const unsigned char *bin, size_t len)
{
    char   *out;
    size_t  i;

    if (bin == NULL || len == 0)
        return NULL;

    out = (char *)malloc(len*2+1);
    for (i=0; i<len; i++) {
        out[i*2]   = "0123456789abcdef"[bin[i] >> 4];
        out[i*2+1] = "0123456789abcdef"[bin[i] & 0x0F];
    }
    out[len*2] = '\0';

    return out;
}

bool SHA256_ossl(void* input, unsigned long length, unsigned char* md)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;

    return true;
}

bool RIPEMD160_ossl(void* input, unsigned long length, unsigned char* md)
{
    RIPEMD160_CTX context;
    if(! RIPEMD160_Init(&context))
        return false;

    if(! RIPEMD160_Update(&context, (unsigned char*)input, length))
        return false;

    if(! RIPEMD160_Final(md, &context))
        return false;

    return true;
}


account accountByWIF( std::string WIF)
{
	account result;
    std::array<uint8_t,PUBLICKEYSIZE> pub;
    uint8_t forencode[BASE58WIFSIZE];
    size_t s = BASE58WIFSIZE;
    b58tobin(forencode,&s,WIF.c_str(),WIF.size());
    std::array<uint8_t,PRIVATEKEYSIZE> pk; //private key bytes form in std::array
    memcpy(pk.data(),forencode+1,PRIVATEKEYSIZE);
    ecc_generate_public(pub.data(),pk.data());//generate public key with secp256r1
    //Build the address script contract
    std::vector<uint8_t> suppPublicKey;//Supplemented private key(scrpit hash contract)
    suppPublicKey.push_back(0x21);
    for(unsigned long i=0; i<PUBLICKEYSIZE; i++)
    {
        suppPublicKey.push_back(pub[i]);
    }
    suppPublicKey.push_back(0xac);
    //Calculate script hash of the contract (20 bytes, make once SHA256 and RIPEMD160 of the script).
    std::array<uint8_t,SHA256HASHSIZE> sha256spubkey;//sha256(supplemented public key)
    std::array<uint8_t,RIDEMD160HASHSIZE> scripthashcontract;//ripemd160(sha256(supplemented public key)
    SHA256_ossl(suppPublicKey.data(),suppPublicKey.size(),sha256spubkey.data());
    RIPEMD160_ossl(sha256spubkey.data(),sha256spubkey.size(),scripthashcontract.data());
    std::vector<uint8_t> supScriptHashContract;
    //Add the version prefix in the hash. (Currently, the NEO version is 0x17)
    supScriptHashContract.push_back(0x17);
    for(unsigned long i=0; i<SCRIPTHASHCONTARTSIZE; i++)
    {
        supScriptHashContract.push_back(scripthashcontract[i]);
    }
    //take the 20 first bytes -> sha256(sha256(this))
    std::array<uint8_t,SHA256HASHSIZE> sha256added;
    std::array<uint8_t,SHA256HASHSIZE> sh256x2added;
    SHA256_ossl(supScriptHashContract.data(),supScriptHashContract.size(),sha256added.data());
    SHA256_ossl(sha256added.data(),sha256added.size(),sh256x2added.data());
    //add for first bytes
    supScriptHashContract.push_back(sh256x2added[0]);
    supScriptHashContract.push_back(sh256x2added[1]);
    supScriptHashContract.push_back(sh256x2added[2]);
    supScriptHashContract.push_back(sh256x2added[3]);
    //base58 encode this -> neo account(wallet)
    char  account[ACCOUNTMAXLENGTH];
    size_t size = ACCOUNTMAXLENGTH;
    b58enc(account,&size,supScriptHashContract.data(),supScriptHashContract.size());
    result.WIF = WIF;
    result.account = string(account);
    result.privateKey = pk;
    result.publicKey = pub;
    return result;
}

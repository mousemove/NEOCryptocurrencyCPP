//============================================================================
// Name        : NEO.cpp
// Author      : Alab
// Version     :
// Copyright   : (c) github.com/mousemove
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "functions.h"
using namespace std;

int main() {
	account acc = accountByWIF("L3cmx16HBswAnUXWrHMaYkCgX3HQWDTWVQvZuzyy6fz1JuyX43ab");
	cout << "WIF: " << acc.WIF << endl;
	cout << "Account(Address): " << acc.account << endl;
	cout << "Private Key(HEX): " <<  bin2hex(acc.privateKey.data(),PUBLICKEYSIZE) << endl;
	cout << "Public  Key(HEX): " << bin2hex(acc.publicKey.data(),PRIVATEKEYSIZE)<< endl;
	return 0;
}

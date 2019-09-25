Functions for work with cryptocurrency neo(https://neo.org/). Written in CPP

I did not find a repository on working with NEO cryptocurrency on GitHub.Com coded with C / C ++, so I decided to create my own. Previously, it was all implemented using Qt+libbitcoin, now you need to rewrite the code under STD. Here we go;)


Now u can use function accountByWIF(std::string wif) for take account data, example:


	account acc = accountByWIF("L3cmx16HBswAnUXWrHMaYkCgX3HQWDTWVQvZuzyy6fz1JuyX43ab");
	cout << "WIF: " << acc.WIF << endl;
	cout << "Account(Address): " << acc.account << endl;
	cout << "Private Key(HEX): " <<  bin2hex(acc.privateKey.data(),PUBLICKEYSIZE) << endl;
	cout << "Public  Key(HEX): " << bin2hex(acc.publicKey.data(),PRIVATEKEYSIZE)<< endl;
	
	
=>

WIF: L3cmx16HBswAnUXWrHMaYkCgX3HQWDTWVQvZuzyy6fz1JuyX43ab

Account(Address): AHxxenhDfxKhAnD4nwyxbCWJ9s5BTN2sAe

Private Key(HEX): bee3cc9b8862bd65d79328388cb17d27ead37c7a0aa8033ef5adcea2270bed9703

Public  Key(HEX): 03df247ad026b09852f6cf5c2f9bdbb824d91564feafb2315271ee88544ca079


project need lib crypto and lib ssl for linking

Borrowed files from another repositories:
ecc.h/ecc.c(i add only ecc_generate_public function)
base58 - I used Satoshi Nakamoti base58 function https://github.com/bitcoin/libbase58

If my repo helped u => AasGRB9KauLBr7UtmNf984k5eqj5TVioCH ;-)


ToDo(When will I have free time for this):

+ Make and Sign transactions
+ Claim gas
+ Neoscan.io integration for get UTXO data/Nodes/Balance



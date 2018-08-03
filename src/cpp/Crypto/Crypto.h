//
// Created by Mac McCann on 8/2/18.
//

#ifndef STONEFALL_CRYPTO_H
#define STONEFALL_CRYPTO_H

#include <string>
#include "sodium.h"

using namespace std;

class Crypto {
public:
    string randomId() {
        uint32_t myInt;
        myInt = randombytes_uniform(999999999);
        return to_string(myInt);
    }

    string randomSecret() {
        return randomId();
    }
};


#endif //STONEFALL_CRYPTO_H

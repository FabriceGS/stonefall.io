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
        char id[17];
        randombytes_buf(id, 16);
        id[16] = '\0';
        return id;
    }

    string randomSecret() {
        return randomId();
    }
};


#endif //STONEFALL_CRYPTO_H

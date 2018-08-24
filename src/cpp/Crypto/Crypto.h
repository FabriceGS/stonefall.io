//
// Created by Mac McCann on 8/2/18.
//

#ifndef STONEFALL_CRYPTO_H
#define STONEFALL_CRYPTO_H

#include <string>
#include "sodium.h"

using namespace std;

class Crypto {
private:
    static int currentId;
public:
    static string id();
    static string randomSecret();
};

#endif //STONEFALL_CRYPTO_H

#include "Crypto/Crypto.h"
#include "sodium.h"

string Crypto::id() {
    currentId++;
    return to_string(currentId);
}

string Crypto::randomSecret() {
    uint32_t myInt;
    myInt = randombytes_uniform(999999999);
    return to_string(myInt);
}

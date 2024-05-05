#include "hash_functions.h"

size_t polynomial_rolling_hash::operator() (std::string const & str) const {
    ulong hash = 0;
    ulong p = 1;
    ulong b = 19;
    ulong m = 3298534883309ul;

    for (auto i = str.begin(); i != str.end(); i++){
        hash += *i * p;
        p = (p * b) % m;
    }
    return hash;
}

size_t fnv1a_hash::operator() (std::string const & str) const {
    ulong prime = 0x00000100000001B3;
    ulong hash = 0xCBF29CE484222325;
    for (auto i = str.begin(); i != str.end(); i++){
        hash = hash ^ *i;
        hash *= prime;
    }
    return hash;
}

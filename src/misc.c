#include "misc.h"



#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME  1099511628211UL


/* Definition of prime number functions */

/*! @function
 @param     n   number to test
 @return    ture if is prime, false if is not prime
*/
bool IsPrime(size_t n)
{
    if((n & 1) != 0) {
        for(size_t divisor = 3; divisor <= n / divisor; divisor += 2) {
            if((n % divisor) == 0) {
                return 0;
            }
        }
        return 1;
    }
    return (n == 2);
}

/*! @function
 @param     n   number to get next higher prime from
 @return    next higher prime from n
*/
size_t GetHigherPrime(size_t n) {
    for(size_t i = (n | 1); i < LONG_MAX; i += 2) {
        if(IsPrime(i)) {
            return i;
        }
    }
    return n;
}

/*! @function
 @param     n   number to get next lower prime from
 @return    next lower prime from n
*/
size_t GetLowerPrime(size_t n) {
    for(size_t i = (n | 1); i < LONG_MAX; i -= 2) {
        if(IsPrime(i)) {
            return i;
        }
    }

    return n;
}


/* hashing functions */

/*! @function
 @param str null terminated character string to hash
 @return hash in form of size_t
*/
size_t fnv_hash_string(const char *str)
{
    size_t hash;
    int i;
    for(i = 0, hash = FNV_OFFSET; *str != '\0'; str++, i++) {
        hash = hash ^ *str;
        hash = hash * FNV_PRIME;
    }

    return hash;
}

/*! @function
 @param data unsigned byte array
 @param size size of byte array
 @return hash in form of size_t
*/
size_t fnv_hash(unsigned char *data, size_t size)
{
    size_t hash;
    int i;
    for(i = 0, hash = FNV_OFFSET; size != 0; size--, i++) {
        hash = hash ^ *data;
        hash = hash * FNV_PRIME;
    }
    return hash;
}

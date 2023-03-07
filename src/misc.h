// (c) 2023 Florian Giest
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef _HASHDB_MISC_H
#define _HASHDB_MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/* definitions */
#define HASHDB_DEFAULT_CAPACITY 7       /* prime number */
#define HASHDB_DEFAULT_LOADFACTOR 0.75  /*  */

/*! @function
 @param     n   number to test if prime
 @return    true if prime, false if not
*/
bool IsPrime(size_t n);

/*! @function
 @param     n   number to get next bigger prime
 @return    next bigger prime number
*/
size_t GetHigherPrime(size_t n);

/*! @function
 @param     n   number to get next bigger prime
 @return    next lower prime number
*/
size_t GetLowerPrime(size_t n);

/*! @function
 @param     str     string to hash fnv hash
 @return    fnv hash
*/
size_t fnv_hash_string(const char *str);

/*! @function
 @param     data    data to hash
 @param     size    size of data to hash
 @return    fnv hash
*/
size_t fnv_hash(unsigned char *data, size_t size);

#endif
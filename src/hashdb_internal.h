#ifndef _HASHDB_INTERNAL_H
#define _HASHBD_INTERNAL_H

#include "misc.h"

/* get index by this ... formular */
#define hash_probe(hash, i, cap) ((hash + (-1) * (i * i + 1) * (i / 2) * (i / 2)) % cap)

/* simple bucket that holds an pointer key as string and pointer to value */
typedef struct bucket {
    const char *key;
    void *value;
} bucket;

/* hashdb holding capacity (number of elements), n (number of elements inside), map (memory location of entries) */
typedef struct hashmap {
    size_t cap;
    size_t n;
    bucket *map;
} hashdb;

int hashdb_insert(bucket *list, size_t capacity, const char *key, void *value);
bucket* hashdb_return(bucket *list, size_t capacity, const char *key);
void hashdb_rehash(bucket *old_list, size_t old_cap, bucket *new_list, size_t new_cap);
int hashdb_realloc(hashdb *hm, size_t new_cap);
int hashdb_grow(hashdb *hm);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#include "hashdb_internal.h"

#define hashdb_DEFAULT_CAP 7



hashdb* hashdb_create()
{
    hashdb *hm = calloc(1, sizeof *hm);
    if(hm == NULL) {
        return NULL;
    }

    hm->cap = hashdb_DEFAULT_CAP;

    hm->map = calloc(hm->cap, sizeof *hm->map);
    if(hm->map == NULL) {
        free(hm);
        return NULL;
    }

    return hm;
}

void hashdb_destroy(hashdb *hm)
{
    free(hm->map);
    free(hm);
}


int hashdb_add(hashdb *hm, const char *key, void *value)
{
    if(hm->n == hm->cap) {
        return -1; /* full, should not happen */
    }

    /* check if it should grow */
    if(hashdb_grow(hm) != 0) {
        return ENOMEM;
    }

    if(hashdb_insert(hm->map, hm->cap, key, value)) {
        return -1; /* internal error */
    }

    hm->n++;

    return 0;
}

void* hashdb_get(hashdb *hm, const char *key)
{
    bucket *item = hashdb_return(hm->map, hm->cap, key);
    if(item == NULL) {
        return item; /* not found */
    }

    return item->value;
}


int hashdb_ensure_capacity(hashdb *hm, size_t new_capacity)
{

    size_t new_cap = GetHigherPrime(new_capacity);
    if(hashdb_realloc(hm, new_cap) != 0) {
        return ENOMEM;
    }

    return 0;
}



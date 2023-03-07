// (c) 2023 Florian Giest
// This code is licensed under MIT license (see LICENSE.txt for details)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#include "hashdb_internal.h"

#define hashdb_DEFAULT_CAP 7

/*! @function
 @return hashdb pointer
*/
hashdb* hashdb_create()
{
    hashdb *db = calloc(1, sizeof *db);
    if(db == NULL) {
        return NULL;
    }

    db->cap = hashdb_DEFAULT_CAP;

    db->map = calloc(db->cap, sizeof *db->map);
    if(db->map == NULL) {
        free(db);
        return NULL;
    }

    return db;
}
/*! @function
 @param db  hashdb pointer to destroy
*/
void hashdb_destroy(hashdb *db)
{
    free(db->map);
    free(db);
}

/*! @function
 @param db      hashdb pointer
 @param key     key
 @param value   value associated with key
 @return        0 on success, ENOMEM on failure
*/
int hashdb_add(hashdb *db, const char *key, void *value)
{
    if(db->n == db->cap) {
        return -1; /* full, should not happen */
    }

    /* check if it should grow */
    if(hashdb_grow(db) != 0) {
        return ENOMEM;
    }

    if(hashdb_insert(db->map, db->cap, key, value)) {
        return -1; /* internal error */
    }

    db->n++;

    return 0;
}

/*! @function
 @param db      hashdb pointer
 @param key     key to retrieve date from
 @return        data associated with key
*/
void* hashdb_get(hashdb *db, const char *key)
{
    bucket *item = hashdb_return(db->map, db->cap, key);
    if(item == NULL) {
        return item; /* not found */
    }

    return item->value;
}

/*! @function
 @param db              hashdb pointer
 @param new_capacity    new number of elements
 @return                0 on succes, ENOMEM on failure
*/
int hashdb_ensure_capacity(hashdb *db, size_t new_capacity)
{

    size_t new_cap = GetHigherPrime(new_capacity);
    if(hashdb_realloc(db, new_cap) != 0) {
        return ENOMEM;
    }

    return 0;
}



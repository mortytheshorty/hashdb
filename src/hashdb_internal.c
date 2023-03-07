// (c) 2023 Florian Giest
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "hashdb_internal.h"

/*! @function
 @param list        pointer to bucket list
 @param capacity    capacity of bucket list
 @param key         key to store
 @param value       value to store by key
 @return            0 if succes, -1 if failure 
*/
int hashdb_insert(bucket *list, size_t capacity, const char *key, void *value)
{
    size_t i = 0;
    size_t hash = fnv_hash_string(key);
    size_t probe = 0;

    /* starting at 1 because 1 and 0 would get the same probe so we can safe that step */
    for(i = 1; i <= capacity; i++) {
        probe = hash_probe(hash, i, capacity);
        if(list[probe].key == NULL)
        {
            list[probe].key = key;
            list[probe].value = value;
            return 0;
        }
    }

    return -1;    
}


/*! @function
 @param     list        pointer to list to return from
 @param     capacity    capacity of list
 @param     key         key to get data from
 @return    location of bucket   
*/
bucket* hashdb_return(bucket *list, size_t capacity, const char *key)
{

    size_t i = 0;
    size_t probe = 0;
    size_t hash = fnv_hash_string(key);

    for(i = 1; i <= capacity; i++) {
        probe = hash_probe(hash, i, capacity);
        if(list[probe].key != NULL) {
            if(strcmp(key, list[probe].key) == 0) {
                return &list[probe];
            }
        }
    }
    
    return NULL;
}

/*! @function
 @param old_list    old list with data
 @param old_cap     old_list's capacity
 @param new_list    new_list to insert to
 @param new_cap     new_list's capacity
*/
void hashdb_rehash(bucket *old_list, size_t old_cap, bucket *new_list, size_t new_cap)
{
    for(size_t i = 0; i < old_cap; i++) {
        if(old_list[i].key != NULL) {
            hashdb_insert(new_list, new_cap, old_list[i].key, old_list[i].value);
        }
    }

}
/*! @function
 @param db      hashdb pointer
 @param new_cap new capacity
 @return        0 on succes, ENOMEM on failure
*/
int hashdb_realloc(hashdb *db, size_t new_cap)
{
    bucket *new_list = calloc(new_cap, sizeof *db->map);
    if(new_list == NULL) {
        return ENOMEM;
    }

    hashdb_rehash(db->map, db->cap, new_list, new_cap);
    free(db->map);

    db->map = new_list;
    db->cap = new_cap;

    return 0;
}

/*! @function
 @param db  hashdb pointer
 @return    0 if nothing to allocate or reallocated successfully, ENOMEM on failure
*/
int hashdb_grow(hashdb *db)
{
    if(db->n != (size_t) (db->cap * HASHDB_DEFAULT_LOADFACTOR)) {
        return 0;
    }

    size_t new_cap = GetHigherPrime(db->cap * 2);

    if(hashdb_realloc(db, new_cap) != 0) {
        return ENOMEM;
    }

    return 0;
}

/*! @function
 @param db  hashdb pointer
 @return    0 if nothing to allocate or reallocated successfully, ENOMEM on failure
*/
int hashdb_shrink(hashdb *db)
{
    if(db->n != (size_t) (db->cap * (1 - HASHDB_DEFAULT_LOADFACTOR)) ) {
        return 0;
    }

    size_t new_cap = GetLowerPrime(db->cap * 2);

    if(hashdb_realloc(db, new_cap) != 0) {
        return ENOMEM;
    }

    return 0;
}
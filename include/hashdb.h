#ifndef _HMAP_H
#define _HMAP_H

#include <stdio.h>

typedef void hashdb;

hashdb* hashdb_create(void);
void hashdb_destroy(hashdb *db);

int   hashdb_add(hashdb *db, const char *key, const void *data);
void* hashdb_get(hashdb *db, const char *key);
void* hashdb_del(hashdb *db, const char *key);

int   hashdb_ensure_capacity(hashdb *db, size_t new_capacity);
int   hashdb_clear(hashdb *db);
int   hashdb_reset(hashdb *db);
int   hashdb_hardreset(hashdb *db);

int   hashdb_to_json(hashdb *db, const char *path);
int   hashdb_from_json(hashdb *db, const char *path);

int   hashdb_to_http(hashdb *db, char *buffer, size_t bufsiz);
int   hashdb_from_http(hashdb *db, char *buffer, size_t bufsiz);



#endif
// (c) 2023 Florian Giest
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "../../include/hashdb.h"
#include "timebot.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROCKYOU_PATH "data/rockyou.txt"
#define ROCKYOU_LINES 14344392

#define HASHDB_START_GET_FROM 121512

char **test_keys = NULL;

/* initialize keys from rockyou.txt */
int init_test_keys(const char *path)
{
    FILE *fp = fopen(path, "r");
    if(fp == NULL) {
        perror("open file");
        return -1;
    }

    test_keys = calloc(ROCKYOU_LINES, sizeof *test_keys);
    if(test_keys == NULL) {
        perror("init_test_keys");
        return -1;
    }

    char buffer[128];
    for(size_t i = 0; i < ROCKYOU_LINES; i++) {
        fgets(buffer, sizeof(buffer), fp);
        buffer[strlen(buffer)-1] = '\0';
        test_keys[i] = strdup(buffer);
    }

    fclose(fp);
    return 0;
}

void destroy_keys()
{
    for(size_t i = 0; i < ROCKYOU_LINES; i++) {
        free(test_keys[i]);
    }
    free(test_keys);
}

/* test append 14344392 keys */
void hashdb_test_append_rockyou(hashdb *db)
{
    size_t x = ROCKYOU_LINES-1;
    size_t i;
    for(i = 0; i < ROCKYOU_LINES; i++, x--) {
        if(hashdb_add(db, test_keys[i], test_keys[x]) != 0) {
            perror("hashdb_add");
            abort();
        }
    }

}

/* test get 1000 keys */
void hashdb_test_get_1000_keys(hashdb *db) {

    for(size_t i = HASHDB_START_GET_FROM; i < HASHDB_START_GET_FROM + 1000; i++) {
        const char *res = hashdb_get(db, test_keys[i]);
        if(res == NULL) {
            perror("hashdb_get");
            abort();
        }
    }

}

/* test get single keys */
void hashdb_test_get_key(hashdb *db)
{
    const char *res = hashdb_get(db, test_keys[HASHDB_START_GET_FROM]);
    if(res == NULL) {
            perror("hashdb_get");
            abort();
    }
}

/* test get all keys */
void hashdb_test_get_rockyou(hashdb *db)
{
    for(size_t i = 0; i < ROCKYOU_LINES; i++) {
        const char *res = hashdb_get(db, test_keys[i]);
        if(res == NULL) {
            perror("hashdb_get");
            abort();
        }
    }
}


int main(void)
{
    timebot bot = { 0 };

    if(init_test_keys(ROCKYOU_PATH) != 0) {
        return EXIT_SUCCESS;
    }

    hashdb *db = hashdb_create();

    //hashdb_ensure_capacity(db, ROCKYOU_LINES);

    timebot_append(&bot, hashdb_test_append_rockyou, db, "Appending 14.344.392 key to hashdb");
    timebot_append(&bot, hashdb_test_get_key, db, "Get one key");
    timebot_append(&bot, hashdb_test_get_1000_keys, db, "Get 1000 keys");
    timebot_append(&bot, hashdb_test_get_rockyou, db, "Get all keys");

    timebot_run(&bot);
    timebot_print_summery(&bot);

    hashdb_destroy(db);

    destroy_keys();

}
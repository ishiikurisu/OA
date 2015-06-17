#ifndef BUCKET_H
#define BUCKET_H 0
#include "hash.h"
/*
#include "string.h"
#include "coseq.h"
*/

#ifdef UNIX
#define SEPARATOR ("/")
#else
#define SEPARATOR ("\\")
#endif

void bullshit() { return; }

typedef struct {
    hashmap* hash;
    char* path;
} bucketmap;

bucketmap* new_bucket(int size, int (*func)(char*), char* path)
{
    bucketmap* bucket = (bucketmap*) malloc(sizeof(bucketmap));
    hashmap*   map    = new_map(size, func);

    bucket->hash = map;
    bucket->path = path;

    return bucket;
}

char* get_path_to_index(bucketmap* bucket, int index)
{
    char* path = bucket->path;

    path = concat(path, SEPARATOR);
    path = concat(path, "b");
    path = concat(path, int_to_string(index));
    path = concat(path, ".bucket");

    return path;
}

bucketmap* bucketify(FILE* inlet, bucketmap* bucket, char att)
{
    hashmap* map    = bucket->hash;
    char*    line   = read_from_file(inlet);
    LIST*    data   = NULL;
    char*    key    = NULL;
    char*    value  = NULL;
    char*    path   = NULL;
    FILE*    outlet = NULL;
    int      index   = -1;

    while (!feof(inlet))
    {
        data  = split(line, att);
        key   = get_from_list(data, 0);
        value = get_from_list(data, 1);
        index = get_address(map, key);
        path  = get_path_to_index(bucket, index);

        outlet = fopen(path, "a");
        fprintf(outlet, "%s\t%s\n", key, value);
        fclose(outlet);
        line = read_from_file(inlet);
    }

    return bucket;
}

bucketmap* bucketify_file(char* input, bucketmap* bucket, char att)
{
    FILE* inlet = fopen(input, "r");
    bucket = bucketify(inlet, bucket, att);
    fclose(inlet);
    return bucket;
}

char* get_from_bucket(bucketmap* bucket, char* to_find)
{
    const char att = '\t';
    hashmap* map   = bucket->hash;
    int      index = get_address(map, to_find);
    char*    path  = get_path_to_index(bucket, index);
    FILE*    inlet = fopen(path, "r");
    char*    line  = NULL;
    LIST*    data  = NULL;
    char*    key   = NULL;
    char*    value = NULL;

    line = read_from_file(inlet);
    while (!feof(inlet) && value == NULL)
    {
        data = split(line, '\t');
        key  = get_from_list(data, 0);

        if (compare(key, to_find) == EQUAL)
            value = get_from_list(data, 1);
        else
            line = read_from_file(inlet);
    }

    return value;
}

#endif

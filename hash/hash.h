#ifndef HASH_H
#define HASH_H 0

#include "string.h"
#include "pair.h"

typedef struct {
    int size;
    PAIR** data;
    int (*func)(char*);
    int (*hash)(char*);
} hashmap;

hashmap* new_map(int size, int (*hash)(char*))
{
    hashmap* map = (hashmap*) malloc(sizeof(hashmap));
    PAIR** data = (PAIR**) malloc(size * sizeof(PAIR*));
    int i = 0;

    for (i = 0; i < size; ++i)
        data[i] = new_pair();

    map->size = size;
    map->data = data;
    map->func = hash;
    map->hash = hash;

    return map;
}

int get_address(hashmap* map, char* key)
{
    return map->hash(key) % map->size;
}

hashmap* put_in_map(hashmap* map, char* key, char* value)
{
    if (map == NULL || key == NULL || value == NULL) return map;
    int index = get_address(map, key);
    map->data[index] = associate(map->data[index], key, value);
    return map;
}

char* get_from_map(hashmap* map, char* key)
{
    if (map == NULL || key == NULL) return NULL;
    return find_in_pair(map->data[get_address(map, key)], key);
}

int map_contains_key(hashmap* map, char* key)
{
    if (map == NULL || key == NULL)
        return 0;

    if (get_from_map(map, key) != NULL)
        return 1;
    else
        return 0;
}

void write_map(hashmap* map)
{
    PAIR* pair = NULL;
    int i = 0;

    for (i = 0; i < map->size; ++i)
    {
        printf("%d: ", i);
        write_pair(map->data[i]);
        printf("\n");
    }
}

hashmap* feed_map(hashmap* map, char* input, char sep)
{
    FILE* inlet  = fopen(input, "r");
    char* line = read_from_file(inlet);
    LIST* data = NULL;
    char* key  = NULL;
    char* value = NULL;

    while (!feof(inlet))
    {
        data = split(line, sep);
        key = get_from_list(data, 0);
        value = get_from_list(data, 1);
        map = put_in_map(map, key, value);
        line = read_from_file(inlet);
    }

    fclose(inlet);
    return map;
}

#endif

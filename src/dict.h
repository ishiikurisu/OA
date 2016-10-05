#ifndef HASH_H
#define HASH_H 0

/* please include the list.h header */

typedef struct {
    int size;
    LIST** data;
    int (*func)(char*);
    int (*hash)(char*);
} DICT;

DICT* new_map(int size, int (*hash)(char*));
DICT* map_new(int sz, int(*h)(char*));
int get_address(DICT* map, char* key);
DICT* put_in_map(DICT* map, char* key, char* value);
DICT* map_put(DICT* m, char* k, char* v);
DICT* map_add(DICT* m, char* k, char* v);
char* get_from_map(DICT* map, char* key);
char* map_get(DICT* m, char* k);
int map_contains_key(DICT* map, char* key);
int map_contains(DICT* m, char* k);
void map_print(DICT* map);
char* map_to_string(DICT* map);
char* map_yaml(DICT* m);
DICT* map_feed(DICT* map, char* input, char sep);
char* remove_key(DICT* map, char* key);
char* map_remove(DICT* m, char* k);

#endif

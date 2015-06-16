#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "hash.h"
#include "hashfunctions.h"

int main(int argc, char** argv)
{
    FILE* inlet  = fopen(argv[1], "r");
    hashmap* map = new_map(10, stupid);
    char* line = read_from_file(inlet);
    LIST* data = NULL;
    char* key  = NULL;
    char* value = NULL;

    /* build hash from file*/
    while (!feof(inlet))
    {
        data = split(line, ':');
        key = get_from_list(data, 0);
        value = get_from_list(data, 1);
        map = put_in_map(map, key, value);
        line = read_from_file(inlet);
    }
    fclose(inlet);
    write_map(map);

    /* retrieve from hash */
    while ((line = read_from_file(stdin)) != NULL)
    {
        /*
        value = get_from_map(map, line);
        if (value == NULL)
        if (map_contains_key)
            printf("%s NOT FOUND\n", line);
        else
            printf("%s: %s\n", line, value);
        */
        if (map_contains_key(map, line))
            printf("contains\n");
        else
            printf("not have\n");
    }

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "hash.h"
#include "hashfunctions.h"

char* search_database(FILE* inlet, char* query)
{
    if (query == NULL) return NULL;

    char* output = NULL;
    int index = -1;

    sscanf(query, "%d", &index);
    output = get_line_from_file(inlet, index);

    return output;
}

int main(int argc, char** argv)
{
    hashmap* map = new_map(10, stupid);
    FILE* inlet = fopen(argv[2], "r");
    char* line = NULL;

    map = feed_map(map, argv[1], ':');

    while ((line = read_from_file(stdin)) != NULL)
    {
        printf("%s: ", line);
        line = get_from_map(map, line);
        if (line != NULL) {
            line = search_database(inlet, line);
            printf("%s\n", line);
        }
        else {
            printf("NULL\n");
        }
    }

    fclose(inlet);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "statichash.h"

int stupid(char* input)
{
    int output = 0;
    int limit = strlen(input);
    int i;

    for (i = 0; i < limit; ++i)
        output += input[i] * (i + 1);

    return output;
}

int main(int argc, char** argv)
{
    hashmap* map = new_map(10, stupid);
    FILE* inlet = fopen(argv[1], "r");
    char* line = read_from_file(inlet);

    while (!feof(inlet))
    {
        printf("adding %s\n", line);
        add_to_map(map, line);
        line = read_from_file(inlet);
    }
    write_keys(map);

    fclose(inlet);
    return 0;
}

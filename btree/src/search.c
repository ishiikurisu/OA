#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "database.h"
#include "btree.h"

int main(int argc, char* argv[])
{
    BT* btree = load_btree(argv[1]);
    char* line;
    char* key;
    char* value;
    int i;

    while ((key = read_from_file(stdin)) != NULL)
    {
        if (compare(key, "exit") == EQUAL)
            break;

        value = search_btree(btree, key);
        if (value != NULL)
            printf("%s => %s\n", key, value);
        else
            printf("%s NOT FOUND\n", key);
    }

    return 0;
}

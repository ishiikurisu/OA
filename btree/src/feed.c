#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "btree.h"

BTND* read_node(char* line)
{
    LIST* data = split(line, ':');
    char* key = get_from_list(data, 0);
    char* value = get_from_list(data, 1);
    return create_node(key, value);
}

int main(int argc, char* argv[])
{
    BT* btree = create_btree(STD_NAME);
    FILE* inlet = stdin;
    BTND* node;
    LIST* data;
    char* line;
    char* key;
    char* value;

    if (argc > 1)
        inlet = fopen(argv[1], "r");

    while ((line = read_from_file(inlet)) != NULL)
    {
        if (compare(line, "exit") == EQUAL) break;
        node = read_node(line);
        btree = insert(btree, node);
    }

    return 0;
}

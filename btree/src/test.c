#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "btree.h"

int main(int argc, char* argv[])
{
    BT* btree = create_btree(argv[1]);
    BTND* node;
    LIST* data;
    char* line;
    char* key;
    char* value;

    while ((line = read_from_file(stdin)) != NULL)
    {
        data = split(line, ':');
        key = get_from_list(data, 0);
        value = get_from_list(data, 1);
        node = create_node(key, value);
        btree = insert(btree, node);
    }

    return 0;
}

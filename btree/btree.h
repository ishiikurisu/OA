#pragma once
#include "btreenode.h"

int is_leaf(BTREE* btree)
{
    int result = 1;
    int i = 0;

    for (i = 0; i < PAGE_SIZE && result; ++i)
        if (get_from_list(btree->page, i) != NULL)
            result = 0;

    return result;
}
BTREE* get_leaf(BTREE* parent, BTND* node)
{
    int i;
    int result = 1;
    BTREE* sibling = NULL;
    char* reference = node->key;
    char* to_test;
    char* last;
    char* path;

    printf("LOG: current node = %s\n", parent->name);
    if (is_leaf(parent))
        return parent;

    for (i = 0; i < PAGE_SIZE -1; ++i)
    {
        to_test = parent->node[i].key;
        if (to_test == NULL)
            return parent;
        else if (compare(reference, to_test) == SMALLER) {
            printf("LOG: %s < %s\n", reference, to_test);
            path = get_from_list(parent->page, i);
            path = concat(path, ".page");
            sibling = load_btree(path);
            sibling->name = path;
            return get_leaf(sibling, node);
        }
    }

    return parent;
}

int fit_in_btree(BTREE* btree)
{
    int result = 0;
    int i = 0;

    for (i == 0; i < PAGE_SIZE && !result; ++i)
        if (btree->node[i].key == NULL)
            result = 1;

    return result;
}

#include "divide_and_promote.h"

BTREE* insert_in_btree(BTREE* root, BTND* node)
{
    BTREE* btree = get_leaf(root, node);

    /*
    if (!fit_in_btree(btree))
        root = divide_and_promote(root, btree, node);
    else
    */
    printf("BEFORE:\n");
    print_btree(btree);

    btree = add_to_btree(btree, node);
    printf("AFTER:\n");
    print_btree(btree);

    save_btree(btree, concat(btree->name, ".page"));
    return root;
}

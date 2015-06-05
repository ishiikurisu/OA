#pragma once
#include "btreenode.h"


BTREE* get_leaf(BTREE* parent, BTND* node)
{
    int i;
    int result = 1;
    BTREE* sibling = NULL;
    char* reference = node->key;
    char* to_test;

    /* test if parent is a leaf*/
    for (i = 0; i < PAGE_SIZE && result; ++i)
        if (get_from_list(parent->page, i) != NULL)
            result = 0;
    if (result)
        return parent;

    /* discover where to go */
    to_test = parent->node[0].key;
    if (compare(reference, to_test) < SMALLER) {

    }

    for (i = 1; i < PAGE_SIZE; ++i)
    {
        sibling = NULL;

    }

    return sibling;
}

BTREE* insert_in_btree(BTREE* root, BTND* node)
{
    BTREE* btree = get_leaf(root, node);
    int result = 0;
    int i = 0;

    if (!fit_in_btree(btree))
        divide_and_promote(btree, node);
    else
        add_to_btree(btree, node);

    return btree;
}

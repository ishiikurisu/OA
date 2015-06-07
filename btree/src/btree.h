#pragma once
#include "btreenode.h"
#define PAGE_SIZE (4)

int is_leaf(BTREE* btree)
{
    LIST* page = btree->page;

    if (page->next == NULL)
        return 1;
    else
        return 0;
}

int fit_in_btree(BTREE* btree)
{
    int count = number_bnodes(btree->node);

    if (count >= PAGE_SIZE)
        return 0;
    else
        return 1;
}

BTREE* get_leaf(BTREE* parent, BTND* node)
{
    int index;
    BT* sibling;

    char* path;

    if (is_leaf(parent))
        return parent;

    index = find_place_to_fit(parent, node);
    path = get_from_list(parent->page, index);
    sibling = load_btree(path);
    return get_leaf(sibling, node);
}

#include "divide_and_promote.h"
BTREE* insert(BTREE* root, BTND* bnode)
{
    BTREE* btree = get_leaf(root, bnode);

    if (!fit_in_btree(btree)) {
        btree = divide_and_promote(root, bnode);
    }
    else {
        btree = add_bnode_to_btree_in_order(btree, bnode);
    }

    save_btree(btree);
    return root;
}

BTREE* insert_to_btree(BTREE* bt, char* k, char* v)
{
    return insert(bt, create_node(k, v));
}

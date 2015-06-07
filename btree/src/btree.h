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

BTREE* get_leaf(BTREE* parent, BTND* node)
{
    int index;
    BT* sibling;

    if (is_leaf(parent))
        return parent;

    index = find_place_to_fit(parent, node);
    sibling = load_btree(get_from_list(parent->page, index));
    return get_leaf(sibling, node);
}

BTREE* get_parent(BTREE* parent, BTND* to_find)
{
    BT* sibling;
    int index;

    index = find_place_to_fit(parent, to_find);
    sibling = load_btree(get_from_list(parent->page, index));

    if (contains_node(sibling, to_find))
        return parent;
    else
        return get_parent(sibling, to_find);
}

typedef struct __divided__ {
    BTREE* smaller;
    BTREE* bigger;
} divided;
divided* alloc_struct_divided()
{ return (divided*) malloc(sizeof(divided)); }
divided* divide(BTREE* btree)
{
    divided* result = alloc_struct_divided();
    BTND*  node    = btree->node;
    LIST*  page    = btree->page;
    BTREE* smaller = NULL;
    BTREE* bigger  = NULL;
    int added = 0;

    inc(node);
    smaller = create_btree(get_key(node));
    for (; added < PAGE_SIZE / 2; ++added, inc(node))
    {
        smaller = add_bnode_to_btree(smaller, node);
        smaller = add_page_to_btree(smaller, get_from_list(page, added));
        smaller->name = get_key(node);
    }

    bigger = create_btree(get_key(node));
    for (; added < PAGE_SIZE; inc(node), ++added)
    {
        bigger = add_bnode_to_btree(bigger, node);
        bigger = add_page_to_btree(bigger, get_from_list(page, added));
        bigger->name = get_key(node);
    }

    save_btree(smaller);
    save_btree(bigger);
    return result;
}

BTND* promote(BTREE* btree)
{
    BTND* node = btree->node;
    BTND* to_promote = node;

    while (node->next != NULL)
    {
        inc(node);
        to_promote = node;
    }

    return to_promote;
}

int fit_in_btree(BTREE* btree)
{
    int count = number_bnodes(btree->node);

    if (count > PAGE_SIZE)
        return 0;
    else
        return 1;
}

BTREE* divide_and_promote(BTREE* root, BTND* to_add)
{
    BTREE* parent;
    BTND* promoted_from_smaller;
    BTND* promoted_from_bigger;
    divided* siblings;

    parent = get_leaf(root, to_add);
    siblings = divide(parent);
    promoted_from_smaller = promote(siblings->smaller);
    promoted_from_bigger = promote(siblings->bigger);

    parent = get_parent(root, to_add);
    root = insert(root, promoted_from_smaller);
    root = insert(root, promoted_from_bigger);

    return root;
}

BTREE* insert(BTREE* root, BTND* bnode)
{
    BTREE* btree = get_leaf(root, bnode);

    btree = add_bnode_to_btree_in_order(btree, bnode);
    if (!fit_in_btree(btree))
        root = divide_and_promote(root, bnode);

    save_btree(btree);
    return root;
}

BTREE* insert_to_btree(BTREE* bt, char* k, char* v)
{
    return insert(bt, create_node(k, v));
}

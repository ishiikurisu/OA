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

BTREE* get_node_parent(BTREE* parent, BTND* to_find)
{
    BTREE* sibling;
    int index;

    index = find_place_to_fit(parent, to_find);
    sibling = load_btree(get_from_list(parent->page, index));

    if (sibling == NULL)
        return NULL;
    if (contains_node(sibling, to_find))
        return parent;
    else
        return get_node_parent(sibling, to_find);
}

BTREE* get_btree_parent(BTREE* parent, BTREE* to_find)
{
    if (parent == to_find)
        return NULL;

    BTND* first_son = (to_find->node)->next;
    return get_node_parent(parent, first_son);
}

typedef struct __divided__ {
    BTREE* smaller;
    BTREE* bigger;
} divided;
divided* alloc_struct_divided()
{ return (divided*) malloc(sizeof(divided)); }
divided* divide(BTREE* btree)
{
    divided* result  = alloc_struct_divided();
    BTND*    node    = btree->node;
    LIST*    page    = btree->page;
    BTREE*   smaller = new_btree();
    BTREE*   bigger  = new_btree();
    int added = 0;

    inc(node);
    for (added = 0; added < PAGE_SIZE / 2; ++added, inc(node))
    {
        smaller = add_bnode_to_btree(smaller, node);
        smaller = add_page_to_btree(smaller, get_from_list(page, added));
        smaller->name = get_key(node);
    }
    save_btree(smaller);

    for (NULL; node != NULL; inc(node), ++added)
    {
        bigger = add_bnode_to_btree(bigger, node);
        smaller = add_page_to_btree(smaller, get_from_list(page, added));
        bigger->name = get_key(node);
    }
    save_btree(bigger);

    result->smaller = smaller;
    result->bigger = bigger;
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

int overflow(BTREE* btree)
{
    int count = number_bnodes(btree->node);

    if (count > PAGE_SIZE)
        return 1;
    else
        return 0;
}

BTREE* update(BTREE* btree, BTREE* smaller, BTREE* bigger)
{
    BTREE* new_btree;

    if (btree == NULL)
        new_btree = create_btree("root");
    else
        new_btree = create_btree(btree->name);

    new_btree = add_bnode_to_btree(new_btree, last_node(smaller->node));
    new_btree = add_bnode_to_btree(new_btree, last_node(bigger->node));
    new_btree = add_page_to_btree(new_btree, smaller->name);
    new_btree = add_page_to_btree(new_btree, bigger->name);
    save_btree(new_btree);

    return new_btree;
}

BTREE* divide_and_promote(BTREE* root, BTREE* to_divide)
{
    divided* siblings = divide(to_divide);
    BTREE* parent = get_btree_parent(root, to_divide);

    if (parent == NULL) {
        root = update(root, siblings->smaller, siblings->bigger);
        parent = root;
    }
    else {
        parent = update(parent, siblings->smaller, siblings->bigger);
        if (overflow(parent))
            divide_and_promote(root, parent);
    }

    return root;
}

BTREE* insert(BTREE* root, BTND* bnode)
{
    BTREE* btree = get_leaf(root, bnode);

    btree = add_bnode_to_btree_in_order(btree, bnode);
    if (overflow(btree)) {
        root = divide_and_promote(root, btree);
        btree = root;
    }

    save_btree(btree);
    return root;
}

BTREE* insert_to_btree(BTREE* bt, char* k, char* v)
{
    return insert(bt, create_node(k, v));
}

char* get_from_btree(BTREE* root, BTND* query)
{
    BTREE* btree;
    int index;

    if (root == NULL)
        return NULL;


    if (contains_node(root, query)) {
        return get_value_from_key(root->node, get_key(query));
    }
    else {
        if (is_leaf(root))
            return NULL;
        index = find_place_to_fit(root, query);
        btree = load_btree(get_from_list(root->page, index));
        return get_from_btree(btree, query);
    }
}

char* search_btree(BTREE* root, char* search_key)
{
    BTND* query = create_node(search_key, "");
    return get_from_btree(root, query);
}

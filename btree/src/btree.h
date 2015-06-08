#pragma once
#include "btreenode.h"
#define PAGE_SIZE (4)
#define STD_NAME ("root")

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
    char*    path    = NULL;
    int added = 0;

    inc(node);
    for (added = 0; added < PAGE_SIZE / 2; added++, inc(node))
    {
        smaller = add_bnode_to_btree(smaller, node);
        smaller = add_page_to_btree(smaller, get_from_list(page, added));
        smaller->name = get_key(node);
    }
    save_btree(smaller);

    for (NULL; node != NULL; inc(node), added++)
    {
        bigger = add_bnode_to_btree(bigger, node);
        bigger = add_page_to_btree(bigger, get_from_list(page, added));
        bigger->name = get_key(node);
    }
    save_btree(bigger);

    result->smaller = smaller;
    result->bigger = bigger;
    return result;
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
    BTREE* replacement = create_btree(btree->name);

    replacement = add_bnode_to_btree(replacement, last_node(smaller->node));
    replacement = add_bnode_to_btree(replacement, last_node(bigger->node));
    replacement = add_page_to_btree(replacement, smaller->name);
    replacement = add_page_to_btree(replacement, bigger->name);
    save_btree(replacement);

    return replacement;
}

BTREE* divide_and_promote(BTREE* root, BTREE* to_divide)
{
    divided* siblings = divide(to_divide);
    BTREE*   parent   = get_btree_parent(root, to_divide);
    BTREE*   sibling  = NULL;

    if (parent == NULL) {
        root = update(root, siblings->smaller, siblings->bigger);
    }
    else {
        sibling = siblings->smaller;
        promote(root, parent, last_node(sibling->node));
        parent = add_bnode_to_btree_in_order(parent, last_node(sibling->node));
        if (overflow(parent))
            root = divide_and_promote(root, parent);
        sibling = siblings->bigger;
        parent = add_bnode_to_btree_in_order(parent, last_node(sibling->node));
        if (overflow(parent))
            root = divide_and_promote(root, parent);
    }

    return root;
}

BTREE* promote(BTREE* root, BTREE* btree, BTND* bnode)
{
    btree = add_bnode_to_btree_in_order(btree, bnode);
    if (overflow(btree))
        root = divide_and_promote(root, btree);

    return root;
}

BTREE* insert(BTREE* root, BTND* bnode)
{
    BTREE* btree = get_leaf(root, bnode);

    if (contains_node(root, bnode))
        return root;

    root = promote(root, btree, bnode);
    write_btree(btree);
    save_btree(btree);
    return root;
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

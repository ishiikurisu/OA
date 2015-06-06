#pragma once
#include "btreenode.h"

BTREE* create_new_page(BTREE* parent, BTND* node)
{
    BTREE* sibling = new_btree();
    char*  key     = node->key;
    char*  value   = node->value;
    char*  path    = concat(key, ".page");
    FILE*  page    = fopen(concat("page\\", path), "w");

    fprintf(page, "%s\n", key);
    fprintf(page, "NODE|%s:%s\n", key, value);
    fclose(page);

    parent->page = add_to_list(parent->page, key);
    save_btree(parent, concat(parent->name, ".page"));
    return parent;
}

int is_leaf(BTREE* btree)
{
    int result = 1;
    int i = 0;

    for (i = 0; i < PAGE_SIZE && result; ++i)
        if (get_from_list(btree->page, i) != NULL)
            result = 0;

    return result;
}
BTREE* get_sibling(char* path) {
    BTREE* sibling = load_btree(concat(path, ".page"));
    sibling->name = path;
    return sibling;
}
BTREE* get_leaf(BTREE* parent, BTND* node)
{
    BTREE* sibling = NULL;
    char* reference = node->key;
    char* to_test;
    char* last;
    char* path;
    int i;

    printf("LOG: current node = %s\n", parent->name);
    if (is_leaf(parent))
        return parent;

    for (i = 0; i < PAGE_SIZE -1; ++i)
    {
        to_test = parent->node[i].key;
        path    = get_from_list(parent->page, i);

        if (to_test == NULL && path != NULL) {
            printf("LOG: going to \"%s\"\n", path);
            sibling = get_sibling(path);
            return get_leaf(sibling, node);
        }
        else if (to_test == NULL && path == NULL) {
            path = get_from_list(parent->page, i - 1);
            if (path != NULL) {
                sibling = get_sibling(path);
                return get_leaf(sibling, node);
            }
            else i = PAGE_SIZE-1;
        }
        else if (compare(reference, to_test) == SMALLER) {
            printf("LOG: %s < %s\n", reference, to_test);
            sibling = get_sibling(path);
            return get_leaf(sibling, node);
        }
    }

    if ((path = get_from_list(parent->page, i)) != NULL) {
        sibling = get_sibling(path);
        sibling = get_leaf(sibling, node);
    }
    else {
        parent = create_new_page(parent, node);
        sibling = load_btree(concat(reference, ".page"));
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

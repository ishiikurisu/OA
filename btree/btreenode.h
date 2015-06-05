#pragma once
#define PAGE_SIZE (4)
#define NULL_PAGE ("NULL")
#define PAGE_TYPE ("PAGE")
#define NODE_TYPE ("NODE")

typedef struct {
    char* key;
    char* value;
} BTREE_NODE;
typedef BTREE_NODE BTND;

typedef struct {
    LIST* page;
    BTND* node;
} BTREE;

BTND* alloc_nodes()
{
    BTND* node = (BTND*) malloc(sizeof(BTND) * PAGE_SIZE);
    int b = -1;

    for (b = 0; b < PAGE_SIZE; ++b)
    {
        node[b].key   = NULL;
        node[b].value = NULL;
    }

    return node;
}

BTND* new_btree_node(char* key, char* value)
{
    BTND* node = (BTND*) malloc(sizeof(BTND));

    node->key = key;
    node->value = value;

    return node;
}

BTREE* alloc_btree()
{ return (BTREE*) malloc(sizeof(BTREE)); }

BTREE* new_btree()
{
    BTREE* btree = alloc_btree();

    btree->page = new_list();
    btree->node = alloc_nodes();

    return btree;
}

BTREE* add_to_btree(BTREE* btree, BTND* node)
{
    BTND* new_nodes = alloc_nodes();
    char* ref = node->key;
    char* add;
    int i = 0;

    add = btree->node[0].key;
    while (compare(ref, add) == BIGGER)
    {
        new_nodes[i].key = btree->node[i].key;
        new_nodes[i].value = btree->node[i].value;
        ++i, add = btree->node[i].key;
    }

    new_nodes[i].key = node->key;
    new_nodes[i].value = node->value;
    i++;
    while (i < PAGE_SIZE)
    {
        new_nodes[i].key = btree->node[i-1].key;
        new_nodes[i].value = btree->node[i-1].value;
        ++i;
    }

    free(btree->node);
    btree->node = new_nodes;
    return btree;
}

void print_btree(BTREE* btree)
{
    int i = 0;
    char* data = btree->node[0].key;
    char *key, *value;

    printf("---\n- btree node:\n");
    while (btree->node[i].key != NULL && i < PAGE_SIZE)
    {
        key = btree->node[i].key;
        value = btree->node[i].value;
        if (key != NULL)
            printf("  - %s: %s\n", key, value);
        else
            break;
        ++i;
    }

    printf("...\n");
}

BTREE* load_btree(char* name)
{
    FILE*  inlet = fopen(name, "r");
    BTREE* btree = new_btree();
    BTND*  bnode = NULL;
    LIST*  data  = NULL;
    char*  line  = NULL;
    char*  key   = NULL;
    char*  value = NULL;
    int    added = 0;

    while (!feof(inlet))
    {
        line = read_from_file(inlet);
        if (line != NULL) {
            /* TYPE|VALUE */
            data  = split(line, '|');
            key   = get_from_list(data, 0);
            value = get_from_list(data, 1);

            if (compare(key, PAGE_TYPE) == EQUAL) {
                btree->page = add_to_list(btree->page, value);
            }
            else if (compare(key, NODE_TYPE) == EQUAL) {
                /* PPK:PRR */
                data = split(value, ':');
                key = get_from_list(data, 0);
                value = get_from_list(data, 1);
                bnode = new_btree_node(key, value);
                add_to_btree(btree, bnode);
                ++added;
            }
        }
    }

    fclose(inlet);
    return btree;
}

void free_btree(BTREE* btree)
{
    free(btree->node);
    free_list(btree->page);
    free(btree);
}

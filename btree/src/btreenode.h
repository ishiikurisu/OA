#pragma once
#define STD_NAME ("root")

typedef struct {
    char* key;
    char* value;
} INDEX_NODE;
typedef INDEX_NODE INND;

INDEX_NODE* new_index_node()
{
    INDEX_NODE* node = (INDEX_NODE*) malloc(sizeof(INDEX_NODE));

    node->key   = NULL;
    node->value = NULL;

    return node;
}

typedef struct __BT_NODE__ {
    INDEX_NODE* data;
    struct __BT_NODE__* next;
} BT_NODE;
typedef BT_NODE BTND;

BTND* new_btnode()
{
    BTND* node = (BTND*) malloc(sizeof(BTND));

    node->data = new_index_node();
    node->next = NULL;

    return node;
}

BTND* last_node(BTND* bnode)
{
    BTND* node = bnode;

    while (node->next != NULL)
        inc(node);

    return node;
}

BTND* create_node(char* key, char* value)
{
    BTND* node = new_btnode();
    INND* index = node->data;

    index->key = key;
    index->value = value;

    node->data = index;
    return node;
}

BTND* add_btnode(BTND* bnode, char* key, char* value)
{
    BTND* to_add = create_node(key, value);
    BTND* butt   = last_node(bnode);

    butt->next = to_add;

    return bnode;
}

BTND* add_to_btnode_at_index(BTND* bnode, char* key, char* value, int index)
{
    BTND* to_add = create_node(key, value);
    BTND* node = bnode;
    int i = 0;

    while (node != NULL)
    {
        if (i == index) {
            to_add->next = node->next;
            node->next = to_add->next;
            break;
        }

        inc(node);
        i++;
    }

    if (node == NULL) {
        node = last_node(bnode);
        node->next = to_add;
        to_add->next = NULL;
    }

    return bnode;
}

char* get_key(BTND* node)
{
    INND* index = node->data;
    return index->key;
}
char* get_value(BTND* node)
{
    INND* index = node->data;
    return index->value;
}

char* get_value_from_key(BTND* bnode, char* key)
{
    char* result = NULL;
    BTND* node   = bnode->next;

    while (node != NULL && result == NULL)
    {
        if (compare(get_key(node), key) == EQUAL)
            result = get_value(node);
        inc(node);
    }

    return result;
}

int number_bnodes(BTND* bnode)
{
    BTND* node = bnode->next;
    int   result = 0;

    while (node != NULL)
    {
        inc(node);
        result++;
    }

    return result;
}

INND* remove_from_btnode(BTND* bnode, int index)
{
    BTND* node   = bnode->next;
    BTND* to_del = NULL;
    INND* outlet = NULL;
    int i = 0;

    while ((i + 1 != index) && (node != NULL))
    {
        inc(node);
        ++i;
    }

    if (node->next != NULL)
    {
        to_del = node->next;
        outlet = to_del->data;
        node->next = to_del->next;
        free(to_del);
    }

    return outlet;
}

#define PAGE_TYPE ("PAGE")
#define NODE_TYPE ("NODE")
typedef struct {
    char* name;
    BTND* node;
    LIST* page;
} BTREE;
typedef BTREE BT;

BTREE* new_btree()
{
    BTREE* btree = (BTREE*) malloc(sizeof(BTREE));

    btree->name = NULL;
    btree->node = new_btnode();
    btree->page = new_list();

    return btree;
}

BTREE* create_btree(char* name)
{
    BTREE* btree = new_btree();
    btree->name = name;
    return btree;
}

int is_std_name(char* name)
{
    if (compare(name, STD_NAME) == EQUAL)
        return 1;
    else
        return 0;
}

BTREE* add_bnode_to_btree_in_order(BTREE* btree, BTND* bnode)
{
    BTND* last = btree->node;
    BTND* node = btree->node;
    char* key  = get_key(bnode);

    inc(node);
    while (node != NULL)
    {
        if (compare(key, get_key(node)) == SMALLER) {
            bnode->next = last->next;
            last->next = bnode;
            break;
        }

        if (compare(key, get_key(node)) == EQUAL)
            return btree;

        last = node;
        inc(node);
    }

    if (node == NULL) {
        node = last_node(btree->node);
        node->next = bnode;
        bnode->next = NULL;
        if (!is_std_name(btree->name))
            btree->name = key;
    }

    return btree;
}

BTREE* add_bnode_to_btree(BTREE* btree, BTND* bnode)
{
    BTND* node  = btree->node;
    char* key   = get_key(bnode);
    char* value = get_value(bnode);

    node = add_btnode(node, key, value);
    if (!is_std_name(btree->name))
        btree->name = key;

    return btree;
}

BTREE* add_node_to_btree(BTREE* btree, char* key, char* value)
{
    BTND* bnode = create_node(key, value);
    return add_bnode_to_btree(btree, bnode);
}

BTREE* add_page_to_btree(BTREE* btree, char* path)
{
    if (path != NULL)
        btree->page = add_to_list(btree->page, path);
    return btree;
}

int contains_node(BTREE* btree, BTND* to_find)
{
    char* reference  = get_key(to_find);
    char* to_compare = NULL;
    BTND* node;
    int result = 0;

    for (node = btree->node; node!= NULL && !result; inc(node))
    {
        to_compare = get_key(node);

        if (compare(reference, to_compare) == EQUAL)
            result = 1;
    }

    return result;
}

int find_place_to_fit(BTREE* btree, BTND* to_find)
{
    int result = 0;
    BTND* node = btree->node;
    char* key  = get_key(to_find);
    char* last = NULL;
    char* curr = NULL;

    /* first step*/
    if (node->next == NULL)
        return result;
    inc(node);
    last = get_key(node);
    if (compare(key, last) == SMALLER)
        return result;

    /* next steps */
    for (result++, inc(node); node != NULL; result++, inc(node))
    {
        curr = get_key(node);

        if ((compare(key, last) == BIGGER) && (compare(key, curr) == SMALLER))
            return result;
        else
            last = curr;

        result++;
    }

    return result - 1;
}

BTREE* load_btree(char* path)
{
    if (path == NULL) return NULL;

    char* input = concat(path, ".page");
    FILE* inlet = fopen(input, "r");
    BTREE*   btree = new_btree();
    char* line  = read_from_file(inlet);
    char* key   = NULL;
    char* value = NULL;
    LIST* data  = NULL;

    btree->name = line;
    while (!feof(inlet))
    {
        line = read_from_file(inlet);
        if (line == NULL) continue;

        data  = split(line, '|');
        key   = get_from_list(data, 0);
        value = get_from_list(data, 1);

        if (compare(key, PAGE_TYPE) == EQUAL) {
            btree = add_page_to_btree(btree, value);
        }
        else if (compare(key, NODE_TYPE) == EQUAL) {
            data  = split(value, ':');
            key   = get_from_list(data, 0);
            value = get_from_list(data, 1);
            btree = add_node_to_btree(btree, key, value);
            btree->name = key;
        }
    }

    return btree;
}

void save_btree(BTREE* btree)
{
    char* path   = concat(btree->name, ".page");
    FILE* outlet = fopen(path, "w");
    BTND* node   = btree->node;
    LIST* page   = btree->page;
    char* key    = NULL;
    char* value  = NULL;

    rewind(outlet);
    fprintf(outlet, "%s\n", btree->name);

    while (node != NULL)
    {
        key   = get_key(node);
        value = get_value(node);
        if (key != NULL)
            fprintf(outlet, "NODE|%s:%s\n", key, value);
        inc(node);
    }

    while (page != NULL)
    {
        key = page->info;
        if (key != NULL)
            fprintf(outlet, "PAGE|%s\n", key);
        inc(page);
    }

    fflush(outlet);
    fclose(outlet);
}

void write_btree(BTREE* btree)
{
    BTND* node   = btree->node;
    LIST* page   = btree->page;
    char* key    = NULL;
    char* value  = NULL;

    fprintf(stdout, "%s\n", btree->name);

    inc(node);
    while (node != NULL)
    {
        key   = get_key(node);
        value = get_value(node);
        if (key != NULL)
            fprintf(stdout, "NODE|%s:%s\n", key, value);
        inc(node);
    }

    inc(page);
    while (page != NULL)
    {
        key = page->info;
        fprintf(stdout, "PAGE|%s\n", key);
        inc(page);
    }
}

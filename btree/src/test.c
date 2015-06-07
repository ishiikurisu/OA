#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "btree.h"

int f()
{
    static int n = -1;
    n++;
    return n;
}

void write_compare(char* s, char* t)
{
    if (compare(s, t) == SMALLER)
        printf("smaller\n");
    else
        printf("BIGGER\n");
}

void test_fit(BT* bt, char* k, char* v)
{
    BTND* n = create_node(k, v);
    int fit = find_place_to_fit(bt, n);
    printf("%s fit @ %d\n", k, fit);
    insert(bt, n);
}

void btree_test(char* input, char* output)
{
    BT* btree = load_btree(input);
    test_fit(btree, "CAROL HAINE", "19");
    test_fit(btree, "JUBS", "18");
    /* test_fit(btree, "IGOR HETERO", "20"); */
}

int main(int argc, char* argv[])
{
    int i = 0;

    /*
    for (i = 0; i < 10; ++i)
        printf("%d\n", f());

    write_compare("joe", "frank");
    */
    btree_test(argv[1], argv[2]);

    return 0;
}

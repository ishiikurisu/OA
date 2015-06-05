#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "btreenode.h"

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

void btree_test()
{
    BTREE* btree = load_btree("bitch.txt");
    BTND* bnode = new_btree_node("FAFINHA", "10");

    print_btree(btree);
    add_to_btree(btree, bnode);
    print_btree(btree);
}

int main()
{
    int i = 0;

    /*
    for (i = 0; i < 10; ++i)
        printf("%d\n", f());

    write_compare("joe", "frank");
    */
    btree_test();

    return 0;
}

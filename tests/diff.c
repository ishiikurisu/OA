#include <stdlib.h>
#include <stdio.h>
#include "src/string.h"
#include "src/list.h"
#include "src/coseq.h"

int main(int argc, char* argv[])
{
    char* i1 = argv[1];
    char* i2 = argv[2];
    FILE* f1 = fopen(i1, "r");
    FILE* f2 = fopen(i2, "r");
    char* l1 = read_from_file(f1);
    char* l2 = read_from_file(f2);
    int   line = 1;

    while (!feof(f1) && !feof(f2))
    {
        line++;

        if (compare(l1, l2) != EQUAL) {
            printf("%d\n", line);
            printf("%s: %s\n", i1, l1);
            printf("%s: %s\n", i2, l2);
            printf("---\n");
        }

        l1 = read_from_file(f1);
        l2 = read_from_file(f2);
    }

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "src/string.h"
#include "src/list.h"
#include "src/coseq.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        fprintf(stderr, "missing argument\n");
        return 1;
    }

    char* input = argv[1];
    FILE* inlet = fopen(input, "r");
    int   count = 0;

    input = read_from_file(inlet);
    while (!feof(inlet))
    {
        count++;
        input = read_from_file(inlet);
    }

    printf("%d\n", count);
    fclose(inlet);
    return 0;
}

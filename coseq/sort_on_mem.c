#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"

void sort_on_mem(char* input, char* output)
{
    FILE* inlet  = fopen(input, "r");
    LIST* subset = new_list();
    char* data   = read_from_file(inlet);

    while (data != NULL && !feof(inlet))
    {
        add_to_list(subset, data);
        data= read_from_file(inlet);
    }

    sort_list(subset);
    write_list_to_file(subset, output);

    fclose(inlet);
}

void main(int argc, char* argv[])
{
    char* input  = argv[1];
    char* output = argv[2];
    sort_on_mem(input, output);
}

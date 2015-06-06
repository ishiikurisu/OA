#pragma once
#include "string.h"
#include "list.h"
#include "coseq.h"

void write_index_with_PRR(char* line, FILE* fp)
{
    static int PRR = 0;
    LIST* data = split(line, '|');
    char* info = get_from_list(data, 0);

    fprintf(fp, "%s:%d\n", info, PRR);
    fflush(fp);
    PRR++;
}

void to_index(char* input, char* output)
{
    FILE* inlet  = fopen(input, "r");
    FILE* outlet = fopen(output, "w");
    char* data   = NULL;

    while (!feof(inlet))
    {
        data = read_from_file(inlet);
        if (data != NULL)
            write_index_with_PRR(data, outlet);
    }

    fclose(inlet);
    fclose(outlet);
}

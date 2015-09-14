#include <oa.h>
#include "lempelziv.h"

char *query_output(int argc, char **argv)
{
    char *output = argv[1];

    if (argc == 2)
        cat(output, ".lz78");
    else
        output = argv[2];

    return output;
}

int main(int argc, char *argv[]) {
    char *input = argv[0];
    char *output = query_output(argc, argv);

    LZ78(input, output);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "database.h"

main(int argc, char* argv[])
{
    char* input  = NULL;
    char* output = NULL;

    if (argc > 1)
        input = argv[1];
    if (argc > 2)
        output = argv[2];
    to_index(input, output);
}

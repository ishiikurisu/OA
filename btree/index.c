#include <stdlib.h>
#include <stdio.h>
#include "database.h"

main(int argc, char* argv[])
{
    char* input  = argv[1];
    char* output = argv[2];
    to_index(input, output);
}

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"

void main(int argc, char* argv[])
{
    char* file1  = argv[1];
    char* file2  = argv[2];
    char* output = argv[3];
    merge_on_memory(file1, file2, output);
}

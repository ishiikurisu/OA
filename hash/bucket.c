#include <stdlib.h>
#include <stdio.h>
#include "src/string.h"
#include "src/list.h"
#include "src/coseq.h"
#include "src/pair.h"
#include "src/hashfunctions.h"
#include "statichash/hash.h"
#include "statichash/bucket.h"

int main(int argc, char** argv)
{
    char*      input  = argv[2];
    char*      output = argv[1];
    bucketmap* bucket = new_bucket(10, dumb, output);
    FILE*      inlet  = fopen(input, "r");
    const char sep    = ':';

    bucket = bucketify(inlet, bucket, sep);
    fclose(inlet);

    while ((input = read_from_file(stdin)) != NULL)
        printf("%s @ %s\n", input, get_from_bucket(bucket, input));

    return 0;
}

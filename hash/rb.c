#include <stdlib.h>
#include <stdio.h>
#include "src/string.h"
#include "src/list.h"
#include "src/coseq.h"
#include "src/pair.h"
#include "statichash/bucket.h"
#include "src/hashfunctions.h"
#define GET_OPTION ("get")
#define DEL_OPTION ("remove")
#define ADD_OPTION ("add")
#define QUIT_OPTION ("quit")

char* read()
{
    return read_from_file(stdin);
}

char* get_option(bucketmap* bucket)
{
    char* message = "";
    char* key = read();
    char* value = get_from_bucket(bucket, key);

    message = concat(message, key);
    message = concat(message, ": ");
    message = concat(message, value);

    return message;
}

char* add_option(bucketmap* bucket)
{
    char* input = read();
    char* output = "added ";
    LIST* data = split(input, ':');
    char* key = get_from_list(data, 0);
    char* value = get_from_list(data, 1);

    bucket = add_to_bucket(bucket, key, value);
    output = concat(output, key);

    return output;
}

char* del_option(bucketmap* bucket)
{
    char* input = read();
    char* output = concat(input, " returned ");

    return concat(output, remove_from_bucket(bucket, input));
}

int main(int argc, char** argv)
{
    bucketmap* bucket = new_bucket(10, dumb, NULL);
    char* line  = read();

    bucket = bucketify_file(argv[1], bucket, ':');
    for ( ; ; )
    {
        if (compare(line, GET_OPTION) == EQUAL)
            line = get_option(bucket);
        else if (compare(line, ADD_OPTION) == EQUAL)
            line = add_option(bucket);
        else if (compare(line, DEL_OPTION) == EQUAL)
            line = del_option(bucket);
        else if (compare(line, QUIT_OPTION) == EQUAL)
            break;
        else
            line = NULL;

        if (line)
            printf("%s\n", line);
        else
            printf("...\n");

        line = read();
    }

    save_bucket(bucket, "new_index.txt");
    return 0;
}

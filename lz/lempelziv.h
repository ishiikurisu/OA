#pragma once
#include <oa.h>

/****************
*    PACKING    *
****************/

char *fill(BUFFER *inlet, LIST *windows)
{
    return NULL;
}

int find_prefix(LIST *windows, char *view)
{
    return 0;
}

char last_char(char *view)
{
    return '\0';
}

void write_node(BUFFER *out, int index, char last)
{

}

/*
LZ78 algorithm
At the start, the dictionary and P are empty;
C := next character in the charstream;
Is the string P+C present in the dictionary?
    if it is, P := P+C (extend P with C);
    if not,
        output these two objects to the codestream:
            the code word corresponding to P,
            C, in the same form as input from the charstream;
        add the string P+C to the dictionary;
        P := empty;
        are there more characters in the charstream?
        if yes, return to step 2;
        if not:
            if P is not empty, output the code word corresponding to P;
            END.
*/
void LZ78(char *input, char *output)
{
    BUFFER *inlet = buffer_new(input, "r", 256);
    BUFFER *outlet = buffer_new(output, "w", 256);
    char* view = string_new();
    LIST* windows = list_new();

    view = fill(inlet, windows);
    while (buffer_is_available(inlet))
    {

        write_node(outlet,
                   find_prefix(windows, view),
                   last_char(view));
        push(windows, view);
        view  = fill(inlet, windows);
    }

    free(view);
    list_free(windows);
    buffer_close(inlet);
    buffer_close(outlet);
}

/******************
*    UNPACKING    *
******************/

void unLZ78(char *input, char *output)
{
    return;
}

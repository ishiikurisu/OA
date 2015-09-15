#pragma once
#include <stdlib.h>
#include <oa.h>

/****************
*    PACKING    *
****************/

char *fill(BUFFER *inlet, LIST *windows)
{
    char *view = string_new();

    do {
        cat(view, ctos(buffer_read(inlet)));
    }
    while (list_contains(windows, view));

    return view;
}

int find_prefix(LIST* windows, char* view)
{
    char* to_find = NULL;
    int index = -1;

    if (view != NULL)
    {
        to_find = substring(view, 0, strlen(view) - 1);
        if (strlen(to_find) > 1)
            index = list_find(windows, to_find);
        free(to_find);
    }

    return index + 1;
}

void write_node(BUFFER *out, int index, char last)
{
    printf("%d %c\n", index, last);
    fwrite(&index, sizeof(int), 1, out->stream);
    fwrite(&last, sizeof(char), 1, out->stream);
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
    char* view = NULL;
    LIST* windows = list_new();

    printf("--- # compressing\n");
    view = fill(inlet, windows);
    while (buffer_is_available(inlet))
    {
        write_node(outlet,
                   find_prefix(windows, view),
                   last_char(view));
        push(windows, view);
        free(view);
        view = fill(inlet, windows);
    }

    free(view);
    list_free(windows);
    buffer_close(inlet);
    buffer_close(outlet);
    printf("...\n");
}

/******************
*    UNPACKING    *
******************/

char* get_node(BUFFER* inlet)
{
    char *message = NULL;
    int i;
    char c;

    fread(&i, sizeof(int), 1, inlet->stream);
    fread(&c, sizeof(char), 1, inlet->stream);
    message = itos(i);
    cat(message, " ");
    cat(message, ctos(c));

    return message;
}

char* decode(LIST* windows, char* coded)
{
    char *decoded = string_new();
    int index = 0;
    char to_add = ' ';
    char* msg = string_new();
    int i = 0;

    for (i = 0; coded[i] != ' '; ++i)
        cat(msg, ctos(coded[i]));

    sscanf(msg, "%d", &index);
    sscanf(coded, "%d %d", &i, &to_add);

    if (i)
        cat(decoded, list_get(windows, i - 1));
    cat(decoded, ctos(to_add));

    return decoded;
}

void unLZ78(char* input, char *output)
{
    BUFFER *inlet = buffer_new(input, "r", 512);
    BUFFER *outlet = buffer_new(output, "w", 512);
    char* coded_piece = NULL;
    char* decoded_piece = NULL;
    LIST* windows = list_new();

    while (!buffer_feof(inlet))
    {
        coded_piece = get_node(inlet);
        decoded_piece = decode(windows, coded_piece);
        buffer_write(outlet, decoded_piece);
        push(windows, decoded_piece);
        free(coded_piece);
        free(decoded_piece);
    }

    list_free(windows);
    buffer_close(inlet);
    buffer_close(outlet);
}

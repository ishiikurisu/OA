#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"

LIST* initialize_list(char* input_file)
{
    FILE* fp   = fopen(input_file, "r");
    LIST* list = new_list();
    char* data;
    char  read_char;

    while (!feof(fp))
    {
        data = "";
        fscanf(fp, "%c", &read_char);

        while (read_char != '\0'  && read_char != '\n')
        {
            data = concat(data, to_array(read_char));
            fscanf(fp, "%c", &read_char);
        }

        list = add_to_list(list, data);
    }

    list = remove_from_list(list, list_length(list) - 1);
    list = sort_list(list);
    
    fclose(fp);
    return list;
}

void write_output(LIST* list, char* output_file)
{
    FILE* fp   = fopen(output_file, "w");
    char* data = to_string_with_title(list, output_file);

    fprintf(fp, data);
    fflush(fp);
    fclose(fp);
}

void free_memory(LIST* list1, LIST* list2, LIST* output)
{
    free_list(list1);
    free_list(list2);
    free_list(output);
}

void main(int argc, char* argv[])
{
    LIST* list1  = initialize_list(argv[1]);
    LIST* list2  = initialize_list(argv[2]);
    LIST* output = match_on_RAM(list1, list2);
    
    write_output(output, argv[3]);
    free_memory(list1, list2, output);
}
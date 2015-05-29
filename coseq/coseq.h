char* read_from_file(FILE* fp)
{
    char* output = NULL;
    char  to_add = '\0';

    do {
        output = "";
        fscanf(fp, "%c", &to_add);

        while (to_add != '\0' && to_add != '\n')
        {
            output = concat(output, to_array(to_add));
            fscanf(fp, "%c", &to_add);
        }

    } while (strlen(output) == 0 && !feof(fp));

    if (strlen(output) == 0) output = NULL;

    return output;
}

void write_to_file(FILE* fp, char* to_write)
{
    fprintf(fp, "%s\n", to_write);
    fflush(fp);
}

/*
void sort_on_RAM(LIST* list)
{
    FILE* in  = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
}
*/

#define BUFFER_SIZE (10)
int build_runs(char* input)
{
    FILE* inlet       = fopen(input, "r");
    FILE* run         = NULL;
    LIST* subset      = NULL;
    char* data        = NULL;
    char* run_name    = NULL;
    int   added_files = 0;
    int   added_data  = 0;

    while (!feof(inlet))
    {
        subset     = new_list();
        data       = read_from_file(inlet);
        added_data = 0;

        while (data != NULL && !feof(inlet) && added_data < BUFFER_SIZE)
        {
            ++added_data;
            add_to_list(subset, data);
            data= read_from_file(inlet);
        }

        run_name = concat(input, to_array('0' + added_files));

        sort_list(subset);
        write_list_to_file(subset, run_name);
        ++added_files;
    }

    fclose(inlet);
    return added_files;
}
char* sort_on_memory(char* input)
{
    char*  output      = concat(input, ".sorted");
    int    added_files = 0;
    FILE*  run         = NULL;
    FILE** run_array   = NULL;
    FILE*  outlet      = fopen(output, "w");

    added_files = build_runs(input);

    /* merge runs */


    return output;
}

void match_on_memory(char* i1, char* i2, char* o)
{
    FILE* in1 = fopen(i1, "r");
    FILE* in2 = fopen(i2, "r");
    FILE* out = fopen(o,  "w");
    char* it1 = read_from_file(in1); /* do I use buffers or read */
    char* it2 = read_from_file(in2); /* each line at once? */

    while (it1 != NULL && it2 != NULL)
    {
        switch (compare(it1, it2))
        {
            case SMALLER:
                it1 = read_from_file(in1);
            break;

            case BIGGER:
                it2 = read_from_file(in2);
            break;

            default:
                write_to_file(out, it1);
                it1 = read_from_file(in1);
                it2 = read_from_file(in2);
        }
    }

    fclose(in1);
    fclose(in2);
    fclose(out);
}

LIST* match_on_RAM(LIST* list1, LIST* list2)
{
    LIST* output = new_list();
    int   index1 = 0;
    int   index2 = 0;
    char* item1  = get_from_list(list1, index1);
    char* item2  = get_from_list(list2, index2);

    while (item1 != NULL && item2 != NULL)
    {
        switch (compare(item1, item2))
        {
            case SMALLER:
                ++index1;
                item1 = get_from_list(list1, index1);
            break;

            case BIGGER:
                ++index2;
                item2 = get_from_list(list2, index2);
            break;

            default:
                add_to_list(output, item1);
                ++index1;
                ++index2;
                item1 = get_from_list(list1, index1);
                item2 = get_from_list(list2, index2);
        }
    }

    free_list(list1);
    free_list(list2);
    return output;
}

void merge_on_memory(char* i1, char* i2, char* o)
{

}

LIST* merge_on_RAM(LIST* list1, LIST* list2)
{
    LIST* output = NULL;

    /* merge this bitch*/

    return output;
}

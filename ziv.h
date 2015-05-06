/*
IMPLEMENTATION FUNCTIONS
*/
LIST* new_window()
{ return new_list(); }
 
int fill_conditions(char* view, LIST* windows, char* input, int i)
{
    int c1 = (contains(windows, view));
    int c2 = (i < strlen(input));
 
    return c1 && c2;
}
 
/*
AUXILIAR FUNCTIONS TO LZ78(char*)
*/
char* fill(int index, char* input, LIST* windows)
{
    char* view = "";
    int i = index + 1;
 
    view = concat(view, to_array(input[index]));
    while (fill_conditions(view, windows, input, i))
    {
        view = concat(view, to_array(input[i]));
        ++i;
    }
 
    return view;
}
 
int find_prefix(LIST* windows, char* view)
{
    char* to_find = "";
    int index = -1;
 
    if (view != NULL)
    {
        to_find = substring(view, 0, strlen(view) - 1);
        index = find_in_list(windows, to_find);
    }
 
    return index + 1;
}
 
char* build_node(int index, char postfix)
{
    int index_size   = ((int) log10(index + 0.1)) + 1;
    int postfix_size = 3;
    int need_memo    = index_size + postfix_size;
    char* node = (char*) malloc(sizeof(char) * (need_memo + 4));
 
    sprintf(node, "%d %d ", index, postfix);
 
    return node;
}
 
void free_memory(char* view, LIST* windows)
{
    free(view);
    free_list(windows);
}
 
void show(char* v, char* inp, int ind, char* out, LIST* win)
{
    char* list = to_string(win);
    int i;
 
    printf("\n---\n");
    printf("- current view: \"%s\"\n", v);
    printf("- added text: \n");
    for (i = 0; i < ind; ++i)
        printf("%c", inp[i]);
    printf("\n");
    printf("\n- code:\n  %s\n", out);
    printf("\n%s\n", list);
    printf("...\n");
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
char* LZ78(char* input)
{
    char* output = "";
    char* view = "";
    char* p;
    char x;
    int i, j;
    int index = 0;
    int limit = strlen(input);
    LIST* windows = new_window();
 
    view = fill(index, input, windows);
    while (index < limit)
    {
        i = find_prefix(windows, view);
        x = last_char(view);
        p = build_node(i, x);
 
        index  += strlen(view);
        output  = concat(output, p);
        windows = add_to_list(windows, view);
        view    = fill(index, input, windows);
    }
 
    printf("%s\n", to_string(windows));
    free_memory(view, windows);
    return output;
}

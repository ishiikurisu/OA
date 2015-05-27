char* get_node(char* input)
{
    char* message    = "";
    int i, j;
 
    for (i = 0, j = 0; j < 2; ++j)
    {
       while (input[i] != ' ')
       {
            message = concat(message, to_array(input[i]));
            i++;
       }
       message = concat(message, to_array(input[i]));
       i++;
    }
 
    return message;
}
 
char* decode(LIST* windows, char* coded)
{
    char* decoded    = "";
    int   index      = 0;
    char  to_add     = ' ';
 
    char* msg = "";
    int i = 0;
    while (coded[i] != ' ')
    {
        msg = concat(msg, to_array(coded[i]));
        i++;
    }
     
    sscanf(msg, "%d", &index);
    sscanf(coded, "%d %d", &i, &to_add);
 
    if (i)
        decoded = concat(decoded, get_from_list(windows, i - 1));
    decoded = concat(decoded, to_array(to_add));
 
    return decoded;
}
 
char* update_input(char* input, char* to_remove)
{
    int size_to_remove = strlen(to_remove);
    int size_to_keep   = strlen(input);
 
    return substring(input, size_to_remove, size_to_keep);
}
 
char* unLZ78(char* inlet)
{
    char* input = inlet;
    char* output = "";
    char* coded_piece;
    char* decoded_piece;
    LIST* windows = new_window();
     
    while (strlen(input) > 0)
    {
        coded_piece   = get_node(input);
        decoded_piece = decode(windows, coded_piece);
        output        = concat(output, decoded_piece);
        windows       = add_to_list(windows, decoded_piece);
        input         = update_input(input, coded_piece);
    }
 
    free_memory(decoded_piece, windows);
    return output;
}

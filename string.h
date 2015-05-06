int strlen(char* s)
{
    int i = 0;
    if (s) while (s[i]) ++i;
    return i;
}
 
char* concat(char* string, char* to_add)
{
    char* new_str;
    int len;
    int i, j;
 
    len = strlen(string);
    new_str = (char*) malloc(sizeof(char) * (len + 2));
 
    for (i = 0, j = 0; i < len; ++i, ++j)
        new_str[j] = string[i];
    for (i = 0; i <= strlen(to_add); ++i, ++j)
        new_str[j] = to_add[i];
 
    return new_str;
}
 
char* to_array(char ch)
{
    char* out = (char*) malloc(sizeof(char) * 2);
    out[0] = ch;
    out[1] = '\0';
    return out;
}
 
char* substring(char* string, int start, int end)
{
    int i;
    int gap = end - start;
    char* sub = (char*) malloc(sizeof(char) * (gap + 1));
 
    for (i = 0; i < gap; ++i)
        sub[i] = string[start + i];
    sub[i] = '\0';
 
    return sub;
}
 
int equals(char* s1, char* s2)
{
    int output = 0;
    int len = strlen(s1);
    int i = -1;
 
    if (strlen(s1) == strlen(s2))
        for (i = 0; (i < len) && (s1[i] == s2[i]); ++i);
    if (i == len)
        output = 1;
 
    return output;
}
 
char last_char(char* string)
{ return string[strlen(string) - 1]; }

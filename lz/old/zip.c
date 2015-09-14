#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "string.h"
#include "lempel.h"
#include "ziv.h"
 
char* read_data(char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    char* data = "";
    char piece;
 
    while (!feof(fp))
    {
        fscanf(fp, "%c", &piece);
        data = concat(data, to_array(piece));
    }
    data = concat(data, to_array(EOF));
 
    fclose(fp);
    return data;
}
 
char* process_data(char* data)
{
    return LZ78(data);
}
 
void write_data(char* file_name, char* data)
{
    FILE* fp = fopen(file_name, "w");
    fprintf(fp, "%s", data);
    fflush(fp);
    fclose(fp);
}
 
int main(int argc, char* argv[])
{
    char* input;
    char* output;
    char* data;
 
    input = argv[1];
    output = argv[2];
 
    data = read_data(input);
    data = process_data(data);
    write_data(output, data);
 
    return 0;
}

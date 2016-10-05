#ifndef COSEQ_H
#define COSEQ_H 0
#include "list.h"

char* read_from_file(FILE* fp);
char* get_line_from_file(FILE* inlet, int line_number);
char* get_line(char* input, int line_number);
LIST* read_whole_file(char* input_file);
void write_to_file(FILE* fp, char* to_write);
void sort_on_RAM(char* input_file, char* output_file);
#define BUFFER_SIZE (10)
int build_runs(char* input);
void match_on_memory(char* i1, char* i2, char* o);
LIST* match_on_RAM(LIST* list1, LIST* list2);
void merge_on_memory(char* i1, char* i2, char* o);
LIST* merge_on_RAM(LIST* list1, LIST* list2);
#endif

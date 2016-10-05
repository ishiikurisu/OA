#ifndef JOE_STRING_H
#define JOE_STRING_H 0
#include <stdbool.h>

char* string_new();
char* old_concat(char* string, char* to_add);
char* concat(char* to_hold, char* to_add);
char *CAT_MACRO(char *to_hold, char *to_add);
char *APE_MACRO(char *to_hold, char *to_add);

#define cat(A,B) ((A)=CAT_MACRO((A), (B)))
#define ape(A,B) ((A)=APE_MACRO((A), (B)))

char* to_array(char ch);
char* ctos(char ch);
char* int_to_string(int input);
char* itos(int number);
char* substring(char* string, int start, int end);
int equals(char* s1, char* s2);
int compare(char* s, char* t);
bool whitespace(char c);
bool match(const char *s, const char *t);
char* tidy_string(char *str);
char last_char(char* string);

#endif

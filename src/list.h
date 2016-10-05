#ifndef LIST_H
#define LIST_H

typedef struct NODE
{
    struct NODE* next;
    char* key;
    char* value;
} NODE;

typedef NODE LIST;

LIST* list_new();
LIST* new_list();
LIST* tail(LIST* head);
int list_length(LIST* head);
char* list_get(LIST* head, int index);
LIST* list_add(LIST* head, char* data);
LIST* list_add_at(LIST* head, char* data, int index);
LIST* associate(LIST* head, char* key, char* value);
int list_find(LIST* head, char* to_find);
char* pair_find(LIST* head, char* to_find);
char* list_to_string(LIST* head);
char* list_yaml_with_title(LIST* head, char* title);
char* list_yaml(LIST* head);
void write_list_to_file(LIST* head, char* output);
char* pair_to_string(LIST* head);
void list_print(LIST* head);
int list_contains(LIST* head, char* to_find);
LIST* using_bubblesort(LIST* head, int(*function)(int));
int is_bigger(int result);
LIST* list_sort(LIST* head);
char* list_pop(LIST* head);
LIST* list_push(LIST* head, char* item);
LIST* list_remove(LIST* head, int index);
char* pair_delete(LIST* head, char* to_find);
void list_free(LIST* head);
LIST* list_filter(LIST *list, bool (*func)(char*));
LIST* list_strsplit(char* string, char to_divide);

#endif

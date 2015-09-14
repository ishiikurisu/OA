#define inc(A) ((A) = (A)->next)
 
typedef struct NODE
{
    struct NODE* next;
    char* info;
}
NODE;
 
typedef NODE LIST;
 
LIST* new_list()
{
    LIST* list = (LIST*) malloc(sizeof(LIST));
 
    list->next = NULL;
    list->info = NULL;
 
    return list;
}
 
LIST* tail(LIST* head)
{
    LIST* list = head;
 
    while (list->next != NULL)
        list = list->next;
 
    return list;
}
 
char* get_from_list(LIST* head, int index)
{
    LIST* list = head->next;
    char* outlet = NULL;
    int i = 0;
 
    while ((i != index) && (list != NULL))
    {
        inc(list);
        ++i;
    }
 
    if (list != NULL)
        outlet = list->info;
 
    return outlet;
}
 
LIST* add_to_list(LIST* head, char* data)
{
    LIST* new_node = new_list();
    LIST* list = tail(head);
 
    new_node->info = data;
    list->next = new_node;
 
    return head;
}
 
int find_in_list(LIST* head, char* to_find)
{
    LIST* list = head->next;
    int outlet = -1;
    int index = 0;
 
    while ((list != NULL) && (outlet < 0))
    {
        if (equals(to_find, list->info))
            outlet = index;
 
        ++index;
        inc(list);
    }
 
    return outlet;
}
 
char* to_string(LIST* head)
{
    LIST* list = head->next;
    char* outlet = "";
 
    outlet = concat(outlet, "---\n- list:\n");
    while (list != NULL)
    {
        outlet = concat(outlet, "  - ");
        outlet = concat(outlet, list->info);
        outlet = concat(outlet, "\n");
        inc(list);
    }
 
    outlet = concat(outlet, "...\n");
    return outlet;
}
 
void print_list(LIST* head)
{
    LIST* list = head->next;
 
    printf("---\n");
    printf("- list:\n");
    while (list != NULL)
    {
        if (list->info != NULL)
            printf("  - %s\n", list->info);
        else
            printf("  - NULL\n");
        inc(list);
    }
    printf("...\n");
}
 
int contains(LIST* head, char* to_find)
{
    LIST* list = head->next;
    int result = 0;
 
    while ((list != NULL) && (result == 0))
    {
        result = equals(to_find, list->info);
        inc(list);
    }
 
    return result;
}
 
void free_list(LIST* head)
{
    LIST* list = head;
    LIST* memo;
 
    while (list->next != NULL)
    {
        memo = list->next;
        free(list);
        list = memo;
    }
 
    free(list);
}

# string

Definitions
===========

+ int BIGGER  = +1
+ int SMALLER = -1
+ int EQUAL   = 0

Methods
=======

+ int strlen(char*)
+ char* concat(char*, char*)
+ char* to_array(char)
+ char* substring(char*, int, int)
+ int equals(char*, char*)
+ int compare(char*, char*)
+ char last_char(char*)

# list

Definitions
===========

+ struct NODE
+ LIST

Methods
=======

+ LIST* new_list()
+ LIST* tail(LIST*)
+ int list_length(LIST*)
+ char* get_from_list(LIST*, int)
+ LIST* add_to_list(LIST*, char)
+ int find_in_list(LIST*, char*)
+ char* to_string(LIST*)
+ void print_list(LIST*)
+ int contains(LIST*,char*)
+ LIST* sort_list(LIST*)
+ char* pop_from_list(LIST*)
+ void push_to_list(LIST*, char*)
+ LIST* renove_from_list(LIST*, int)
+ void free_list(LIST*)
+ LIST* split(char*, char)

# coseq

+ char* read_from_file(FILE*)
+ LIST* read_whole_file(char*)
+ void write_to_file(char*)
+ void sort_on_RAM(char*, char*)
+ void match_on_memory(char*, char*, char*)
+ LIST* match_on_RAM(LIST*, LIST*)
+ void merge_on_memory(char*, char*, char*)
+ LIST* merge_on_RAM(LIST*, LIST*)

# btreenode

Definitions
===========

+ struct BTREE_NODE
+ typedef BTREE_NODE BTND
+ struct BTREE

Methods
=======

+ BTND* alloc_nodes()
+ BTND* new_btree_node(char*, char*)
+ BTREE* alloc_btree()
+ BTREE* new_btree()
+ BTREE* add_to_btree(BTREE*, BTND*)
+ void print_btree(BTREE*)
+ BTREE* load_btree(char*)
+ void free_btree(BTREE*)

# btree

Methods
=======

+ BTREE* get_leaf(BTREE* parent, BTND* node)
+ BTREE* insert(BTREE*, BTND*)

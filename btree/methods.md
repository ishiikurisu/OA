# string

Definitions
-----------

+ int BIGGER  = +1
+ int SMALLER = -1
+ int EQUAL   = 0

Methods
-------

+ int strlen(char*)
+ char* concat(char*, char*)
+ char* to_array(char)
+ char* substring(char*, int, int)
+ int equals(char*, char*)
+ int compare(char*, char*)
+ char last_char(char*)

# list

Definitions
-----------

+ struct NODE
+ LIST

Methods
-------

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
+ LIST* remove_from_list(LIST*, int)
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
-----------

+ typedef INDEX_NODE INND
+ typedef BTREE_NODE BTND
+ define PAGE_TYPE
+ define NODE_TYPE
+ typedef BTREE BT

Methods
-------

+ INND* new_index_node()
+ BTND* new_btnode()
+ BTND* last_node(BTND*)
+ BTND* create_node(char*,char*)
+ BTND* add_btnode(BTND*,char*,char*)
+ BTND* add_to_btnode_at_index(BTND*,char*,char*,int)
+ char* get_key(BTND*)
+ char* get_value(BTND*)
+ char* get_value_from_key(BTND*,char*)
+ int number_bnodes(BTND*)
+ INND* remove_from_btnode(BTND*,int)
+ BTREE* new_btree()
+ BTREE* create_btree(char*)
+ BTREE* add_bnode_to_btree_in_order(BTREE*,BTND*)
+ BTREE* add_bnode_to_btree(BTREE*,BTND*)
+ BTREE* add_node_to_btree(BTREE*,char*,char*)
+ BTREE* add_page_to_btree(BTREE*,char*)
+ bool contains_node(BTREE*,BTND*)
+ int find_place_to_fit(NTREE*,BTND*)
+ BTREE* load_btree(char*)
+ void save_btree(BTREE*)
+ void write_btree(BTREE*)

# btree

Definitions
-----------

+ define PAGE_SIZE
+ struct __divided__

Methods
-------

+ bool is_leaf(BTREE*)
+ BTREE* get_leaf(BTREE*,BTND*)
+ BTREE* get_node_parent(BTREE*,BTND*)
+ BTREE* get_btree_parent(BTREE*,BTREE*)
+ divided* alloc_struct_divided()
+ divided* divide(BTREE*)
+ BTND* promote(BTREE*)
+ bool overflow(BTREE*)
+ BTREE* update(BTREE*,BTREE*,BTREE*)
+ BTREE* divide_and_promote(BTREE*,BTREE*)
+ BTREE* insert(BTREE*,BTND*)
+ char* get_from_btree(BTREE*,BTND*)
+ char* search_btree(BTREE*,char*)

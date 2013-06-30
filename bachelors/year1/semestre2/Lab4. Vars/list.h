#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

typedef string list_type;

struct List {
    list_type data;
    List *prev, *next;
};

List *create(list_type value);
List *insert_after (List *t, list_type value);
List *insert_before (List *t, list_type value);
List *find_by_value (List *t, list_type value);
List *find_by_id (List *t, int id);
List *get_prev (List *t);
List *get_next (List *t);
List *get_tail (List *t);
List *get_head (List *t);
List *delete_node (List *&t);
list_type get_value (List *t);
bool swap_values(List *a, List *b);
bool clear_list (List *&t);
List *insert_list (List *dest, List *source);
List *cut_list (List *from, List *to);
List *union_list (List *a, List *b);
List *copy_list (List *from, List *to);
bool destroy (List *&t);
void print (List *t);
int get_id (List *t);
bool is_last(List *t);
bool is_first(List *t);

#endif //LIST_INCLUDED

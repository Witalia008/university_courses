#ifndef TREE_H
#define TREE_H

#include "../../tools.h"
#include "node.h"
#include "../vars/variables.h"

struct Tree {
    struct List {
        Tree *data;
        List *prev, *next;
    };
    Node_data data;
    List *sons;
    Tree *father;
};


/* Functions for TREE */

Tree *create_tree(Node_data val);
Tree *create_tree(Node_data val, Tree *l, Tree *r);
Tree *get_son(Tree *father, int id);
Tree *get_father(Tree *son);
Node_data get_val(Tree *t);
Tree *add_son(Tree *t, Node_data val);
void add_subtree(Tree *t, Tree *subt);
Tree *find_by_val(Tree *root, Node_data &val);
bool delete_subtree(Tree *t);//to be done
bool is_leaf(Tree *t);
bool straigh_trav(Tree *t, bool f(Tree*));
bool reverse_trav(Tree *t, bool f(Tree*));
bool k_symm_trav(Tree *t, int k, bool f(Tree*));
bool swap_sons(Tree *t, int id1, int id2);
bool swap_subtrees(Tree *t1, Tree *t2);//not needed
int count_if(Tree *t, bool f(Tree*));
Tree *LCA(Tree *t1, Tree *t2); //not needed


/* Functions for LIST */

Tree::List *create(Tree *value);
Tree::List *insert_after (Tree::List *t, Tree *value);
Tree::List *insert_before (Tree::List *t, Tree *value);
Tree::List *find_by_value (Tree::List *t, Tree *value);
Tree::List *find_by_id (Tree::List *t, int id);
Tree::List *get_prev (Tree::List *t);
Tree::List *get_next (Tree::List *t);
Tree::List *get_tail (Tree::List *t);
Tree::List *get_head (Tree::List *t);
Tree::List *delete_node (Tree::List *&t);
Tree *get_value (Tree::List *t);
bool swap_values(Tree::List *a, Tree::List *b);
bool clear_list (Tree::List *&t);
Tree::List *insert_list (Tree::List *dest, Tree::List *source);
Tree::List *cut_list (Tree::List *from, Tree::List *to);
Tree::List *union_list (Tree::List *a, Tree::List *b);
Tree::List *copy_list (Tree::List *from, Tree::List *to);
bool destroy (Tree::List *&t);
void print (Tree::List *t);
int get_id (Tree::List *t);
bool is_last(Tree::List *t);
bool is_first(Tree::List *t);


#endif //TREE_H

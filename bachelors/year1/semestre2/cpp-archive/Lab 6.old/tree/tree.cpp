#include "tree.h"

Tree *create_tree(Node_data val) {
    Tree *res = new Tree();
    res->data = val;
    res->sons = NULL;
    res->father = NULL;
    return res;
}

Tree *create_tree(Node_data val, Tree *l, Tree *r) {
    Tree *res = create_tree(val);
    if (l != NULL) {
        add_subtree(res, l);
    }
    if (r != NULL) {
        add_subtree(res, r);
    }
    return res;
}

Tree *get_son(Tree *father, int id) {
    Tree *res = NULL;
    if (father != NULL) {
        Tree::List *son = find_by_id(father->sons, id);
        res = son->data;
    }
    return res;
}

Tree *get_father(Tree *son) {
    Tree *res = NULL;
    if (son != NULL) {
        res = son->father;
    }
    return res;
}

Node_data get_val(Tree *t) {
    Node_data res;
    if (t != NULL) {
        res = t->data;
    }
    return res;
}

Tree *add_son(Tree *t, Node_data val) {
    Tree *res = NULL;
    if (t != NULL) {
        res = create_tree(val);
        t->sons = get_head(insert_after(get_tail(t->sons), res));
    }
    return res;
}

void add_subtree(Tree *t, Tree *subt) {
    if (t != NULL && subt != NULL) {
        t->sons = get_head(insert_after(get_tail(t->sons), subt));
        subt->father = t;
    }
}

Tree *find_by_val(Tree *root, Node_data &val) {
    Tree *res = NULL;
    if (root->data == val) {
        res = root;
    } else {
        for (Tree::List *i = root->sons; i == NULL && res == NULL; i = get_next(i)) {
            res = find_by_val(i->data, val);
        }
    }
    return res;
}

bool delete_subtree(Tree *t) {
    //To be done...
}

bool is_leaf(Tree *t) {
    return (t != NULL && t->sons == NULL);
}

bool straigh_trav(Tree *t, bool f(Tree*)) {
    bool success = f(t);
    if (t != NULL) {
        for (Tree::List *i = t->sons; i != NULL; i = get_next(i)) {
            success &= f(i->data);
        }
    }
    return success;
}

bool reverse_trav(Tree *t, bool f(Tree*))  {
    bool success = true;
    if (t != NULL) {
        for (Tree::List *i = t->sons; i != NULL; i = get_next(i)) {
            success &= f(i->data);
        }
    }
    return success && f(t);
}

bool k_symm_trav(Tree *t, int k, bool f(Tree*)) {
    bool success = true;
    if (t != NULL) {
        Tree::List *i = t->sons;
        for (int j = 0; j < 2; j++) {
            for (; i != NULL && (k > 0 || j > 0); i = get_next(i), --k) {
                success &= f(i->data);
            }
            if (j == 0) {
                success &= f(t);
            }
        }
    }
    return success;
}

bool swap_sons(Tree *t, int id1, int id2) {
    bool success = (t != NULL);
    if (t != NULL) {
        if (id1 > id2) {
            swap(id1, id2);
        }
        Tree::List *son1, *son2;
        son1 = son2 = t->sons;
        for (; id1 > 0 || id2 > 0; id1--, id2--) {
            if (id1 > 0 && son1 != NULL) {
                son1 = get_next(son1);
            }
            if (id2 > 0 && son2 != NULL) {
                son2 = get_next(son2);
            }
        }
        success &= swap_values(son1, son2);
    }
    return success;
}

int count_if(Tree *t, bool f(Tree*)) {
    int count = 0;
    if (t != NULL) {
        count += f(t);
        for (Tree::List *i = t->sons; i != NULL; i = get_next(i)) {
            count += count_if(i->data, f);
        }
    }
    return count;
}

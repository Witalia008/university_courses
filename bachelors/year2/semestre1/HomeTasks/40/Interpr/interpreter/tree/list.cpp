#include "tree.h"

/*
 *  This function creates new Tree::List with some value
 */
Tree::List * create (Tree *value) {
    Tree::List * res = new Tree::List();
    res->prev = res->next = 0;
    res->data = value;
    return res;
}

/*
 * Inserts element after current and returns
 * pointer on inserted element
 */
Tree::List * insert_after (Tree::List *t, Tree *value) {
    Tree::List * res = create (value);
    if (t) {
        res->next = t->next;
        if (t->next)
            t->next->prev = res;
        t->next = res;
        res->prev = t;
    }
    return res;
}

/*
 * Inserts element before current and returns
 * pointer on inserted element
 */
Tree::List * insert_before (Tree::List *t, Tree *value) {
    Tree::List * res = create (value);
    if (t) {
        res->prev = t->prev;
        if (t->prev)
            t->prev->next = res;
        res->next = t;
        t->prev = res;
    }
    return res;
}

/*
 * Given a value. Returns pointer on element in Tree::List with this value.
 */
Tree::List * find_by_value (Tree::List *t, Tree *value) {
    while (t) {
        if (t->data == value)
            return t;
        t = t->next;
    }
    return 0;
}

/*
 * Returns pointer on previous element.
 */
Tree::List *get_prev (Tree::List *t) {
    if (t)
        t = t->prev;
    return t;
}

/*
 * Returns pointer on next element.
 */
Tree::List *get_next (Tree::List *t) {
    if (t)
        t = t->next;
    return t;
}

/*
 * Returns pointer on tail of the list.
 */
Tree::List *get_tail (Tree::List *t) {
    if (!t)
        return 0;
    while (t->next)
        t = t->next;
    return t;
}

/*
 * Deletes element from Tree::List and returns pointer on this el. for next use.
 */
Tree::List *delete_node (Tree::List *&t) {
    if (!t)
        return 0;
    Tree::List *p = t;
    if (t->prev)
        t->prev->next = t->next;
    if (t->next)
        t->next->prev = t->prev;
    p->prev = p->next = 0;
    return p;
}

/*
 * Returns value of element.
 */
Tree *get_value (Tree::List *t) {
    if (!t)
        return 0;
    return t->data;
}

/*
 * Function deletes all elements from Tree::List and clears memory.
 */
bool clear_list (Tree::List *&t) {
    if (!t)
        return false;
    t = get_head(t);
    while (t->next) {
        Tree::List *p = t->next->next;
        if (!destroy(t->next))
            return false;
        t->next = p;
    }
    if (!destroy(t))
        return false;
    t = 0;
    return true;
}

/*
 * Returns pointer on id-th element.
 */
Tree::List *find_by_id (Tree::List *t, int id) {
    while (id && t) {
        t = get_next(t);
        id--;
    }
    return t;
}

/*
 * If elements a and b exist then function swaps their values.
 */
bool swap_values (Tree::List *a, Tree::List *b) {
    if (a && b) {
        swap(a->data, b->data);
        return true;
    }
    return false;
}

/*
 * Returns pointer on head of the list
 */
Tree::List *get_head (Tree::List *t) {
    while (t && t->prev)
        t = get_prev(t);
    return t;
}

/*
 * Inserts some Tree::List and returns pointer on head of new list.
 */
Tree::List *insert_list(Tree::List *dest, Tree::List *source) {
    if (dest && source) {
        Tree::List *p = get_tail(source);
        p->next = dest->next;
        if (dest->next)
            dest->next->prev = p;
        dest->next = source;
        source->prev = dest;
        return get_head(dest);
    } else {
        return dest ? dest : source;
    }
}

/*
 * Cuts part of Tree::List from..to
 */
Tree::List *cut_list (Tree::List *from, Tree::List *to) {
    if (from && to) {
        if (from->prev)
            from->prev->next = to->next;
        if (to->next)
            to->next->prev = from->prev;
        to->next = from->prev = 0;
        return from;
    } else {
        return 0;
    }
}

/*
 * Inserts Tree::List b after Tree::List a. Returns pointer of head.
 */
Tree::List *union_list(Tree::List *a, Tree::List *b) {
    if (a && b) {
        Tree::List *p1 = get_tail(a);
        Tree::List *p2 = get_head(b);
        p1->next = p2;
        p2->prev = p1;
        return get_head(p1);
    } else {
        return a ? a : b;
    }
}

/*
 * Creates new Tree::List with elements from..to and returns a pointer on head of new list.
 */
Tree::List *copy_list (Tree::List *from, Tree::List *to) {
    Tree::List * res = 0;
    while (from != to) {
        res = insert_after(res, get_value(from));
        from = get_next (from);
    }
    return get_head(res);
}

/*
 * Deletes some element and frees memory.
 */
bool destroy (Tree::List *&t) {
    if (t) {
        delete t;
        t = 0;
        return true;
    } else {
        return false;
    }
}

/*
 * Outputs all values to stdout.
 */
void print (Tree::List *t) {
    while (t) {
        //printf ("%.6lf\n", t->data);
        cout << t->data << endl;
        t = get_next(t);
    }
    printf ("\n");
}

/*
 * Returns number in order.
 */
int get_id (Tree::List *t) {
    int res = -1;
    while (t) {
        res++;
        t = get_prev(t);
    }
    return res;
}

bool is_last(Tree::List *t) {
    return (t && get_next(t));
}

bool is_first(Tree::List *t) {
    return (t && get_prev(t));
}

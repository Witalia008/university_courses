#include "list.h"

/*
 *  This function creates new list with some value
 */
List * create (list_type value) {
    List * res = new List();
    res->prev = res->next = 0;
    res->data = value;
    return res;
}

/*
 * Inserts element after current and returns
 * pointer on inserted element
 */
List * insert_after (List *t, list_type value) {
    List * res = create (value);
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
List * insert_before (List *t, list_type value) {
    List * res = create (value);
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
 * Given a value. Returns pointer on element in list with this value.
 */
List * find_by_value (List *t, list_type value) {
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
List *get_prev (List *t) {
    if (t)
        t = t->prev;
    return t;
}

/*
 * Returns pointer on next element.
 */
List *get_next (List *t) {
    if (t)
        t = t->next;
    return t;
}

/*
 * Returns pointer on tail of the list.
 */
List *get_tail (List *t) {
    if (!t)
        return 0;
    while (t->next)
        t = t->next;
    return t;
}

/*
 * Deletes element from list and returns pointer on this el. for next use.
 */
List *delete_node (List *&t) {
    if (!t)
        return 0;
    List *p = t;
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
list_type get_value (List *t) {
    if (!t)
        return 0;
    return t->data;
}

/*
 * Function deletes all elements from list and clears memory.
 */
bool clear_list (List *&t) {
    if (!t)
        return false;
    t = get_head(t);
    while (t->next) {
        List *p = t->next->next;
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
List *find_by_id (List *t, int id) {
    while (id && t) {
        t = get_next(t);
        id--;
    }
    return t;
}

/*
 * If elements a and b exist then function swaps their values.
 */
bool swap_values (List *a, List *b) {
    if (a && b) {
        swap(a->data, b->data);
        return true;
    }
    return false;
}

/*
 * Returns pointer on head of the list
 */
List *get_head (List *t) {
    while (t && t->prev)
        t = get_prev(t);
    return t;
}

/*
 * Inserts some list and returns pointer on head of new list.
 */
List *insert_list(List *dest, List *source) {
    if (dest && source) {
        List *p = get_tail(source);
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
 * Cuts part of list from..to
 */
List *cut_list (List *from, List *to) {
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
 * Inserts list b after list a. Returns pointer of head.
 */
List *union_list(List *a, List *b) {
    if (a && b) {
        List *p1 = get_tail(a);
        List *p2 = get_head(b);
        p1->next = p2;
        p2->prev = p1;
        return get_head(p1);
    } else {
        return a ? a : b;
    }
}

/*
 * Creates new list with elements from..to and returns a pointer on head of new list.
 */
List *copy_list (List *from, List *to) {
    List * res = 0;
    while (from != to) {
        res = insert_after(res, get_value(from));
        from = get_next (from);
    }
    return get_head(res);
}

/*
 * Deletes some element and frees memory.
 */
bool destroy (List *&t) {
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
void print (List *t) {
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
int get_id (List *t) {
    int res = -1;
    while (t) {
        res++;
        t = get_prev(t);
    }
    return res;
}

bool is_last(List *t) {
    return (t && get_next(t));
}

bool is_first(List *t) {
    return (t && get_prev(t));
}

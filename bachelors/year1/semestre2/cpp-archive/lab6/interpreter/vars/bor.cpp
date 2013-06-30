#include "bor.h"

Bor *find_add(Bor *root, string word, bool need_add) {
    Bor *res = root;
    for (int i = 0; i < word.size() && res != NULL; i++) {
        if (res->next[word[i]] == NULL) {
            if (need_add == true) {
                res->next[word[i]] = new Bor();
            } else {
                res = NULL;
                break;
            }
        }
        res = res->next[word[i]];
    }
    return res;
}

void set_value(Bor *root, List *var) {
    Bor *where = find_add(root, var->data.name, true);
    where->var = var;
}

void sub_tree_out(Bor *v, ostream &out) {
    if (v == NULL) {
        return;
    }
    if (v->var != NULL) {
        out << v->var->data.name << " = " << v->var->data.value << endl;
    }
    for (map<int, Bor*>::iterator i = v->next.begin(); i != v->next.end(); i++) {
        sub_tree_out(i->second, out);
    }
}

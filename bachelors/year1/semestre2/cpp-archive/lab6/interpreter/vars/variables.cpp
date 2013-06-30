#include "variables.h"

var_set get_from_file(istream &inp) {
    var_set res;
    res.vars = NULL;
    res.trie = new Bor();
    for (;;) {
        list_type cur_var;
        cur_var.name = cur_var.value = "";
        if (inp.eof()) {
            break;
        }
        inp >> cur_var.name >> cur_var.value >> cur_var.value;
        if (cur_var.name == "") {
            break;
        }
        add_var(res, cur_var);
    }
    return res;
}

var_set get_from_file(string file_name) {
    ifstream fin(file_name.c_str());
    var_set res = get_from_file(fin);
    fin.close();
    return res;
}

void check_namespace(string &s) {
    if (s.find("::") == -1) {
        s = "main::" + s;
    }
}

List *find_variable(var_set t, string var_name) {
    check_namespace(var_name);
    Bor *where = find_add(t.trie, var_name, false);
    if (where != NULL) {
        return where->var;
    } else {
        return NULL;
    }
}

bool add_var(var_set &t, list_type value) {
    check_namespace(value.name);
    Bor *where = find_add(t.trie, value.name, false);
    bool was_added = false;
    if (where == NULL) {
        was_added = true;
        t.vars = insert_before(t.vars, value);
        set_value(t.trie, t.vars);
    }
    return was_added;
}

void set_var(var_set &t, list_type var) {
    check_namespace(var.name);
    t.vars = insert_before(t.vars, var);
    set_value(t.trie, t.vars);
}

string variable_value(var_set t, string name) {
    string res = "";
    check_namespace(name);
    Bor *wh = find_add(t.trie, name, false);
    if (wh != NULL && wh->var != NULL) {
        res = wh->var->data.second;
    }
    return res;
}

void out_to_file(var_set t, ostream &out) {
    sub_tree_out(t.trie, out);
}

void out_to_file(var_set t, string filename) {
    ofstream out (filename.c_str());
    out_to_file(t, out);
    out.close();
}

void out_from_namesp(var_set t, string namesp, ostream &out) {
    t.trie = find_add(t.trie, namesp, false);
    if (t.trie != NULL) {
        sub_tree_out(t.trie, out);
    }
}

var_set *set_namesp(var_set *t, string namesp) {
    var_set *res = new var_set();
    res->vars = t->vars;
    res->trie = find_add(t->trie, namesp, true);
    return res;
}

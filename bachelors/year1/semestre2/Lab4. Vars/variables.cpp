#include "variables.h"

var_set get_from_file (string filename) {
    ifstream inp (filename.c_str());
    var_set res;
    res.name = res.value = 0;
    for (;;) {
        list_type name, val;
        name = val = "";
        inp >> name >> val;
        if (name == "") break;
        add_var(res, name, val);
    }
    res.name = get_head(res.name);
    res.value = get_head(res.value);
    return res;
    inp.close();
}

list_type get_namespace (list_type name) {
    list_type namesp = "main::";
    if (name.find("::") != -1) {
        namesp = name;
        while (namesp.size() > 2 && (namesp[namesp.size()-1] != ':' || namesp[namesp.size()-2] != ':'))
            namesp.erase (namesp.size() - 1, 1);
    }
    return namesp;
}

var_set find_variable(var_set t, list_type name) {
    while (t.name && get_value(t.name) != name) {
        t.name = get_next(t.name);
        t.value = get_next(t.value);
    }
    return t;
}

bool add_var (var_set &t, list_type name, list_type val) {
    if (name.find("::") == -1)
        name = "main::" + name;
    if (find_variable(t, name).name != 0)
        return false;
    t.name = get_head(insert_after(t.name, name));
    t.value = get_head(insert_after(t.value, val));
    return true;
}

bool set_var (var_set &t, list_type name, list_type val) {
    if (name.find("::") == -1)
        name = "main::" + name;
    t = find_variable(t, name);
    if (t.name == 0)
        return false;
    t.value->data = val;
    return true;
}

void out_to_file (var_set t, string filename) {
    t.name = get_head(t.name);
    t.value = get_head(t.value);
    ofstream out (filename.c_str());
    while (t.name) {
        out << get_value(t.name) <<  " " << get_value(t.value) << endl;
        t.name = get_next(t.name);
        t.value = get_next(t.value);
    }
    out.close();
}

bool is_good_variable (list_type name) {
    string can_use = "1234567890_qwertyuioplkjhgfdsazxcvbnmZXCVBNMASDFGHJKLPOIUYTREWQ";
    for (int i = 0; i < name.size(); i++)
        if (can_use.find(name[i]) == -1)
            return false;
    return name != "" && (name[0] < '0' || name[0] > '9');
}

void out_by_namespace(var_set t, string filename) {
    ofstream out (filename.c_str());
    List * used = 0;
    while (t.name) {
        list_type namesp = get_namespace(get_value(t.name));
        if (find_by_value(used, namesp) == 0) {
            used = insert_before(used, namesp);
            out << namesp << endl;
            var_set r1 = get_from_namesp(t, namesp);
            while (r1.name) {
                r1.name->data.erase(0, namesp.size());
                out << get_value(r1.name) << " " << get_value(r1.value) << endl;
                r1.name = get_next(r1.name);
                r1.value = get_next(r1.value);
            }
            clear_list(r1.name);
            clear_list(r1.value);
        }
        t.name = get_next(t.name);
        t.value = get_next(t.value);
    }
    clear_list(used);
    out.close();
}

var_set get_from_namesp (var_set t, list_type name) {
    var_set res;
    res.name = res.value = 0;
    t.name = get_head(t.name);
    t.value = get_head(t.value);
    while (t.name) {
        if (get_namespace(get_value(t.name)) == name)
            add_var(res, get_value(t.name), get_value(t.value));
        t.name = get_next(t.name);
        t.value = get_next(t.value);
    }
    return res;
}

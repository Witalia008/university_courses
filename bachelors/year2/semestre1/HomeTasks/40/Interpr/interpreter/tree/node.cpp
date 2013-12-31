#include "node.h"

Node_data get_value(Node_data arg0) {
    Node_data res = arg0;
    if (arg0.type == Variable) {
        //cout << *arg0.str_val << endl;
        string value = variable_value(*arg0.var_val, *arg0.str_val);
        res = Node_data(get_type(value), value);
    }
    if (arg0.type == Return || arg0.type == Break) {
        if (is_string(*arg0.str_val))
            res.type = String;
        else {
            res = Node_data(Number, *arg0.str_val);
        }
    }
    return res;
}

double to_number(Node_data a) {
    double res = 0;
    if (a.type == Number) {
        res = a.d_val;
    } else if (a.type == Boolean) {
        res = (*a.str_val == "true");
    } else if (a.type == Char) {
        res = a.ch_val;
    }
    return res;
}

int to_int(Node_data a) {
    return int(to_number(a));
}

Node_data from_int(int a, Data_type _type) {
    Node_data res;
    res.type = _type;
    if (_type == String) {
        res.str_val = new string(toStr(a));
    } else if (_type == Char) {
        res.ch_val = a;
    } else if (_type == Number) {
        res.d_val = a;
    } else if (_type == Boolean) {
        res.str_val = new string(a ? "true" : "false");
    }
    return res;
}

string to_str(Node_data a) {
    string res;
    a = get_value(a);
    if (a.type == String || a.type == Boolean) {
        res = *a.str_val;
    } else if (a.type == Number) {
        res = toStr(a.d_val);
    } else if (a.type == Char) {
        res = "' '";
        res[1] = a.ch_val;
    }
    return res;
}

Data_type get_type(string a) {
    Data_type res;
    if (is_number(a)) {
        res = Number;
    } else if (is_string(a)) {
        res = String;
    } else if (is_char(a)){
        res = Char;
    } else {
        res = Boolean;
    }
    return res;
}

string to_clr_str(Node_data a) {
    string res = to_str(a);
    if (res != "" && (res[0] == '"' || res[0] == '\'')) {
        res.erase(0, 1);
    }
    if (res != "" && (res[res.size() - 1] == '"' || res[res.size() - 1] == '\'')) {
        res.erase(res.size() - 1, 1);
    }
    return res;
}

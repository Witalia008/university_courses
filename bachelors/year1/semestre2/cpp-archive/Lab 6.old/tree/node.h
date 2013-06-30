#ifndef NODE_H
#define NODE_H

#include "../tools.h"
#include "../vars/variables.h"

enum Data_type {
    Number, Boolean, String, Char, Variable, Oper, Func
};

struct Node_data {
    Data_type type;
    union {
        double d_val;
        char ch_val;
        string *str_val;
    };
    var_set *var_val;
    Node_data() {}
    Node_data(Data_type _type, string value) {
        type = _type;
        if (_type == Number) {
            d_val = fromStr(value);
        } else if (_type == Char) {
            del_spec_symbs(value);
            ch_val = value[1];
        } else {
            str_val = new string(value);
        }
    }
    Node_data(string _name, var_set *vars) {
        type = Variable;
        var_val = vars;
        str_val = new string(_name);
    }
    bool operator == (Node_data b) {
        bool equal = type = b.type;
        if (equal) {
            if (type == Number) {
                equal &= d_val == b.d_val;
            } else {
                equal &= str_val == b.str_val;
            }
        }
        return equal;
    }
};

Node_data get_value(Node_data);
double to_number(Node_data a);
Data_type get_type(string a);
int to_int(Node_data a);
Node_data from_int(int a, Data_type);
string to_str(Node_data a);
string to_clr_str(Node_data a);

#endif //NODE_H

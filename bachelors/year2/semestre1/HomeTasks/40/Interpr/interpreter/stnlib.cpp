#include "stnlib.h"


/* Implementation for standart functions */

Node_data print_func(vector<Node_data> &args) {
    for (int i = 0; i < args.size(); i++) {
        Node_data cur = get_value(args[i]);
        if (cur.type == Number) {
            cout << cur.d_val;
        } else if (cur.type == Char) {
            cout << cur.ch_val;
        } else {
            cout << str_to_print(*cur.str_val);
        }
    }
    return Node_data(Number, toStr(args.size()));
}

Node_data scan_func(vector<Node_data> &args) {
    bool success = true;
    Node_data cur(String, "");
    for (int i = 0; i < args.size(); i++) {
        if (args[i].type != Variable) {
            success = false;
            cerr << "Argument must be a variable\n";
        } else {
            cin >> (*cur.str_val);
            operator_equal(args[i], cur);
        }
    }
    return Node_data(Number, toStr(args.size()));
}

Node_data return_func(vector<Node_data> &args) {
    Node_data res = Node_data(Return, "0");
    if (args.size())
        *res.str_val = to_str(args.back());
    return res;
}

Node_data break_func(vector<Node_data> &args) {
    Node_data res = Node_data(Break, "0");
    if (args.size())
        *res.str_val = to_str(args.back());
    return res;
}

/* Implementation for standart operators */

/* UNARY */

Node_data operator_is(Node_data arg0) {
    Node_data res(Boolean, "true");
    arg0 = get_value(arg0);
    if (arg0.type == Boolean && *arg0.str_val == "false") {
        res.str_val = new string("false");
    } else if (arg0.type == Number && arg0.d_val == 0) {
        res.str_val = new string("false");
    } else if (arg0.type == String && *arg0.str_val == """") {
        res.str_val = new string("false");
    } else if (arg0.type == Char && arg0.ch_val == 0) {
        res.str_val = new string("false");
    }
    return res;
}

Node_data operator_rev(Node_data arg0) {
    Node_data res = arg0;
    arg0 = get_value(arg0);
    if (arg0.type == String) {
        cerr << "There is no rev number for strings\n";
    } else {
        if (res.type == Number) {
            res.d_val *= -1;
        } else if (res.type == Char) {
            res.ch_val *= -1;
        }
    }
    return res;
}

Node_data operator_not(Node_data arg0) {
    Node_data res = operator_is(arg0);
    if (*res.str_val == "false") {
        *res.str_val = "true";
    } else {
        *res.str_val = "false";
    }
    return res;
}

Node_data operator_bit_not(Node_data arg0) {
    Node_data res;
    arg0 = get_value(arg0);
    if ((arg0.type != Number || is_integer(arg0.d_val) == false) && arg0.type != Boolean) {
        cerr << "Not avaible operation ~ for those type\n";
    } else {
        if (arg0.type == Number) {
            res = Node_data(Number, toStr(~(int(arg0.d_val))));
        } else {
            res = Node_data(Boolean, (*arg0.str_val) == "true" ? "false" : "true");
        }
    }
    return res;
}

Node_data operator_add(Node_data arg0, int delta, bool left) {
    Node_data res = get_value(arg0);
    string value = "";
    if (arg0.type == Variable) {
        value = variable_value(*arg0.var_val, *arg0.str_val);
    }
    if (arg0.type != Variable || is_number(value) == false || is_integer(fromStr(value)) == false) {
        cerr << "Not avaible ++ for this type\n";
    } else {
        double val = fromStr(value) + delta;
        set_var(*arg0.var_val, make_pair(*arg0.str_val, toStr(val)));
        if (left == false) {
            res.d_val = int(val);
        }
    }
    return res;
}

Node_data operator_plusplusL(Node_data arg0) {
    return operator_add(arg0, 1, true);
}

Node_data operator_plusplusR(Node_data arg0) {
    return operator_add(arg0, 1, false);
}

Node_data operator_minusx2L(Node_data arg0) {
    return operator_add(arg0, -1, true);
}

Node_data operator_minusx2R(Node_data arg0) {
    return operator_add(arg0, -1, false);
}

Node_data operator_unary_minus(Node_data arg0) {
    arg0 = get_value(arg0);
    if (arg0.type == Number) {
        arg0.d_val *= -1;
    } else if (arg0.type == Char) {
        arg0.ch_val *= -1;
    } else {
        cerr << "Unary minus is not used for this type\n";
    }
    return arg0;
}

Node_data operator_unary_plus(Node_data arg0) {
    return arg0;
}


Node_data operator_void(Node_data, Node_data) {

}
/* BINARY */
Node_data operator_semicolon(Node_data arg0, Node_data arg1) {
    Node_data res = arg1;
    if (arg0.type == Return) {
        res = arg0;
    }
    return res;
}

Node_data operator_coma(Node_data arg0, Node_data arg1) {
    return arg1;
}

Node_data bin_bit_op(Node_data arg0, Node_data arg1, char op) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        cerr << "Operation " << op << " can't be done with strings\n";
    } else {
        int val;
        int a0 = to_int(arg0), a1 = to_int(arg1);
        if (op == '&') {
            val = a0 & a1;
        } else if (op == '|') {
            val = a0 | a1;
        } else if (op == '^') {
            val = a0 ^ a1;
        } else if (op == '>') {
            val = a0 >> a1;
        } else if (op == '<') {
            val = a0 << a1;
        }
        res = from_int(val, arg0.type);
    }
    return res;
}

Node_data operator_and(Node_data arg0, Node_data arg1) {
    return bin_bit_op(arg0, arg1, '&');
}

Node_data operator_or(Node_data arg0, Node_data arg1) {
    return bin_bit_op(arg0, arg1, '|');
}

Node_data operator_xor(Node_data arg0, Node_data arg1) {
    return bin_bit_op(arg0, arg1, '^');
}

Node_data operator_shr(Node_data arg0, Node_data arg1) {
    return bin_bit_op(arg0, arg1, '>');
}

Node_data operator_shl(Node_data arg0, Node_data arg1) {
    return bin_bit_op(arg0, arg1, '<');
}

Node_data operator_equal(Node_data arg0, Node_data arg1) {
    Node_data res = get_value(arg1);
    if (arg0.type != Variable) {
        cerr << "Left operand must be lvalue\n";
    } else {
        string value = to_str(res);
        set_var(*(arg0.var_val), make_pair(*arg0.str_val, value));
    }
    return res;
}

Node_data operator_plus_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_plus(arg0, arg1));
}

Node_data operator_minus_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_minus(arg0, arg1));
}

Node_data operator_multi_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_multi(arg0, arg1));
}

Node_data operator_div_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_div(arg0, arg1));
}

Node_data operator_mod_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_mod(arg0, arg1));
}

Node_data operator_and_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_and(arg0, arg1));
}

Node_data operator_or_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_or(arg0, arg1));
}

Node_data operator_xor_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_xor(arg0, arg1));
}

Node_data operator_shl_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_shl(arg0, arg1));
}

Node_data operator_shr_equal(Node_data arg0, Node_data arg1) {
    return operator_equal(arg0, operator_shr(arg0, arg1));
}

Node_data operator_andx2(Node_data arg0, Node_data arg1) {
    return operator_and(operator_is(arg0), operator_is(arg1));
}

Node_data operator_orx2(Node_data arg0, Node_data arg1) {
    return operator_or(operator_is(arg0), operator_is(arg1));
}

Node_data operator_equalx2(Node_data arg0, Node_data arg1) {
    Node_data res(Boolean, "true");
    *res.str_val = (to_str(arg0) == to_str(arg1)) ? "true" : "false";
    //cout << *res.str_val << endl;
    return res;
}

Node_data operator_less(Node_data arg0, Node_data arg1) {
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    Node_data res = Node_data(Boolean, "true");
    if (arg1.type == String || arg0.type == String) {
        if (arg0.type != String || arg1.type != String)
            cerr << "Incompatible types\n";
        else
            *res.str_val = (*arg0.str_val < *arg1.str_val ? "true" : "false");
    } else {
        *res.str_val = (to_int(arg0) < to_int(arg1) ? "true" : "false");
    }
    return res;
}

Node_data operator_less_equal(Node_data arg0, Node_data arg1) {
    return operator_orx2(operator_less(arg0, arg1), operator_equalx2(arg0, arg1));
}

Node_data operator_bigger(Node_data arg0, Node_data arg1) {
    return operator_not(operator_less_equal(arg0, arg1));
}

Node_data operator_bigger_equal(Node_data arg0, Node_data arg1) {
    return operator_not(operator_less(arg0, arg1));
}

Node_data operator_not_equal(Node_data arg0, Node_data arg1) {
    return operator_not(operator_equalx2(arg0, arg1));
}

Node_data operator_plus(Node_data arg0, Node_data arg1) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        res = Node_data(String, "\"" + to_clr_str(arg0) + to_clr_str(arg1) + "\"");
    } else {
        if (arg0.type == arg1.type) {
            if (arg0.type == Boolean) {
                res = operator_xor(arg0, arg1);
            } else if (arg0.type == Char) {
                arg0.ch_val += arg1.ch_val;
                res = arg0;
            } else if (arg0.type == Number) {
                arg0.d_val += arg1.d_val;
                res = arg0;
            }
        } else {
            if (arg0.type == Char) {
                res = arg0;
                res.ch_val += to_int(arg1);
            } else
                res = Node_data(Number, toStr(to_number(arg0) + to_number(arg1)));
        }
    }
    return res;
}

Node_data operator_minus(Node_data arg0, Node_data arg1) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        cerr << "Can't do substraction with strings\n";
    } else {
        arg1 = operator_rev(arg1);
        res = operator_plus(arg0, arg1);
    }
    return res;
}

Node_data operator_multi(Node_data arg0, Node_data arg1) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        res = Node_data(String, "\"" + to_clr_str(arg0) + to_clr_str(arg1) + "\"");
    } else {
        if (arg0.type == arg1.type) {
            if (arg0.type == Boolean) {
                res = operator_and(arg0, arg1);
            } else if (arg0.type == Char) {
                arg0.ch_val *= arg1.ch_val;
                res = arg0;
            } else if (arg0.type == Number) {
                arg0.d_val *= arg1.d_val;
                res = arg0;
            }
        } else {
            res = Node_data(Number, toStr(to_number(arg0) * to_number(arg1)));
        }
    }
    return res;
}

Node_data operator_div(Node_data arg0, Node_data arg1) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        cerr << "Operation / is not avaible for strings\n";
    } else {
        if (*(operator_not(arg1).str_val) == "true") {
            cerr << "Division vy zero\n";
        } else {
            if (arg0.type == arg1.type) {
                if (arg0.type == Boolean) {
                    res = operator_and(arg0, arg1);
                } else if (arg0.type == Char) {
                    arg0.ch_val /= arg1.ch_val;
                    res = arg0;
                } else if (arg0.type == Number) {
                    arg0.d_val /= arg1.d_val;
                    res = arg0;
                }
            } else {
                res = Node_data(Number, toStr(to_number(arg0) / to_number(arg1)));
            }
        }
    }
    return res;
}

Node_data operator_mod(Node_data arg0, Node_data arg1) {
    Node_data res;
    arg0 = get_value(arg0);
    arg1 = get_value(arg1);
    if (arg0.type == String || arg1.type == String) {
        cerr << "Operation % is not avaible for strings\n";
    } else {
        res = Node_data(Number, toStr(to_int(arg0) % to_int(arg1)));
    }
    return res;
}

/* TERNARY */
Node_data operator_if(Node_data arg0, Node_data arg1, Node_data arg2) {
    Node_data res = operator_is(arg0);
    if (*res.str_val == "true") {
        res = arg1;
    } else {
        res = arg2;
    }
    return res;
}

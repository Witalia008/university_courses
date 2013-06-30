#ifndef PROGRAM_H
#define PROGRAM_H

#include "tree/tree.h"
#include "vars/variables.h"
#include "stnlib.h"

typedef Node_data func_type(vector<Node_data> &args);

class Program {
public:
    string file_name;
    ifstream source;
    struct Function {
        bool is_standart;
        string name;
        union {
            Tree *func_my;
            func_type *st_func;
        };
        Function() {}
        Function(string _name, Tree *func_tree) {
            is_standart = false;
            func_my = func_tree;
            name = _name;
        }
        Function(string _name, func_type f) {
            is_standart = true;
            st_func = f;
            name = _name;
        }
    };
    struct Operator {
        bool is_standart;
        int nary, priority;
        string name, sname;
        enum unary_type {Left, Right} type;
        enum binary_end {Big, Little} endian;
        union {
            Tree *oper_my;
            Node_data (*unary)(Node_data);
            Node_data (*binary)(Node_data, Node_data);
            Node_data (*ternary)(Node_data, Node_data, Node_data);
        };
        Operator() {}
        Operator(int prior, string _name, Tree *op, int _nary) {
            name = _name;
            nary = _nary;
            oper_my = op;
            is_standart = false;
            priority = prior;
        }
        Operator(int prior, string _name, Node_data un(Node_data), unary_type unt) {
            name = _name;
            is_standart = true;
            nary = 1;
            unary = un;
            priority = prior;
            type = unt;
        }
        Operator(int prior, string _name, Node_data bin(Node_data, Node_data), binary_end _endian) {
            name = _name;
            is_standart = true;
            nary = 2;
            binary = bin;
            priority = prior;
            endian = _endian;
        }
        Operator(int prior, string _name, string _sname, Node_data ter(Node_data, Node_data, Node_data)) {
            name = _name;
            sname = _sname;
            is_standart = true;
            nary = 3;
            ternary = ter;
            priority = prior;
        }
    };
    vector<Function> funcs;
    vector<Operator> opers;
    vector<string> stack;
    var_set vars;
    Program() {}
    Program(string file) {
        file_name = file;
        funcs.clear();
        opers.clear();
        vars = var_set();

        funcs.push_back(Function("print", print_func));
        funcs.push_back(Function("scan", scan_func));
        funcs.push_back(Function("return", return_func));

        opers.push_back(Operator(0, ";", operator_semicolon, Operator::Big));
        opers.push_back(Operator(1, ",", operator_coma, Operator::Big));
        opers.push_back(Operator(0, ",,", operator_coma, Operator::Big));

        opers.push_back(Operator(1, "&", operator_and, Operator::Little));
        opers.push_back(Operator(0, "^", operator_xor, Operator::Little));
        opers.push_back(Operator(0, "|", operator_or, Operator::Little));
        opers.push_back(Operator(0, ">>", operator_or, Operator::Big));
        opers.push_back(Operator(0, "<<", operator_or, Operator::Big));

        opers.push_back(Operator(1, "=", operator_equal, Operator::Big));
        opers.push_back(Operator(0, "+=", operator_plus_equal, Operator::Big));
        opers.push_back(Operator(0, "*=", operator_multi_equal, Operator::Big));
        opers.push_back(Operator(0, "/=", operator_div_equal, Operator::Big));
        opers.push_back(Operator(0, "%=", operator_mod_equal, Operator::Big));
        opers.push_back(Operator(0, "-=", operator_minus_equal, Operator::Big));
        opers.push_back(Operator(0, "^=", operator_xor_equal, Operator::Big));
        opers.push_back(Operator(0, "|=", operator_or_equal, Operator::Big));
        opers.push_back(Operator(0, "&=", operator_and_equal, Operator::Big));
        opers.push_back(Operator(0, ">>=", operator_and_equal, Operator::Big));
        opers.push_back(Operator(0, "<<=", operator_and_equal, Operator::Big));

        opers.push_back(Operator(1, "&&", operator_andx2, Operator::Little));
        opers.push_back(Operator(0, "||", operator_orx2, Operator::Little));

        opers.push_back(Operator(1, "==", operator_equalx2, Operator::Little));
        opers.push_back(Operator(0, "!=", operator_not_equal, Operator::Little));

        opers.push_back(Operator(1, "+", operator_plus, Operator::Little));
        opers.push_back(Operator(0, "-", operator_minus, Operator::Little));
        opers.push_back(Operator(1, "*", operator_multi, Operator::Little));
        opers.push_back(Operator(0, "/", operator_div, Operator::Little));
        opers.push_back(Operator(0, "%", operator_mod, Operator::Little));

        opers.push_back(Operator(1, "!", operator_not, Operator::Right));
        opers.push_back(Operator(0, "-", operator_unary_minus, Operator::Right));
        opers.push_back(Operator(0, "+", operator_unary_plus, Operator::Right));
        opers.push_back(Operator(0, "~", operator_bit_not, Operator::Right));

        opers.push_back(Operator(1, "++", operator_plusplusR, Operator::Right));
        opers.push_back(Operator(0, "++", operator_plusplusL, Operator::Left));
        opers.push_back(Operator(0, "--", operator_minusx2R, Operator::Right));
        opers.push_back(Operator(0, "--", operator_minusx2L, Operator::Left));

        opers.push_back(Operator(1, "for", operator_void, Operator::Little));
        opers.push_back(Operator(0, "while", operator_void, Operator::Little));

        opers.push_back(Operator(1, "?", ":", operator_if));
        opers.push_back(Operator(0, "if", "else", operator_if));

        for (int i = 1; i < opers.size(); i++) {
            opers[i].priority += opers[i - 1].priority;
        }
    }
};


#endif

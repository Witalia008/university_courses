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
        enum unary_type { Left, Right} type;
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
        Operator(int prior, string _name, Node_data bin(Node_data, Node_data)) {
            name = _name;
            is_standart = true;
            nary = 2;
            binary = bin;
            priority = prior;
        }
        Operator(int prior, string _name, string _sname, Node_data ter(Node_data, Node_data, Node_data)) {
            name = _name;
            is_standart = true;
            nary = 3;
            ternary = ter;
            priority = prior;
        }
    };
    vector<Function> funcs;
    vector<Operator> opers;
    var_set vars;
    Program() {}
    Program(string file) {
        file_name = file;
        funcs.clear();
        opers.clear();
        vars = var_set();

        funcs.push_back(Function("print", print));
        funcs.push_back(Function("scan", scan));

        opers.push_back(Operator(0, ";", operator_semicolon));
        opers.push_back(Operator(1, ",", operator_coma));
        opers.push_back(Operator(0, ".,", operator_coma));

        opers.push_back(Operator(1, "&", operator_and));
        opers.push_back(Operator(0, "^", operator_xor));
        opers.push_back(Operator(0, "|", operator_or));
        opers.push_back(Operator(0, ">>", operator_or));
        opers.push_back(Operator(0, "<<", operator_or));

        opers.push_back(Operator(1, "=", operator_equal));
        opers.push_back(Operator(0, "+=", operator_plus_equal));
        opers.push_back(Operator(0, "*=", operator_multi_equal));
        opers.push_back(Operator(0, "/=", operator_div_equal));
        opers.push_back(Operator(0, "%=", operator_mod_equal));
        opers.push_back(Operator(0, "-=", operator_minus_equal));
        opers.push_back(Operator(0, "^=", operator_xor_equal));
        opers.push_back(Operator(0, "|=", operator_or_equal));
        opers.push_back(Operator(0, "&=", operator_and_equal));
        opers.push_back(Operator(0, ">>=", operator_and_equal));
        opers.push_back(Operator(0, "<<=", operator_and_equal));

        opers.push_back(Operator(1, "&&", operator_andx2));
        opers.push_back(Operator(0, "||", operator_orx2));

        opers.push_back(Operator(1, "==", operator_equalx2));
        opers.push_back(Operator(0, "!=", operator_not_equal));

        opers.push_back(Operator(1, "+", operator_plus));
        opers.push_back(Operator(0, "-", operator_minus));
        opers.push_back(Operator(1, "*", operator_multi));
        opers.push_back(Operator(0, "/", operator_div));
        opers.push_back(Operator(0, "%", operator_mod));

        opers.push_back(Operator(1, "!", operator_not, Operator::Right));
        opers.push_back(Operator(0, "~", operator_bit_not, Operator::Right));
        opers.push_back(Operator(0, "++", operator_plusplusR, Operator::Right));
        opers.push_back(Operator(0, "++", operator_plusplusL, Operator::Left));
        opers.push_back(Operator(0, "--", operator_minusx2R, Operator::Right));
        opers.push_back(Operator(0, "--", operator_minusx2L, Operator::Left));

        for (int i = 1; i < opers.size(); i++) {
            opers[i].priority += opers[i - 1].priority;
        }
    }
};

bool build(Program&);
bool run(Program&);
vector<Node_data> calc(Tree*, Program&);
int get_func_id(Program&, string);
int get_oper_id(Program&, string);
Node_data read_number(istream&);
Node_data read_string(istream&);
Node_data read_variable(istream&);
Node_data read_char(istream&);
int oper_number(Program&, string);
int find_oper(Program&, int);
int next_by_prior(Program&, int);
void user_functions(Program&);
Tree *operators(Program&, int);
Tree *functions(Program&, int);
Tree *operand(Program&);

#endif

#include "parser.h"


bool cmp(const Program::Operator &a, const Program::Operator &b) {
    return a.priority < b.priority;
}

bool build(Program &prog) {
    prog.source.open(prog.file_name.c_str());
    user_functions(prog);
    prog.source.close();
}

Node_data read_number(istream &f) {
    string str_num = read_dig_seq(f);
    if (f.peek() != -1 && f.peek() == '.') {
        str_num += f.get();
        str_num += read_dig_seq(f);
        if (f.peek() != -1 && f.peek() == 'e') {
            str_num += f.get();
            str_num += read_dig_seq(f);
        }
    }
    return Node_data(Number, str_num);
}

Node_data read_string(istream &f) {
    string str = "";
    if (check_symb(f, '"')) {
        str += '"';
        while (f.peek() != -1 && (f.peek() != '"' || prev_symb(f) == '\\')) {
            str += f.get();
        }
        if (check_symb(f, '"')) {
            str += '"';
        } else {
            cerr << "No closing quote!\n";
        }
    } else {
        cerr << "No opening quote!\n";
    }
    return Node_data(String, str);
}

Node_data read_char(istream &f) {
    string str = "";
    if (check_symb(f, '\'')) {
        str += '\'';
        while (f.peek() != -1 && f.peek() != '\'') {
            str += f.get();
        }
        if (check_symb(f, '\'')) {
            str += '\'';
        } else {
            cerr << "No closing quote!\n";
        }
    } else {
        cerr << "No opening quote!\n";
    }
    return Node_data(Char, str);
}

Node_data read_variable(istream &f) {
    string var_name = "";
    if (f.peek() != -1 && (f.peek() == '_' || isalpha(f.peek()))) {
        var_name += f.get();
        while (f.peek() != -1 && (f.peek() == '_' || isdigit(f.peek()) || isalpha(f.peek()))) {
            var_name += f.get();
        }
    } else {
        if (f.peek() != -1) {
            cerr << "It's not a name of variable or function!\n";
        }
    }
    return Node_data(Variable, var_name);
}

int oper_number(Program &prog, string op_name) {
    int res = -1;
    for (int i = 0; i < prog.opers.size() && res == -1; i++) {
        if (prog.opers[i].name == op_name) {
            res = i;
        }
    }
    return res;
}

int find_oper(Program &prog, int num, bool is_left) {
    int res = -1;
    for (int i = num; i < prog.opers.size() && prog.opers[i].priority == prog.opers[num].priority && res == -1; i++) {
        if (prog.opers[i].name == next_symbs(prog.source, prog.opers[i].name.size())
            && (prog.opers[i].nary != 1 ||
            (prog.opers[i].type == is_left ? Program::Operator::Left : Program::Operator::Right))) {
            res = i;
        }
    }
    for (int i = 0; i < prog.opers.size() && res != -1; i++) {
        if (prog.opers[i].name == next_symbs(prog.source, prog.opers[i].name.size()) &&
            prog.opers[i].name.size() > prog.opers[res].name.size()) {
            res = -1;
        }
    }
    return res;
}

int next_by_prior(Program &prog, int pos) {
    int res = pos;
    while (res < prog.opers.size() && prog.opers[pos].priority == prog.opers[res].priority) {
        ++res;
    }
    return res;
}

void user_functions(Program &prog) {
    for (;;) {
        ignore_whitespace(prog.source);
        string func_name = *read_variable(prog.source).str_val;
        if (prog.source.peek() == -1 || func_name == "") {
            break;
        }
        Tree *args = operand(prog);
        if (args != NULL && *args->data.str_val == ",,")
            *args->data.str_val = ",";
        Tree *body = operand(prog);
        prog.funcs.push_back(Program::Function(func_name, create_tree(Node_data(Func, func_name), args, body)));
     }
}

Tree *operators(Program &prog, int op_num) {
    if (op_num == prog.opers.size()) {
        return functions(prog, 0);
    }
    int next_op_num = next_by_prior(prog, op_num);
    Tree *res = operators(prog, next_op_num);
    int pos;
    while ((pos = find_oper(prog, op_num, res != NULL)) != -1) {
        switch (prog.opers[pos].nary) {
        case 1:
            if (prog.opers[pos].type == Program::Operator::Left) {
                if (res == NULL)
                    return res;
                else {
                    prog.source.ignore(prog.opers[pos].name.size());
                    res = create_tree(Node_data(Oper, prog.opers[pos].name + "0"), res, NULL);
                }
            } else {
                if (res == NULL) {
                    prog.source.ignore(prog.opers[pos].name.size());
                    res = create_tree(Node_data(Oper, prog.opers[pos].name + "1"), operators(prog, next_op_num), NULL);
                } else return res;
            }
        break;
        case 2:
            prog.source.ignore(prog.opers[pos].name.size());
            if (prog.opers[pos].name == "for") {
                res = create_tree(Node_data(Oper, prog.opers[pos].name), NULL, NULL);
                check_symb(prog.source, '(');
                for (int i = 0; i < 3; i++) {
                    Tree *r = operators(prog, 1);
                    add_subtree(res, r);
                    check_symb(prog.source, i == 2 ? ')' : ';');
                }
                add_subtree(res, operand(prog));
            } else if (prog.opers[pos].name  == "while"){
                res = create_tree(Node_data(Oper, prog.opers[pos].name), NULL, NULL);
                for (int i = 0; i < 2; i++)
                    add_subtree(res, operand(prog));
            } else if (prog.opers[pos].name == "do") {
                res = create_tree(Node_data(Oper, prog.opers[pos].name), NULL, NULL);
                add_subtree(res, operand(prog));
                if (next_symbs(prog.source, prog.opers[pos].sname.size()) == prog.opers[pos].sname) {
                    prog.source.ignore(prog.opers[pos].sname.size());
                    add_subtree(res, operand(prog));
                }
            } else
            res = create_tree(Node_data(Oper, prog.opers[pos].name), res,
                                operators(prog, (prog.opers[pos].endian == Program::Operator::Big) ? op_num : next_op_num));
        break;
        case 3:
            if (prog.opers[pos].name == "if") {
                prog.source.ignore(prog.opers[pos].name.size());
                res = operators(prog, next_op_num);
            }
            res = create_tree(Node_data(Oper, prog.opers[pos].name), res, NULL);
            if (prog.opers[pos].name != "if")
                prog.source.ignore(prog.opers[pos].name.size());
            add_subtree(res, operators(prog, next_op_num));
            if (next_symbs(prog.source, prog.opers[pos].sname.size()) == prog.opers[pos].sname) {
                prog.source.ignore(prog.opers[pos].sname.size());
                add_subtree(res, operators(prog, next_op_num));
                return res;
            }
        break;
        }
    }
    return res;
}

Tree *functions(Program &prog, int func_num) {
    if (func_num == prog.funcs.size()) {
        return operand(prog);
    }
    Tree *res = NULL;
    if (prog.funcs[func_num].name == next_symbs(prog.source, prog.funcs[func_num].name.size())
        && end_of_name(prog.source, prog.funcs[func_num].name.size())) {
        prog.source.ignore(prog.funcs[func_num].name.size());
        Tree *son = operand(prog);
        if (son != NULL && son->data.type == Oper && *son->data.str_val == ",,")
            *son->data.str_val = ",";
        res = create_tree(Node_data(Func, prog.funcs[func_num].name), son, NULL);
    } else {
        res = functions(prog, func_num + 1);
    }
    return res;
}

Tree *operand(Program &prog) {
    char cur_symb = next_symbs(prog.source, 1).at(0);
    Tree *res = NULL;
    if (isdigit(cur_symb)) {
        res = create_tree(read_number(prog.source));
    } else if (cur_symb == '"') {
        res = create_tree(read_string(prog.source));
    } else if (cur_symb == '\'') {
        res = create_tree(read_char(prog.source));
    } else if ((cur_symb == '_' || isalpha(cur_symb)) && !reserved_name(prog.source)) {
        res = create_tree(read_variable(prog.source));
        res->data.var_val = &prog.vars;
    } else if (cur_symb == '(') {
        check_symb(prog.source, '(');
        res = operators(prog, oper_number(prog, ","));
        if (res != NULL && res->data.type == Oper && *res->data.str_val == ",")
            *res->data.str_val = ",,";
        check_symb(prog.source, ')');
    } else if (cur_symb == '{') {
        check_symb(prog.source, '{');
        res = operators(prog, oper_number(prog, ";"));
        check_symb(prog.source, '}');
    } else if (cur_symb == ';' && prev_symb(prog.source) == ')') {
        check_symb(prog.source, ';');
    }
    return res;
}



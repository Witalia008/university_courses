#include "program.h"

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

int find_oper(Program &prog, int num) {
    int res = -1;
    for (int i = num; i < prog.opers.size() && prog.opers[i].priority == prog.opers[num].priority && res == -1; i++) {
        if (prog.opers[i].name == next_symbs(prog.source, prog.opers[i].name.size())) {
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
        Tree *body = operand(prog);
        prog.funcs.push_back(Program::Function(func_name, create_tree(Node_data(Func, func_name), args, body)));
       /* prog.funcs.push_back(Program::Function(func_name, create_tree(Node_data(Func, func_name),
                                                                        operators(prog, oper_number(prog, ",")),
                                                                        operators(prog, oper_number(prog, ";")))));*/
    }
}

Tree *operators(Program &prog, int op_num) {
    if (op_num == prog.opers.size()) {
        return functions(prog, 0);
    }
    int next_op_num = next_by_prior(prog, op_num);
    Tree *res = operators(prog, next_op_num);
    int pos;
    while ((pos = find_oper(prog, op_num)) != -1) {
        prog.source.ignore(prog.opers[pos].name.size());
        res = create_tree(Node_data(Oper, prog.opers[pos].name), res, NULL);
        if (prog.opers[pos].nary > 1 || prog.opers[pos].type == Program::Operator::Right) {
            add_subtree(res, operators(prog, next_op_num));
            if (prog.opers[pos].nary > 2) {
                if (next_symbs(prog.source, prog.opers[pos].sname.size()) == prog.opers[pos].sname) {
                    add_subtree(res, operators(prog, next_op_num));
                } else {
                    cerr << "Not enough arguments for operator!\n";
                }
            }
        }
    }
    return res;
}

Tree *functions(Program &prog, int func_num) {
    if (func_num == prog.funcs.size()) {
        return operand(prog);
    }
    Tree *res = NULL;
    if (prog.funcs[func_num].name == next_symbs(prog.source, prog.funcs[func_num].name.size())) {
        prog.source.ignore(prog.funcs[func_num].name.size());
        Tree *son = operand(prog);
        if (*son->data.str_val == ".,") {
            *son->data.str_val = ",";
        }
        res = create_tree(Node_data(Func, prog.funcs[func_num].name), son, NULL);
    } else {
        res = functions(prog, func_num + 1);
    }
    return res;
}

Tree *operand(Program &prog) {
    char cur_symb = next_symbs(prog.source, 1).at(0);
    Tree *res = NULL;
    if (cur_symb == '-' || cur_symb == '+' || isdigit(cur_symb)) {
        res = create_tree(read_number(prog.source));
    } else if (cur_symb == '"') {
        res = create_tree(read_string(prog.source));
    } else if (cur_symb == '\'') {
        res = create_tree(read_char(prog.source));
    } else if (cur_symb == '_' || isalpha(cur_symb)) {
        res = create_tree(read_variable(prog.source));
        res->data.var_val = &prog.vars;
    } else if (cur_symb == '(') {
        check_symb(prog.source, '(');
        res = operators(prog, oper_number(prog, ","));
        if (res != NULL && *res->data.str_val == ",") {
            *res->data.str_val = ".,";
        }
        check_symb(prog.source, ')');
    } else if (cur_symb == '{') {
        check_symb(prog.source, '{');
        res = operators(prog, oper_number(prog, ";"));
        check_symb(prog.source, '}');
    }
    return res;
}

int get_func_id(Program &prog, string _name) {
    int res = -1;
    for (int i = 0; i < prog.funcs.size(); i++) {
        if (prog.funcs[i].name == _name) {
            res = i;
        }
    }
    return res;
}

int get_oper_id(Program &prog, string _name) {
    int res = -1;
    for (int i = 0; i < prog.opers.size(); i++) {
        if (prog.opers[i].name == _name) {
            res = i;
        }
    }
    return res;
}

vector<Node_data> calc(Tree *node, Program &prog) {
    vector<Node_data> res, sons, son;
    sons.clear();
    for (Tree::List *i = node->sons; i != NULL; i = get_next(i)) {
        res = calc(i->data, prog);
        sons.insert(sons.end(), res.begin(), res.end());
        son.push_back(sons.back());
    }
    res.clear();
    if (node->data.type == Oper) {
        if (*node->data.str_val == ",") {
            res = sons;
        } else {
            int oper_id = get_oper_id(prog, *node->data.str_val);
            if (prog.opers[oper_id].is_standart == true) {
                switch (prog.opers[oper_id].nary) {
                case 1:
                    res.push_back(prog.opers[oper_id].unary(son[0]));
                    break;
                case 2:
                    res.push_back(prog.opers[oper_id].binary(son[0], son[1]));
                    break;
                case 3:
                    res.push_back(prog.opers[oper_id].ternary(son[0], son[1], son[2]));
                    break;
                }
            }
        }
    } else if (node->data.type == Func) {
        int func_id = get_func_id(prog, *node->data.str_val);
        if (prog.funcs[func_id].is_standart == true) {
            res.push_back(prog.funcs[func_id].st_func(sons));
        } else {
        //    res = calc(prog.funcs[func_id].func_my, prog);
        }
    } else {
        res.push_back(node->data);
    }
    return res;
}

bool run(Program &prog) {
    bool success = true;
    int main_id = -1;
    for (int i = 0; i < prog.funcs.size(); i++) {
        if (prog.funcs[i].name == "main") {
            main_id = i;
        }
    }
    if (main_id == -1) {
        main_id = prog.funcs.size() - 1;
    }
    if (prog.funcs[main_id].is_standart == true) {
        cerr << "No functions found!\n";
        success = false;
    } else {
        calc(prog.funcs[main_id].func_my, prog);
    }
    return success;
}

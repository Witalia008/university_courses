#include "executer.h"


vector<Node_data> calc(Tree *node, Program &prog, string namesp) {
    vector<Node_data> res, sons, son;
    if (!node)
        return res;
    sons.clear();
    bool is_ter = (node->data.type == Oper && (*node->data.str_val == "if" || *node->data.str_val == "?"));
    bool is_for = (node->data.type == Oper && *node->data.str_val == "for");
    for (Tree::List *i = node->sons; i != NULL; i = get_next(i)) {
        if (is_for) break;
        res = calc(i->data, prog, namesp);
        sons.insert(sons.end(), res.begin(), res.end());
        son.push_back(sons.back());
        if (is_ter) break;
    }
    res.clear();
    if (node->data.type == Oper) {
        if (*node->data.str_val == ",") {
            res = sons;
        } else {
            int oper_id = get_oper_id(prog, *node->data.str_val, is_ter ? 3 : (is_for ? 2 : son.size()));
            //cout << *node->data.str_val << endl;
            if (prog.opers[oper_id].is_standart == true) {
                switch (prog.opers[oper_id].nary) {
                case 1:
                    res.push_back(prog.opers[oper_id].unary(son[0]));
                    break;
                case 2:
                    if (prog.opers[oper_id].name == "for") {
                        res = calc(get_son(node, 0), prog, namesp);
                        int cnt_iters = 0;
                        while (*operator_is(calc(get_son(node, 1), prog, namesp).back()).str_val == "true") {
                            res = calc(get_son(node, 3), prog, namesp);
                            res = calc(get_son(node, 2), prog, namesp);
                            cnt_iters++;
                        }
                        res.clear(); res.push_back(Node_data(Number, toStr(cnt_iters)));
                    } else if (prog.opers[oper_id].name == "while"){
                        int cnt_iters = 0;
                        while (*operator_is(calc(get_son(node, 0), prog, namesp).back()).str_val == "true") {
                            res = calc(get_son(node, 1), prog, namesp);
                            cnt_iters++;
                        }
                        res.clear(); res.push_back(Node_data(Number, toStr(cnt_iters)));
                    } else
                        res.push_back(prog.opers[oper_id].binary(son[0], son[1]));
                    break;
                case 3:
                    if (*operator_is(son[0]).str_val == "true")
                        res.push_back(calc(get_son(node, 1), prog, namesp).back());
                    else if (get_son(node, 1) != NULL)
                        res.push_back(calc(get_son(node, 2), prog, namesp).back());
                    else res.push_back(son[0]);
                    break;
                }
            }
        }
    } else if (node->data.type == Func) {
        int func_id = get_func_id(prog, *node->data.str_val);
        if (prog.funcs[func_id].is_standart == true) {
            res.push_back(prog.funcs[func_id].st_func(sons));
        } else {
            res.push_back(exec_func(func_id, prog, sons, namesp));
        }
    } else {
        res.push_back(node->data);
        if (res.back().type == Variable && (*res.back().str_val).substr(0, namesp.size()) != namesp)
            *res.back().str_val = namesp + *res.back().str_val;
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
        cerr << "Program executed with status " << exec_func(main_id, prog, vector<Node_data>(0), "").d_val << endl;
    }
    return success;
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

int get_oper_id(Program &prog, string _name, int ary) {
    int res = -1;
    for (int i = 0; i < prog.opers.size(); i++) {
        if (prog.opers[i].name == _name && ary == prog.opers[i].nary) {
            res = i;
        }
        if (prog.opers[i].nary == 1 && ary == 1)
            if (_name.substr(0, prog.opers[i].name.size()) == prog.opers[i].name &&
            (_name[prog.opers[i].name.size()] == '0' ? Program::Operator::Left : Program::Operator::Right)
            == prog.opers[i].type)
                res = i;
    }
    return res;
}


Node_data exec_func(int id, Program &prog, vector<Node_data> args, string namesp) {
    Program::Function & func = prog.funcs[id];
    namesp += func.name + "::";
    vector<Node_data> params = get_params(func, prog, namesp);
    if (params.size() > args.size()) {
        cerr << "No enough arguments for functinon " << func.name << endl;
        return Node_data(Number, "1");
    }
    if (find_in_stack(prog, func.name)) {
        cerr << "Oops! Function " << func.name << " creates infinite recursion\n";
        return Node_data(Number, "1");
    }
    prog.stack.push_back(func.name);
    for (int i = 0; i < params.size(); i++) {
        operator_equal(params[i], args[i]);
    }
    vector<Node_data> res = calc(get_body(func, prog), prog, namesp);
    prog.stack.pop_back();
    if (res.size())
        return res.back();
    return Node_data(Number, "1");
}

vector<Node_data> get_params(Program::Function &func, Program &prog, string namesp) {
    vector<Node_data> res(0);
    if (get_next(func.func_my->sons))
        res = calc(func.func_my->sons->data, prog, namesp);
    return res;
}

Tree *get_body(Program::Function &func, Program &prog) {
    if (!func.func_my->sons)
        return NULL;
    Tree *res = func.func_my->sons->data;
    if (get_next(func.func_my->sons))
        res = get_next(func.func_my->sons)->data;
    return res;
}

bool find_in_stack(Program &prog, string name) {
    for (int i = 0; i < prog.stack.size(); i++)
        if (prog.stack[i] == name)
            return true;
    return false;
}


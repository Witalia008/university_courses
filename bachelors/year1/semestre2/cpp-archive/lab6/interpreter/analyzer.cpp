#include "analyzer.h"

bool call(Tree *f, Program &prog) {
    if (f == NULL)
        return false;
    if (f->data.type == Oper && *f->data.str_val == "if")
        return false;

    bool res = false;
    if (f->data.type == Func) {
        int func_id = get_func_id(prog, *f->data.str_val);
        if (prog.funcs[func_id].is_standart == false)
            res |= call_func(func_id, prog);
    } else {
        for (Tree::List *i = f->sons; i != NULL; i = get_next(i))
            res |= call(i->data, prog);
    }
    return res;
}

bool call_func(int id, Program &prog) {
    if (find_in_stack(prog, prog.funcs[id].name)) {
        cerr << "Function " << prog.funcs[id].name << " seems to create an infinite recursion\n";
        return true;
    }
    prog.stack.push_back(prog.funcs[id].name);
    bool res = call(get_body(prog.funcs[id], prog), prog);
    prog.stack.pop_back();
    return res;
}

bool analyze(Program &prog) {
    for (int i = 0; i < prog.funcs.size(); i++)
        if (prog.funcs[i].name == "main") {
            return call_func(i, prog);
        }
}

bool find_in_stack(Program &prog, string name) {
    for (int i = 0; i < prog.stack.size(); i++)
        if (prog.stack[i] == name)
            return true;
    return false;
}

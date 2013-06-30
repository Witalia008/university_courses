#ifndef EXECUTER_H
#define EXECUTER_H

#include "program.h"

bool run(Program&);
vector<Node_data> calc(Tree*, Program&, string namesp);
int get_func_id(Program&, string);
int get_oper_id(Program&, string, int);
Node_data exec_func(int id, Program &prog, vector<Node_data> args, string namesp);
vector<Node_data> get_params(Program::Function &func, Program &prog, string namesp);
Tree *get_body(Program::Function &func, Program &prog);
bool find_in_stack(Program &prog, string name);

#endif //EXECUTER_H

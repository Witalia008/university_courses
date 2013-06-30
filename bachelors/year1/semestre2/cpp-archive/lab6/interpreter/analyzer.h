#ifndef ANALYZER_H
#define ANALYZER_H

#include "program.h"

extern int get_func_id(Program&, string);
bool call(Tree*, Program&);
bool call_func(int, Program&);
bool analyze(Program&);
bool find_in_stack(Program &prog, string name);
extern Tree *get_body(Program::Function &func, Program &prog);

#endif //ANALYZER_H

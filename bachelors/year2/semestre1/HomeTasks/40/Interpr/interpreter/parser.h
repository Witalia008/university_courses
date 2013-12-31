
#ifndef PARSER_H
#define PARSER_H

#include "program.h"

bool build(Program&);
Node_data read_number(istream&);
Node_data read_string(istream&);
Node_data read_variable(istream&);
Node_data read_char(istream&);
int oper_number(Program&, string);
int find_oper(Program&, int, bool);
int next_by_prior(Program&, int);
void user_functions(Program&);
Tree *operators(Program&, int);
Tree *functions(Program&, int);
Tree *operand(Program&);

#endif //PARSER_H

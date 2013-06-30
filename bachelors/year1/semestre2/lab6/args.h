#ifndef ARGS_H
#define ARGS_H

#include "master.h"

typedef enum {Number, String, Variable} ArgName;

struct argument {
    ArgName name;
    string value;
};

#endif //ARGS_H

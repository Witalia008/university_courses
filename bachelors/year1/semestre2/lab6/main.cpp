#include <iostream>

using namespace std;

#include "program.h"
#include "executer.h"
#include "parser.h"

int main()
{
    Program prog("x.cpp");
    build(prog);
    run(prog);
    return 0;
}

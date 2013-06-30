#include <iostream>

using namespace std;

#include "interpreter/analyzer.h"
#include "interpreter/executer.h"
#include "interpreter/parser.h"
#include "interpreter/program.h"

int main()
{
    Program prog("x.cpp");
    build(prog);
    bool need_run = false;
    if (analyze(prog) == false) {
        need_run = true;
    } else {
        cout << "Would you like to run program? [y] / [n]: ";
        if (cin.get() == 'y')
            need_run = true;
    }
    if (need_run == true) {
        run(prog);
    }
    return 0;
}

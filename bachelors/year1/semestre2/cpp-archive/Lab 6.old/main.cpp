#include <iostream>

using namespace std;

#include "program.h"

int main()
{
    Program prog("m.cpp");
    build(prog);
    cout << prog.funcs.size() << endl;
    run(prog);
    return 0;
}

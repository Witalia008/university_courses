#include "head.h"
#include "variables.h"

VarSet a;

int main()
{
    add_var("a", "1", a);
    add_var("b", "2", a);
    fromFile(a);
    del_var("a", a);
    toFile(a);
    return 0;
}

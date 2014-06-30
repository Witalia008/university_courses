#include "SortPack.h"

int main() {
    int n = 10;
    ArrayOfInt a(n);
    a.fill();
    //a.show();
    SortPack sorter;
    sorter.attach(a, n);
    sorter.quick();
    sorter.show();
    system("pause");
    return 0;
}
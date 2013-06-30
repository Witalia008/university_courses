#include <iostream>
#include "list.h"
#include "sort.h"
#include "polynom.h"

using namespace std;

List *mas;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    task1();
    task2();
    int n;
    cin >> n;
    mas = 0;
    for (int i = 0; i < n; i++) {
        double val;
        cin >> val;
        mas = insert_after(mas, val);
    }
    mas = get_head(mas);
    List * i = get_tail(mas);
    while (i && get_prev(i)) {
        List * j = mas;
        while (get_next(j)) {
            if (get_value(j) > get_value(get_next(j)))
                swap_values(j, get_next(j));
            j = get_next(j);
        }
        i = get_prev(i);
    }
    print(mas);
    return 0;
}

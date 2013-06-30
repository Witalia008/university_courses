#ifndef POLYNOM_INCLUDED
#define POLYNOM_INCLUDED

#include <iostream>
#include "list.h"

/*
 * Contains degree of polynom and coeficients before x^0, x^1, ... , x ^ degree
 */
struct polynom {
    int degree;
    List *coef;
    List *poww;
};

void add_power(polynom &r, list_type power, list_type coef);
polynom read_polynom();
void write_polynom(polynom a);
polynom sum_poly(polynom a, polynom b);
polynom multiply(polynom a, polynom b);
void task2();

#endif // POLYNOM_INCLUDED

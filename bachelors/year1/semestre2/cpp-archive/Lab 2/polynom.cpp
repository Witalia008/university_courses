#include "polynom.h"

/*
 * Reads polynom from stdin.
 */
polynom read_polynom () {
    polynom res;
    int n;
    cin >> n;
    res.coef = res.poww = 0;
    res.degree = 0;
    for (int i = 0; i < n; i++) {
        list_type cur_coef, cur_pow;
        cin >> cur_coef >> cur_pow;
        res.coef = insert_after (res.coef, cur_coef);
        res.poww = insert_after (res.poww, cur_pow);
        if (cur_pow > res.degree)
            res.degree = cur_pow;
    }
    res.coef = get_head(res.coef);
    res.poww = get_head(res.poww);
    return res;
}

/*
 * This function search for some power in polynom. If there is one, it add some value to coeficient
 * before this power. Else it add this power in some place in polynom. After this operation
 * polynom will left ordered by powers.
 */

void add_power (polynom &r, list_type power, list_type coef) {
    List *r_coef, *r_poww;
    r_coef = get_head(r.coef);
    r_poww = get_head(r.poww);
    while (r_coef && r_poww->data < power) {
        r_coef = get_next(r_coef);
        r_poww = get_next(r_poww);
    }
    if (r_coef) {
        if (r_poww->data == power) {
            r_coef->data += coef;
        } else {
            r_coef = insert_before(r_coef, coef);
            r_poww = insert_before(r_poww, power);
        }
    } else {
        r.coef = insert_after(r.coef, coef);
        r.poww = insert_after(r.poww, power);
    }
}

/*
 * Sum of two polynoms. One by one adds powers with coeficients on polynom 1 and 2.
 */
polynom sum_poly (polynom a, polynom b) {
    polynom res;
    res.degree = max (a.degree, b.degree);
    res.coef = res.poww = 0;
    List *l_coef, *l_poww;
    for (int i = 0; i < 2; i++) {
        for (l_coef = a.coef, l_poww = a.poww; l_coef; l_coef = get_next(l_coef), l_poww = get_next(l_poww))
            add_power(res, l_poww->data, l_coef->data);
        swap(a, b);
    }
    res.coef = get_head(res.coef);
    res.poww = get_head(res.poww);
    return res;
}


/*
 * Multiplies two polynoms. Take pair i and j. i - power of a, j - power of b. And adds in result
 * polynome power i+j with some coeficient.
 */
polynom multiply (polynom a, polynom b) {
    polynom res;
    res.degree = a.degree + b.degree;
    res.poww = res.coef = 0;
    for (List *coef_1 = a.coef, *poww_1 = a.poww; coef_1; coef_1 = get_next(coef_1), poww_1 = get_next(poww_1)) {
        for (List *coef_2 = b.coef, *poww_2 = b.poww; coef_2; coef_2 = get_next(coef_2), poww_2 = get_next(poww_2))
            add_power (res, poww_1->data + poww_2->data, coef_1->data * coef_2->data);
    }
    res.coef = get_head(res.coef);
    res.poww = get_head(res.poww);
    return res;
}

/*
 * Outputs polynom to stdout.
 */
void write_polynom (polynom a) {
    for (List *poww = get_tail(a.poww), *coef = get_tail(a.coef); coef; coef = get_prev(coef), poww = get_prev(poww))
        if (coef->data != 0) {
            printf ("%.4lf", coef->data);
            if (poww->data != 0)
                printf (" * x ^ %.0lf", poww->data);
            if (poww->prev)
                printf (" + ");
        }
    printf ("\n\n");
}

void task2() {
    polynom a = read_polynom();
    polynom b = read_polynom();
    polynom c = sum_poly (a, b);
    polynom d = multiply (a, b);
    write_polynom (c);
    write_polynom (d);
}

#include "sort.h"

void digit_sort (List *&from, List *to) {
    struct {
        int operator () (int a) {
            int res = 0;
            while (a)
                ++res, a /= 10;
            return res;
        }
    } cnt_digs;
    List *p;
    int max_dig_len = 0;
    for (p = from; p != to; p = get_next(p))
        max_dig_len = max (max_dig_len, cnt_digs(get_value(p)));
    int poww = 1;
    List * bucket[10];
    for (int i = 0; i < 10; i++)
        bucket[i] = 0;
    List *before_from = get_prev(from);
    for (int cur_dig = 0; cur_dig < max_dig_len; cur_dig++) {
        for (p = from; p != to;) {
            int cur_dig = ((int)get_value(p) / poww) % 10;
            List *p1 = p;
            p = get_next(p);
            p1 = cut_list(p1, p1);
            bucket[cur_dig] = union_list(bucket[cur_dig], p1);
        }
        p = before_from;
        for (int i = 0; i < 10; i++) {
            p = union_list(p, bucket[i]);
            bucket[i] = 0;
        }
        p = union_list(p, to);
        poww *= 10;
        from = get_head(p);
    }
}

void task1 ()
{
    List *mas = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double val;
        cin >> val;
        mas = insert_after(mas, val);
    }
    mas = get_head(mas);
    digit_sort(mas, 0);
    print(mas);
}

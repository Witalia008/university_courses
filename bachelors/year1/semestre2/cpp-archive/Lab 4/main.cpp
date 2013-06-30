#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <iomanip>
#include "sorters.h"

using namespace std;

#define Inf 1000000000
#define N 10000

int cnt_ops;

ofstream info_file ("output.txt");

bool lower (my_type a, my_type b) {
    cnt_ops++;
    return a < b;
}

void output_array (my_type a[], int l, int r, fstream &out){
    for (int i = l; i <= r; i++)
        out << fixed << setprecision(3) << a[i] << " ";
    out << "\n\n";
}

void random_set (my_type a[], int l, int r) {
    srand(1234567);
    for (int i = l; i <= r; i++)
        a[i] = rand16() / 1000.0;
}

bool is_sorted_arr(string file_name, cmp_type cmp, int n) {
    ifstream inp (file_name.c_str());
    my_type prev, cur;
    for (int i = 0; i <= n; i++)
        inp >> prev;
    for (int i = 1; i < n; i++) {
        inp >> cur;
        if (cmp(cur, prev)){
            inp.close();
            cout << i << endl;
            cout << prev << " " << cur << endl;
            return false;
        }
        prev = cur;
    }
    inp.close();
    return true;
}

int numb_sort;

void test_sorting (my_type a[], int l, int r, cmp_type cmp, sort_type some_sorting, string name, string complexity){
    random_set(a, l, r);
    string outf = "output_" + name + ".txt";
    fstream fout(outf.c_str(), fstream::out);
    cnt_ops = 0;

    output_array(a, l, r, fout);
    some_sorting(a, l, r, cmp);
    output_array(a, l, r, fout);

    fout.close();

    cout << outf << " ";
    cout << (is_sorted_arr(outf, cmp, r - l + 1) ? "OK" : "NOT SORTED") << endl;

    info_file << "Sorting N" << ++numb_sort << endl;
    info_file << complexity << endl;
    info_file << name << " " << cnt_ops << " ops\n";
    info_file << endl;
}

int n;
my_type A[N];

int main()
{
    //freopen ("input.txt", "r", stdin);
    //freopen ("output.txt", "w", stdout);
    //cin >> n;
    n = N;

    test_sorting(A, 0, n - 1, lower, quick_sort, "quick_sort", "N * logN (worst N ^ 2)");
    test_sorting(A, 0, n - 1, lower, heap_sort, "heap_sort", "N * logN");
    test_sorting(A, 0, n - 1, lower, btree_sort, "btree_sort", "N * logN (Cartesian randomized tree) (worst N ^ 2)");
    test_sorting(A, 0, n - 1, lower, top_sort, "top_sort", "N ^ 2");
    test_sorting(A, 0, n - 1, lower, introsort, "intro_sort", "N * logN");
    test_sorting(A, 0, n - 1, lower, merge_sort, "merge_sort", "N * logN, O(1) memory");
    return 0;
}

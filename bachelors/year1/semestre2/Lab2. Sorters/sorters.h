#include <memory.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

int rand16();
int rand32();
int rand(int l, int r);
double rand(double l, double r);

typedef double my_type;
typedef bool(*cmp_type)(my_type, my_type);
typedef void(*sort_type)(my_type[], int, int, cmp_type);

void quick_sort(my_type a[], int l, int r, cmp_type comp);
void heap_sort(my_type a[], int l, int r, cmp_type comp);
void btree_sort(my_type a[], int l, int r, cmp_type comp);
void top_sort(my_type a[], int l, int r, cmp_type comp);
void introsort(my_type a[], int l, int r, cmp_type comp);
void merge_sort(my_type a[], int l, int r, cmp_type comp);
void bucket_sort(my_type a[], int l, int r, cmp_type comp);
void patience_sort(my_type a[], int l, int r, cmp_type comp);


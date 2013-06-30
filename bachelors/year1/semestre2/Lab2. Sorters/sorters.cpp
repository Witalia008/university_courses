#include "sorters.h"

int rand16() { return rand() % (1 << 16); }
int rand32() { return rand16() << 16 || rand16(); }
int rand (int l, int r) { return l + rand() % (r - l); }
double rand(double l, double r) { return rand(ceil(l * 100), floor(r * 100)) / 100.0; }

void quick_sort (my_type a[], int l, int r, cmp_type comp) {
    if (l >= r - 1) {
        if (!comp(a[l], a[r]))
            swap(a[l], a[r]);
        return ;
    }
    my_type etalon = a[rand(l, r)];
    int i = l, j = r;
    while (i < j) {
        while (comp(a[i], etalon))
            i++;
        while (comp(etalon, a[j]))
            j--;
        if (i < j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (i < r)
        quick_sort(a, i, r, comp);
    if (j > l)
        quick_sort(a, l, j, comp);
}

void heap_sort (my_type a[], int l, int r, cmp_type comp) {
    struct {
        bool operator ()(my_type *a, int cur_vertex, cmp_type cmp) {
            while (cur_vertex > 0 && cmp(a[cur_vertex], a[(cur_vertex - 1) / 2])) {
                swap(a[cur_vertex], a[(cur_vertex - 1) / 2]);
                cur_vertex = (cur_vertex - 1) / 2;
            }
        }
    } shift_up;
    struct {
        bool operator ()(my_type *a, int cur_vertex, int num_vert, cmp_type cmp){
            while (cur_vertex * 2 + 1 < num_vert) {
                int max_child = cur_vertex;

                if (cmp(a[cur_vertex * 2 + 1], a[cur_vertex]))
                    max_child = cur_vertex * 2 + 1;
                if (cur_vertex * 2 + 2 < num_vert && cmp(a[cur_vertex * 2 + 2], a[max_child]))
                    max_child = cur_vertex * 2 + 2;

                if (max_child == cur_vertex) {
                    cur_vertex = num_vert;
                } else {
                    swap(a[cur_vertex], a[max_child]);
                    cur_vertex = max_child;
                }
            }
        }
    } shift_down;
    for (int i = l; i <= r; i++)
        shift_up(&a[l], i - l, comp);
    for (int i = r; i > l; i--) {
        swap(a[l], a[i]);
        shift_down(&a[l], 0, i - l, comp);
    }
    for (int i = l; i < r - i + l; i++)
        swap(a[i], a[r - i + l]);
}

struct dtree {
    my_type key;
    int prior;
    bool used;
    dtree *left_son, *right_son;
    dtree() {}
    dtree(my_type _key) : key(_key), prior(rand32()), left_son(0), right_son(0), used(false) {}
};

dtree *merge(dtree *left_part, dtree *right_part) {
    if (!left_part || !right_part)
        return left_part ? left_part : right_part;
    else {
        if (left_part->prior > right_part->prior) {
            left_part->right_son = merge(left_part->right_son, right_part);
            return left_part;
        } else {
            right_part->left_son = merge(left_part, right_part->left_son);
            return right_part;
        }
    }
}

void split(dtree *cur_node, my_type key, dtree *&left_part, dtree *&right_part, cmp_type cmp) {
    if (!cur_node)
        return void(left_part = right_part = 0);
    if (cmp(key, cur_node->key)) {
        split(cur_node->left_son, key, left_part, cur_node->left_son, cmp);
        right_part = cur_node;
    } else {
        split(cur_node->right_son, key, cur_node->right_son, right_part, cmp);
        left_part = cur_node;
    }
}

void insert(dtree *&cur_node, dtree *item, cmp_type cmp){
    if (!cur_node)
        return void(cur_node = item);
    if (item->prior > cur_node->prior) {
        split(cur_node, item->key, item->left_son, item->right_son, cmp);
        cur_node = item;
    } else {
        insert(cmp(item->key, cur_node->key) ? cur_node->left_son : cur_node->right_son, item, cmp);
    }
}

void out_elems(dtree *cur_node, my_type a[], int &pos){
    if (!cur_node)
        return;
    out_elems(cur_node->left_son, a, pos);
    a[pos++] = cur_node->key;
    out_elems(cur_node->right_son, a, pos);
    delete cur_node;
}

void btree_sort(my_type a[], int l, int r, cmp_type comp) {
    dtree *root = 0;
    for (int i = l; i <= r; i++)
        insert(root, new dtree(a[i]), comp);
    out_elems(root, a, l);
}

void ts_dfs (int v, my_type *source, int cnt_src_el, my_type *dest, int &insert_pos, bool *is_visited, cmp_type cmp) {
    is_visited[v] = true;
    for (int to = 0; to < cnt_src_el; to++)
        if (!is_visited[to] && cmp(source[v], source[to]))
            ts_dfs(to, source, cnt_src_el, dest, insert_pos, is_visited, cmp);
    dest[insert_pos--] = source[v];
}

void top_sort(my_type a[], int l, int r, cmp_type comp) {
    int n = r - l + 1;
    my_type *temp = new my_type[n];
    bool *is_visited = new bool[n];
    memcpy(temp, a + l, sizeof (my_type) * n);
    for (int i = 0; i < n; i++)
        is_visited[i] = false;
    for (int i = 0; i < n; i++)
        if (!is_visited[i])
            ts_dfs(i, temp, n, a, r, is_visited, comp);
    delete temp;
    delete is_visited;
}

void intro_sort(my_type a[], int l, int r, cmp_type comp, int max_deph, int deph) {
    if (l >= r - 1) {
        if (!comp(a[l], a[r]))
            swap(a[l], a[r]);
        return ;
    }
    if (deph > max_deph) {
        heap_sort(a, l, r, comp);
        return;
    }
    my_type etalon = a[rand(l, r)];
    int i = l, j = r;
    while (i < j) {
        while (comp(a[i], etalon))
            i++;
        while (comp(etalon, a[j]))
            j--;
        if (i < j) {
            swap (a[i], a[j]);
            i++;
            j--;
        }
    }
    if (i < r)
        intro_sort(a, i, r, comp, max_deph, deph + 1);
    if (j > l)
        intro_sort(a, l, j, comp, max_deph, deph + 1);
}

void introsort(my_type a[], int l, int r, cmp_type comp) {
    intro_sort(a, l, r, comp, ceil(log2f(double(r - l + 1))), 0);
}

void slow_sort(my_type a[], int l, int r, cmp_type comp) {
    for (int i = r; i > l; i--)
        for (int j = l; j < i; j++)
            if (comp(a[j + 1], a[j]))
                swap(a[j], a[j + 1]);
}

void swap_groups(my_type a[], int n, int p1, int p2) {
    for (int i = 0; i < n; i++)
        swap(a[i + p1], a[i + p2]);
}

void merge_groups(my_type a[], int n, int p1, int p2, int p3, cmp_type cmp) {
    swap_groups(a, n, p1, p3);
    int taken1 = 0, taken2 = 0;
    for (int i = 0; i < n * 2; i++) {
        if (taken2 == n || (taken1 < n && cmp(a[p3], a[p2]))){
            swap(a[p1++], a[p3++]);
            taken1++;
        } else {
            swap(a[p1++], a[p2++]);
            taken2++;
        }
    }
}

void merge(my_type *a, int n, cmp_type comp) {
    if (n <= 16) {
        slow_sort(a, 0, n - 1, comp);
        return ;
    }

    int group_sz = (int) sqrt(n * 1.0);
    int groups = n / group_sz - 1;
    int left = n % group_sz;

    int pos_gap = 0;
    while (pos_gap < groups * group_sz && (a[pos_gap] == a[pos_gap + 1] || comp(a[pos_gap], a[pos_gap + 1])))
        pos_gap++;

    left += group_sz;
    swap_groups(a, group_sz, pos_gap - pos_gap % group_sz, groups * group_sz);

    for (int i = 0; i < groups; i++) {
        int wh = i;
        for (int j = i; j < groups; j++)
            if (comp(a[j * group_sz], a[wh * group_sz]) ||
                a[j * group_sz] == a[wh * group_sz] &&
                comp(a[(j + 1) * group_sz - 1], a[(wh + 1) * group_sz - 1]))
                    wh = j;
        if (wh != i)
            swap_groups(a, group_sz, i * group_sz, wh * group_sz);
    }

    for (int i = 1; i < groups; i++)
        merge_groups(a, group_sz, (i - 1) * group_sz, i * group_sz, n - left, comp);

    slow_sort(a, n - 2 * left, n - 1, comp);

    for (int i = n - 2 * left; i >= left; i -= left)
        merge_groups(a, left, i - left, i, n - left, comp);

    slow_sort(a, 0, left * 2 - 1, comp);
    slow_sort(a, n - left, n - 1, comp);
}

void merge_sort(my_type a[], int l, int r, cmp_type comp) {
    int n = r - l + 1;
    my_type *A = a + l;
    for (int step = 1; step / 2 <= n; step *= 2)
        for (int i = 0; i < n; i += step) {
            int gr_sz = min(n, i + step) - i;
            merge(A + i, gr_sz, comp);
        }
}

void bucket_sort(my_type a[], int l, int r, cmp_type comp) {
    if (r - l + 1 <= 16) {
        slow_sort(a, l, r, comp);
        return;
    }

    bool sorted = true;
    for (int i = l + 1; i <= r; i++) {
        if (comp(a[i], a[i - 1]))
            sorted = false;
    }
    if (sorted)
        return;

    int m = r - l + 1;
    my_type *buckets[m + 1];
    int cnt_in_buck[m + 1];
    for (int i = 0; i <= m; i++)
        cnt_in_buck[i] = 0, buckets[i] = NULL;

    double max_num = a[l], min_num = a[l];
    for (int i = l; i <= r; i++) {
        max_num = max(max_num, a[i]);
        min_num = min(min_num, a[i]);
    }
    double one_buck_len = (max_num - min_num) / m;
    for (int i = l; i <= r; i++) {
        int cur_buck = floor((a[i] - min_num) / one_buck_len);
        buckets[cur_buck] = (my_type*) realloc(buckets[cur_buck], (cnt_in_buck[cur_buck] + 1) * sizeof(my_type));
        buckets[cur_buck][cnt_in_buck[cur_buck]++] = a[i];
    }
    for (int i = 0; i <= m; i++)
        if (cnt_in_buck[i]) {
            //slow_sort(buckets[i], 0, cnt_in_buck[i] - 1, comp);
            bucket_sort(buckets[i], 0, cnt_in_buck[i] - 1, comp);
            for (int j = 0; j < cnt_in_buck[i]; j++)
                a[l++] = buckets[i][j];
        }
}


void patience_sort(my_type a[], int l, int r, cmp_type comp) {
    int m = r - l + 1;
    my_type *stack[m];
    for (int i = 0; i < m; i++)
        stack[i] = 0;

    int cnt_st = 0;
    int cnt_in_st[m];
    for (int i = l; i <= r; i++)
        if (!cnt_st || stack[cnt_st - 1][cnt_in_st[cnt_st - 1] - 1] > a[i]) {
            stack[cnt_st] = (my_type*) malloc(sizeof (my_type));
            stack[cnt_st][0] = a[i];
            cnt_in_st[cnt_st] = 1;
            cnt_st++;
        } else {
            int left = 0, right = cnt_st - 1;
            while (left < right - 1) {
                int middle = (left + right) >> 1;
                if (stack[middle][cnt_in_st[middle] - 1] <= a[i])
                    right = middle;
                else
                    left = middle;
            }
            if (stack[left][cnt_in_st[left] - 1] <= a[i])
                right = left;
            stack[right] = (my_type*) realloc(stack[right], (cnt_in_st[right] + 1) * sizeof (my_type));
            stack[right][cnt_in_st[right]++] = a[i];
        }
    priority_queue<pair<my_type, int> > stack_top;
    for (int i = 0; i < cnt_st; i++)
        stack_top.push(make_pair(stack[i][cnt_in_st[i] - 1], i));
    while (!stack_top.empty()) {
        pair<my_type, int> cur = stack_top.top();
        stack_top.pop();
        a[r--] = cur.first;
        cnt_in_st[cur.second]--;
        if (cnt_in_st[cur.second])
            stack_top.push(make_pair(stack[cur.second][cnt_in_st[cur.second] - 1], cur.second));
    }
}

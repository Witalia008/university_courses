#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


using namespace std;
using namespace std::chrono;

/* class for varrier.
 * at some ponit of each thread (where barrier will be placed)
 * all threads will wait until counter (with which was initialized barrier) become zero
 * if we set counter to number of threads, then it will be point, where all
 * threads will be synchronized (wait until every thread reaches this point)
 */
class barrier
{
public:

    barrier(unsigned int count)
        : m_threshold(count), m_count(count), m_generation(0)
    {
    }

    bool wait()
    {
        /* get ownership of mutex */
        unique_lock<mutex> lock(m_mutex);
        unsigned int gen = m_generation;
        /* if counter gets zero - notify everyone that they can continue working */
        if (--m_count == 0)
        {
            m_generation++;
            m_count = m_threshold;
            m_cond.notify_all();
            return true;
        }
        /* we need to wait until it will be our time to move on */
        while (gen == m_generation)
            m_cond.wait(lock);
        return false;
    }

private:
    mutex m_mutex;
    condition_variable m_cond;
    unsigned int m_threshold;
    unsigned int m_count;
    unsigned int m_generation;
};

typedef vector<vector<int>> vvi;

/* Read graph from stdin.
 * is_matr says if graph is given by adjacency matrix (=true) or list of adjacency (=false)
 * function saves readed data into adjacency matrix - M
 * If between i and j doesn't exists edge, then M[i][j] = Inf (INT_MAX / 2)
 */
void read_graph(vvi &M, int &n, bool is_matr, bool is_oriented) {
    cin >> n;
    M.clear();
    M.resize(n);
    for (int i = 0; i < n; ++i)
        M[i].assign(n, INT_MAX / 2);
    if (is_matr) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                cin >> M[i][j];
                if (M[i][j] == -1)
                    M[i][j] = INT_MAX / 2;
            }
    } else {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int from, to, weight;
            cin >> from >> to >> weight;
            --from; --to;
            M[from][to] = min(M[from][to], weight);
            if (!is_oriented)
                M[to][from] = min(M[to][from], weight);
        }
    }
}

/* output distances to every vertex from vertex 'fr' */
void output_distances(const vvi &M, int fr) {
    for (int j = 0; j < M[fr].size(); ++j)
        if (j != fr)
            cout << (M[fr][j] >= INT_MAX / 2 ? -1 : M[fr][j]) << (j == M[fr].size() - 1 ? "" : " ");
    cout << endl;
}

/* output matrix of distances between every pair of vertices */
void output_matrix(const vvi &M, int n) {
    for (int i = 0; i < n; ++i)
        output_distances(M, i);
}

/* number of threads */
const int n_threads = 2;
barrier bar = barrier(n_threads);

/* function, that will be executed in each thread
 * M - adjacency matrix, which will be in future transformed to minimal distance matrix
 * id - number of thread
 * v_per_thr - how many vertices should this thread evaluate
 * it needs to evaluate vertices from id * v_per_thr to (i + 1) * v_per_thr - 1
 * as in floyd's algorithm, it runs over each k (after each step synchronizing with other threads)
 * and update answer for all pairs (i, j), where (1 <= i <= n) and (id * v_per_thr <= j <= (i + 1) * v_per_thr - 1)
 */
void floyd_multithread(vvi &M, int id, int v_per_thr) {
    int n = M.size();
    int from = id * v_per_thr;
    int to = min((id + 1) * v_per_thr, n);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i){
            for (int j = from; j < to; ++j)
                if (M[i][j] > M[i][k] + M[k][j])
                    M[i][j] = M[i][k] + M[k][j];}

        bar.wait();    //sync
    }
}

/* runs n_thread threads and wait until they finish */
void floyd(vvi &M, int n) {
    int per_thread = max(1, n / n_threads);
    vector<thread> threads(n_threads);
    for (int i = 0; i < n_threads; ++i)
        threads[i] = thread(floyd_multithread, ref(M), i, per_thread);
    for (int i = 0; i < n_threads; ++i)
        threads[i].join();
}

/* non-parallelized version of algorithm */
void floyd_slow(vvi &M, int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (M[i][j] > M[i][k] + M[k][j])
                    M[i][j] = M[i][k] + M[k][j];
}    

/* one one of the version of algorithm and comute running time (with outputting results)*/
void run(vvi M, int n, void (*func)(vvi&, int)) {
    auto start = high_resolution_clock::now();
    floyd(M, n);
    cout << "finished in " << duration_cast<duration<double>>(high_resolution_clock::now() - start).count() << " seconds" << endl;
    output_distances(M, 0);
}

vector<vector<int>> M;
//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    read_graph(M, n, false, false);
    run(M, n, floyd_slow);
    run(M, n, floyd);
    return 0;
}
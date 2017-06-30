// MPIHelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <memory.h>
#include <stdarg.h>

using namespace std;

const double EPS = 1e-7;
const int N = 20000;

//#define DEBUG
//#define LOGG

void log(const char *format, ...)
{
#ifdef LOGG
    va_list arg;
    va_start(arg, format);
    vfprintf(stderr, format, arg);
    va_end(arg);
    fflush(stderr);
#endif
}

void read_data(int &n, double *&F)
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    F = new double[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &F[i]);
    }
    fclose(stdin);
}

void gen_data(int &n, double *&F)
{
    n = N;
    F = new double[n];
    for (int i = 0; i < n; ++i)
    {
        F[i] = rand() / 1e5;
    }
}

void print_ans(char *msg, double tm, int n, double *ans)
{
    printf("%s took %.5lf ms.\n", msg, tm);
    for (int i = 0; i < n && i < 10; ++i)
    {
        printf("%.5lf ", ans[i]);
    }
    if (n > 10)
        printf("...");
    printf("\n");
}

double *deepcopy(int n, double *F)
{
    double *res = new double[n];
    for (int i = 0; i < n; ++i)
    {
        res[i] = F[i];
    }
    return res;
}

void seq_bubble(int n, double *F)
{
    bool sorted = false;
    for (int i = 1; i < n && !sorted; ++i)
    {
        sorted = true;
        for (int j = (i & 1); j + 1 < n; j += 2)
        {
            if (F[j] > F[j + 1])
            {
                swap(F[j], F[j + 1]);
                sorted = false;
            }
        }
    }
}

// can't change
const int root = 0;
int sz, rnk;
int n = 0, m, fr, to;
double *F = NULL;
double *A = NULL;
bool sorted = false;

void exchange(bool even_forw)
{
    double temp;
    bool exch_left = (even_forw ^ (1 - fr % 2)) && fr != 0;
    bool exch_right = (even_forw ^ (1 - to % 2)) && to != n;
    if (exch_left)
    {
        MPI_Send(&A[0], 1, MPI_DOUBLE, rnk - 1, 0, MPI_COMM_WORLD);
        log("%d send to %d elem %d (%.3lf)\n", rnk, rnk - 1, fr, A[0]);
    }
    if (exch_right)
    {
        MPI_Send(&A[m - 1], 1, MPI_DOUBLE, rnk + 1, 1, MPI_COMM_WORLD);
        log("%d send to %d elem %d (%.3lf)\n", rnk, rnk + 1, to - 1, A[m - 1]);
    }
    for (int i = (even_forw ^ (1 - fr % 2)); i + 1 < m; i += 2)
    {
        log("Compare %d and %d\n", i, i + 1);
        if (A[i] > A[i + 1])
        {
            sorted = false;
            log("Bigger %d and %d\n", i, i + 1);
            swap(A[i], A[i + 1]);
        }
    }
    if (exch_left)
    {
        MPI_Recv(&temp, 1, MPI_DOUBLE, rnk - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        log("%d recv from %d elem %d (%.3lf)\n", rnk, rnk - 1, fr - 1, temp);
        if (temp > A[0])
        {
            sorted = false;
            A[0] = temp;
        }
    }
    if (exch_right)
    {
        MPI_Recv(&temp, 1, MPI_DOUBLE, rnk + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        log("%d recv from %d elem %d (%.3lf)\n", rnk, rnk + 1, to, temp);
        if (temp < A[m - 1])
        {
            sorted = false;
            A[m - 1] = temp;
        }
    }
}

void finalise()
{
    if (F != NULL)
    {
        delete[] F;
    }
    if (rnk == root)
    {
        fclose(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    exit(0);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);

    if (rnk == root)
    {
        freopen("output.txt", "w", stdout);
        gen_data(n, F);
        //read_data(n, F);
        double *F1 = deepcopy(n, F);
        double start = MPI_Wtime();
        seq_bubble(n, F1);
        double stop = MPI_Wtime();
        print_ans("Sequential Bubble Sort", stop - start, n, F1);
    }

    double start = MPI_Wtime();

    // send out n
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    m = (n + sz - 1) / sz;
    fr = rnk * m;
    to = min(n, (rnk + 1) * m);
    m = to - fr;
    A = new double[m];

    // Send out parts to each processor
    if (rnk == root)
    {
        for (int i = 0; i < m; ++i)
        {
            A[i] = F[i];
        }
        for (int i = m, nn = 1; i < n; i += m, ++nn)
        {
            MPI_Send(F + i, min(i + m, n) - i, MPI_DOUBLE, nn, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(A, to - fr, MPI_DOUBLE, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // Iterate
    int cc = 0;
    for (bool it = true; cc++ < n && !sorted; it = !it)
    {
        sorted = true;

        log("Prep for exchange\n");
        exchange(it);
        MPI_Barrier(MPI_COMM_WORLD);
        log("exchs completed\n");

        // Gather 'sorted' value
        if (rnk != root)
        {
            MPI_Send(&sorted, 1, MPI_C_BOOL, root, 0, MPI_COMM_WORLD);
        }
        else
        {
            for (int i = 1; i < sz; ++i)
            {
                bool srt;
                MPI_Recv(&srt, 1, MPI_C_BOOL, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sorted &= srt;
            }
        }
        //MPI_Barrier(MPI_COMM_WORLD);
        // Spread 'sorted' value
        MPI_Bcast(&sorted, 1, MPI_C_BOOL, root, MPI_COMM_WORLD);
        //MPI_Barrier(MPI_COMM_WORLD);
    }

    // Send data to the centre
    if (rnk != root)
    {
        MPI_Send(A, m, MPI_DOUBLE, root, 0, MPI_COMM_WORLD);
    }

    // Gather data
    if (rnk == root)
    {
        for (int i = 0; i < m; ++i)
        {
            F[i] = A[i];
        }
        for (int i = m, nn = 1; i < n; i += m, ++nn)
        {
            MPI_Recv(F + i, min(i + m, n) - i, MPI_DOUBLE, nn, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rnk == root)
    {
        double stop = MPI_Wtime();
        print_ans("Parallel Bubble Sort", stop - start, n, F);
    }

    finalise();

    return 0;
}

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
const int N = 50000;

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
    for (int i = 0; i < n; ++i)
    {
        printf("%.5lf ", ans[i]);
    }
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
int n = 0, m;
double *F = NULL;
double *A = NULL;
double *B = NULL;
bool sorted = false;

void exchange(bool it)
{
    int rnk_o = (it ? rnk + 1 : rnk - 1 + sz) % sz;
    int to_exc = m, st = 0;
    if (it && (n - 1) % sz == rnk)
        --to_exc; // last element is not exchanged with next
    if (!it && rnk == 0)
        ++st, --to_exc; // first element is not exchanged with previous
    // Send my chunk
    log("%d sends to %d %d bytes\n", rnk, rnk_o, to_exc);
    MPI_Send(A + st, to_exc, MPI_DOUBLE, rnk_o, 1, MPI_COMM_WORLD);
    // Get other chunk
    log("%d receives from %d %d bytes\n", rnk, rnk_o, to_exc);
    MPI_Recv(B, to_exc, MPI_DOUBLE, rnk_o, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Replace wrong elements
    for (int i = 0; i < to_exc; ++i)
    {
        if (it && B[i] < A[st + i] || !it && B[i] > A[st + i])
        {
            A[st + i] = B[i];
            sorted = false;
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

    if (sz & 1)
    {
        log("Even number of processors required");
        finalise();
    }
    double start = MPI_Wtime();

    // send out n
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    A = new double[(n + sz - 1) / sz];
    m = 0;

    // Send out parts to each processor
    if (rnk == root)
    {
        for (int i = 0; i < n; ++i)
        {
            if (i % sz)
            {
                MPI_Send(&F[i], 1, MPI_DOUBLE, i % sz, 1, MPI_COMM_WORLD);
            }
            else
            {
                A[m++] = F[i];
            }
        }
    }
    else
    {
        for (int i = rnk; i < n; i += sz)
        {
            MPI_Recv(&A[m++], 1, MPI_DOUBLE, root, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    B = new double[m];
    MPI_Barrier(MPI_COMM_WORLD);

    // Iterate
    for (bool it = true; !sorted; it = !it)
    {
        sorted = true;

        log("Prep for exchange\n");
        exchange(it ^ (rnk & 1));
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
        MPI_Barrier(MPI_COMM_WORLD);
        // Spread 'sorted' value
        MPI_Bcast(&sorted, 1, MPI_C_BOOL, root, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Send data to the centre
    if (rnk != root)
    {
        MPI_Send(A, m, MPI_DOUBLE, root, 0, MPI_COMM_WORLD);
    }

    // Gather data
    if (rnk == root)
    {
        for (int i = 0; i < sz; ++i)
        {
            if (i != root)
            {
                MPI_Recv(B, (n - i) / sz + 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            else
            {
                B = A;
            }
            for (int j = i, k = 0; j < n; j += sz, ++k)
            {
                F[j] = B[k];
            }
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

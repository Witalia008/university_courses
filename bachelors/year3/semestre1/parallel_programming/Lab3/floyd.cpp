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
const int N = 2000;

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

void read_data(int &n, double **&F)
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    F = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        F[i] = new double[n + 1];
        for (int j = 0; j < n + 1; ++j)
        {
            scanf("%lf", &F[i][j]);
        }
    }
    fclose(stdin);
}

void gen_data(int &n, double **&F)
{
    n = N;
    F = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        F[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            F[i][j] = rand() / 1e4;
        }
        F[i][i] = 0;
    }
}

void print_ans(char *msg, double tm, int n, double **ans)
{
    printf("%s took %.5lf ms.\n", msg, tm);
    for (int i = 0; i < min(n, 10); ++i)
    {
        for (int j = 0; j < min(n, 10); ++j)
        {
            printf("%.5lf ", ans[i][j]);
        }
        if (n > 10)
            printf("...");
        printf("\n");
    }
    if (n > 10)
        printf("...\n");
}

double **deepcopy(int n, double **F)
{
    double **res = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        res[i] = new double[n + 1];
        for (int j = 0; j <= n; ++j)
        {
            res[i][j] = F[i][j];
        }
    }
    return res;
}

void seq_floyd(int n, double **F)
{
    //return;
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                F[i][j] = min(F[i][j], F[i][k] + F[k][j]);
            }
        }
    }
}

// can't change
const int root = 0;
int sz, rnk;
int n = 0, m, fr, to, mm;
double **F = NULL;
double **A = NULL;
double *row;

void finalise()
{
    if (F != NULL)
    {
        for (int i = 0; i < (rnk == root ? n : m); ++i)
        {
            delete[] F[i];
        }
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
        double **F1 = deepcopy(n, F);
        double start = MPI_Wtime();
        seq_floyd(n, F1);
        double stop = MPI_Wtime();
        print_ans("Sequential Floyd", stop - start, n, F1);
    }

    double start = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

    m = (n + sz - 1) / sz;
    fr = rnk * m;
    to = min(n, (rnk + 1) * m);
    mm = to - fr;
    log("%d: %d - %d\n", rnk, fr, to);

    // Distribute the data
    if (rnk == root)
    {
        A = F;
        for (int i = m; i < 2 * m && i < n; ++i)
        {
            for (int j = i; j < n; j += m)
            {
                MPI_Send(F[j], n, MPI_DOUBLE, j / m, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        A = new double *[mm];
        for (int i = fr; i < to; ++i)
        {
            A[i - fr] = new double[n];
            MPI_Recv(A[i - fr], n, MPI_DOUBLE, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    row = new double[m];
    // Algo
    int cnt_op = 0;
    for (int k = 0; k < n; ++k)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        // Distribute row K
        int k_owner = k / m;
        if (rnk == k_owner)
        {
            for (int i = 0; i < sz; ++i)
            {
                log("%d: sending row %d (%d-%d) to %d\n", rnk, k, i * m, min(n, (i + 1) * m), i);
                if (i == rnk)
                {
                    for (int j = fr; j < to; ++j)
                    {
                        row[j - fr] = A[k - fr][j];
                    }
                }
                else
                {
                    MPI_Send(&A[k - fr][i * m],
                             min(n, (i + 1) * m) - i * m,
                             MPI_DOUBLE, i, k, MPI_COMM_WORLD);
                }
            }
        }
        else
        {
            MPI_Recv(row, mm, MPI_DOUBLE, k_owner, k, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // sz chunks to process
        int ch_own = rnk, ch_fr = fr, ch_to = to;
        for (int it = 0; it < sz; ++it)
        {
#ifdef DEBUG
            if (rnk == root)
            {
                log("row %d: chunk %d-%d\n", k, ch_fr, ch_to);
                for (int j = ch_fr; j < ch_to; ++j)
                {
                    log("%.3lf ", row[j - ch_fr]);
                }
                log("\n");
            }
#endif
            log("%d iterating (%d-%d)x(%d-%d)\n", rnk, fr, to, ch_fr, ch_to);
            for (int i = 0; i < mm; ++i)
            {
                double A_ik = A[i][k];
                int mmm = ch_to - ch_fr;
                for (int j = 0, jj = ch_fr; j < mmm; ++j, ++jj)
                {
                    //++cnt_op;
                    if (A_ik + row[j] < A[i][jj])
                    {
                        A[i][jj] = A_ik + row[j];
                    }
                }
            }

            // Send chunk to next processor
            log("%d proceeding row %d (%d-%d) to %d\n", rnk, k, ch_fr, ch_to, (rnk + 1) % sz);
            MPI_Send(row, ch_to - ch_fr, MPI_DOUBLE, (rnk + 1) % sz, ch_fr, MPI_COMM_WORLD);

            ch_own = (ch_own - 1 + sz) % sz;
            ch_fr = ch_own * m;
            ch_to = min(n, (ch_own + 1) * m);

            // Receive chunk from previous processor
            log("%d receiving row %d (%d-%d) from %d\n", rnk, k, ch_fr, ch_to, (rnk - 1 + sz) % sz);
            MPI_Recv(row, ch_to - ch_fr, MPI_DOUBLE, (rnk - 1 + sz) % sz, ch_fr, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    log("%d: CNT_OP = %d\n", rnk, cnt_op);

    MPI_Barrier(MPI_COMM_WORLD);
    // Gather the data
    if (rnk == root)
    {
        for (int i = m; i < 2 * m && i < n; ++i)
        {
            for (int j = i; j < n; j += m)
            {
                log("root recv from %d. Tag %d\n", j / m, j);
                MPI_Recv(F[j], n, MPI_DOUBLE, j / m, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }
    else
    {
        for (int i = fr; i < to; ++i)
        {
            log("%d sends to root. Tag %d\n", rnk, i);
            MPI_Send(A[i - fr], n, MPI_DOUBLE, root, i, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rnk == root)
    {
        double stop = MPI_Wtime();
        print_ans("Parallel Floyd", stop - start, n, F);
    }

    finalise();

    return 0;
}

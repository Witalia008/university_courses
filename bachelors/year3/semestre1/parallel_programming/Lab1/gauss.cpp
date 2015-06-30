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
const int N = 1000;

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
        F[i] = new double[n + 1];
        for (int j = 0; j < n + 1; ++j)
        {
            F[i][j] = rand() / 1e5;
        }
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

void seq_gauss(int n, double **F, double *&ans)
{
    ans = new double[n];
    for (int i = 0; i < n - 1; ++i)
    {
        int sel = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (fabs(F[j][i]) > fabs(F[sel][i]))
            {
                sel = j;
            }
        }
        if (sel != i)
        {
            for (int j = i; j <= n; ++j)
            {
                swap(F[i][j], F[sel][j]);
            }
        }
        if (fabs(F[i][i]) < EPS)
        {
            break;
        }
        for (int j = 0; j < n; ++j)
        {
            if (j != i)
            {
                double c = F[j][i] / F[i][i];
                for (int k = i; k <= n; ++k)
                {
                    F[j][k] -= c * F[i][k];
                }
            }
        }

#ifdef DEBUG
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                log("%.3lf ", F[i][j]);
            }
            log("\n");
        }
#endif
    }
#ifdef DEBUG
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            log("%.3lf ", F[i][j]);
        }
        log("\n");
    }
#endif
    for (int i = n - 1; i >= 0; --i)
    {
        ans[i] = F[i][n];
        for (int j = i + 1; j < n; ++j)
        {
            ans[i] -= F[i][j] * ans[j];
        }
        ans[i] /= F[i][i];
    }
#ifdef DEBUG
    for (int i = 0; i < n; ++i)
    {
        log("%.3lf ", ans[i]);
    }
#endif
}

// can't change
const int root = 0;
int sz, rnk;
int n = 0, m;
double **F = NULL;
int cur_row;

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
    // without root
    sz -= 1;

    if (rnk == root)
    {
        freopen("output.txt", "w", stdout);
        gen_data(n, F);
        //read_data(n, F);
        double **F1 = deepcopy(n, F);
        double start = MPI_Wtime();
        double *ans;
        seq_gauss(n, F1, ans);
        double stop = MPI_Wtime();
        print_ans("Sequential Gauss", stop - start, n, ans);
    }
    if (sz == 0)
    {
        log("Only one core\n");
        finalise();
    }
    double start = MPI_Wtime();

    // Broadacst n
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
    log("ID = %d, N = %d\n", rnk, n);

    // Distribute rows
    MPI_Barrier(MPI_COMM_WORLD);
    if (rnk == root)
    {
        for (int i = 0; i < n; ++i)
        {
            MPI_Send(F[i], n + 1, MPI_DOUBLE, i % sz + 1, 1, MPI_COMM_WORLD);
            log("Sent row %d to %d\n", i, i % sz + 1);
        }
    }
    else
    {
        m = (n + sz - 1) / sz;
        F = new double *[m];
        for (int i = 0; i < m; ++i)
        {
            F[i] = new double[n + 1];
        }
        log("%d\n", m);

        for (int i = rnk - 1, j = 0; i < n; i += sz, ++j)
        {
            MPI_Recv(F[j], n + 1, MPI_DOUBLE, root, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            log("Participant %d receiveed row %d\n", rnk, i);
        }
    }

    // Forward iteration
    MPI_Barrier(MPI_COMM_WORLD);
    cur_row = rnk - 1;
    double *ith = new double[n + 1];
    double *temp = NULL;
    if (rnk == root)
    {
        temp = new double[n + 1];
    }
    for (int i = 0; i + 1 < n; ++i)
    {
        // Get maximum
        int mx = -1;
        double mval = 0;
        if (rnk == root)
        {
            for (int j = 0; j < sz; ++j)
            {
                int cur = -1;
                double val;
                MPI_Recv(&cur, 1, MPI_INT, j + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&val, 1, MPI_DOUBLE, j + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (cur != -1 && (mx == -1 || fabs(val) > fabs(mval)))
                {
                    mx = cur;
                }
            }
        }
        else
        {
            for (int j = cur_row; j < n; j += sz)
            {
                if (mx == -1 || fabs(F[j / sz][i]) > fabs(F[mx / sz][i]))
                {
                    mx = j;
                }
            }
            MPI_Send(&mx, 1, MPI_INT, root, 1, MPI_COMM_WORLD);
            MPI_Send(&F[mx / sz][i], 1, MPI_DOUBLE, root, 1, MPI_COMM_WORLD);
        }
        if (rnk == root)
        {
            log("Step %d, max = %d\n", i, mx);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        // Broadcast found maximum
        MPI_Bcast(&mx, 1, MPI_INT, root, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        // swap rows
        if (mx != i)
        {
            if (rnk == root)
            {
                // Get ith from owner and send to new owner
                MPI_Recv(ith, n + 1, MPI_DOUBLE, i % sz + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(temp, n + 1, MPI_DOUBLE, mx % sz + 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(ith, n + 1, MPI_DOUBLE, mx % sz + 1, 2, MPI_COMM_WORLD);
                MPI_Send(temp, n + 1, MPI_DOUBLE, i % sz + 1, 1, MPI_COMM_WORLD);
            }
            else
            {
                if (mx % sz == rnk - 1)
                {
                    // Send mxth to root
                    MPI_Send(F[mx / sz], n + 1, MPI_DOUBLE, root, 2, MPI_COMM_WORLD);
                }
                if (i % sz == rnk - 1)
                {
                    // Send ith to root
                    MPI_Send(F[i / sz], n + 1, MPI_DOUBLE, root, 1, MPI_COMM_WORLD);
                }
                if (mx % sz == rnk - 1)
                {
                    // Receive ith from root
                    MPI_Recv(F[mx / sz], n + 1, MPI_DOUBLE, root, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
                if (i % sz == rnk - 1)
                {
                    // get mxth from root
                    MPI_Recv(F[i / sz], n + 1, MPI_DOUBLE, root, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
        }
#ifdef DEBUG
        if (rnk == 2)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n + 1; ++j)
                {
                    log("%.3lf ", F[i][j]);
                }
                log("\n");
            }
        }
#endif
        MPI_Barrier(MPI_COMM_WORLD);
        // move somebody from ith row
        if (rnk != root && cur_row == i)
        {
            cur_row += sz;
            // broadcast ith row for reduction
            memcpy(ith, F[i / sz], sizeof(double) * (n + 1));
        }
        MPI_Bcast(ith, n + 1, MPI_DOUBLE, i % sz + 1, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
#ifdef DEBUG
        if (rnk == root)
        {
            for (int j = 0; j < n + 1; ++j)
            {
                log("%.3lf ", ith[j]);
            }
            log("\n");
        }
#endif

        // reduce rows
        if (rnk != root)
        {
            for (int row = cur_row, r = cur_row / sz; row < n; row += sz, ++r)
            {
                log("%d reduces row %d\n", rnk, row);
                double coef = F[r][i] / ith[i];
                for (int j = i; j < n + 1; ++j)
                {
                    F[r][j] -= ith[j] * coef;
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    // Reverse iteration
    double *anss = new double[n];
    if (rnk != root)
    {
        for (int i = n - 1; i >= 0; --i)
        {
            if (i % sz == rnk - 1)
            {
                if (i != n - 1)
                {
                    // receive from guy (rnk - 1) + 1
                    MPI_Recv(anss, n, MPI_DOUBLE, rnk % sz + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    log("%d recvd from %d\n", rnk, rnk % sz + 1);
                }
                // find ith answer
                anss[i] = F[i / sz][n];
                for (int j = i + 1; j < n; ++j)
                {
                    anss[i] -= anss[j] * F[i / sz][j];
                }
                anss[i] /= F[i / sz][i];
                // send to guy (rnk - 1) - 1 or root
                MPI_Send(anss, n, MPI_DOUBLE, i ? ((rnk - 2 + sz) % sz + 1) : root, 1, MPI_COMM_WORLD);
                log("%d sent to %d\n", rnk, i ? (rnk - 2 + sz) % sz + 1 : root);
            }
        }
    }
    else
    {
        MPI_Recv(anss, n, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (rnk == root)
    {
        double stop = MPI_Wtime();
        print_ans("Parallel Gauss", stop - start, n, anss);
    }
    delete[] anss;

    finalise();

    return 0;
}

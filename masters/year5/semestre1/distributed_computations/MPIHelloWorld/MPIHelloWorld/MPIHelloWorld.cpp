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
#include <limits.h>

using namespace std;

const double EPS = 1e-3;
const int N = 500;

//#define DEBUG
//#define LOGG

void log(const char *format, ...) {
#ifdef LOGG
    va_list arg;
    va_start(arg, format);
    vfprintf(stderr, format, arg);
    va_end(arg);
    fflush(stderr);
#endif
}

void read_data(int &n, double** &F) {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    F = new double*[n];
    for (int i = 0; i < n; ++i) {
        F[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            scanf("%lf", &F[i][j]);
        }
    }
    fclose(stdin);
}

void gen_data(int &n, double ** &F) {
    n = N;
    F = new double*[n];
    for (int i = 0; i < n; ++i) {
        F[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            F[i][j] = rand() / 1e4;
        }
    }
}

void print_ans(char *msg, double tm, int n, double **ans) {
    printf("%s took %.5lf ms.\n", msg, tm);
    for (int i = 0; i < min(n, 3); ++i) {
        for (int j = 0; j < min(n, 12); ++j) {
            printf("%.5lf ", ans[i][j]);
        }
        if (n > 12) printf("...");
        printf("\n");
    }
    if (n > 12) printf("...\n");
}

double **deepcopy(int n, double **F) {
    double ** res = new double*[n];
    for (int i = 0; i < n; ++i) {
        res[i] = new double[n];
        for (int j = 0; j <= n; ++j) {
            res[i][j] = F[i][j];
        }
    }
    return res;
}

void seq_gz(int n, double **F, double **U, double h) {
    double dmax;
    do {
        dmax = 0;
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                double temp = U[i][j];
                U[i][j] = 0.25 * (U[i - 1][j] + U[i + 1][j]
                    + U[i][j - 1] + U[i][j + 1] - h * h * F[i][j]);
                double dx = fabs(temp - U[i][j]);
                if (dx > dmax) {
                    dmax = dx;
                }
            }
        }
    } while (dmax > EPS);
}

// can't change
const int root = 0;
int sz, rnk;
int n = 0, m, fr, to, mm;
double **F = NULL, **U = NULL;
double **A = NULL, **B = NULL;
double h, dmax, dloc;

void finalise() {
    if (F != NULL) {
        for (int i = 0; i < (rnk == root ? n : m); ++i) {
            delete[] F[i];
        }
        delete[] F;
    }
    if (rnk == root) {
        fclose(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    exit(0);
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);

    if (rnk == root) {
        freopen("output.txt", "w", stdout);
        gen_data(n, F);
        gen_data(n, U);
        h = 0.1;
        //read_data(n, F);
        double **U1 = deepcopy(n, U);
        double start = MPI_Wtime();
        seq_gz(n, F, U1, h);
        double stop = MPI_Wtime();
        print_ans("F - matrix and value h:", h, n, F);
        print_ans("Sequential Gauss-Seidel", stop - start, n, U1);
    }

    double start = MPI_Wtime();
    
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(&h, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);

    m = (n + sz - 1) / sz;
    fr = rnk * m;
    to = min(n, (rnk + 1) * m);
    mm = to - fr;
    log("%d: %d - %d\n", rnk, fr, to);

    // Distribute the data
    if (rnk == root) {
        A = F;
        B = new double*[mm + 2];
        for (int i = 0; i < mm + 2; ++i) {
            B[i] = new double[n];
            if (i > 0 && i != mm + 1) {
                memcpy(B[i], U[i - 1], sizeof(double) * n);
            }
        }
        for (int i = m; i < 2 * m && i < n; ++i) {
            for (int j = i; j < n; j += m) {
                MPI_Send(F[j], n, MPI_DOUBLE, j / m, 0, MPI_COMM_WORLD);
                MPI_Send(U[j], n, MPI_DOUBLE, j / m, 1, MPI_COMM_WORLD);
            }
        }
    }
    else {
        A = new double*[mm];
        B = new double*[mm + 2]; // two extra lines from prev and next procs
        B[0] = new double[n];
        B[mm + 1] = new double[n];
        for (int i = fr; i < to; ++i) {
            A[i - fr] = new double[n];
            B[i - fr + 1] = new double[n];
            MPI_Recv(A[i - fr], n, MPI_DOUBLE, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(B[i - fr + 1], n, MPI_DOUBLE, root, 1, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }
    }

    // ALGO HERE
    do {
        log("%d: Send row to next proc\n", rnk);
        MPI_Sendrecv(B[mm], n, MPI_DOUBLE, (rnk + 1) % sz, 0,
            B[0], n, MPI_DOUBLE, (rnk - 1 + sz) % sz, 0, 
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        log("%d: Send row to prev proc\n", rnk);
        MPI_Sendrecv(B[1], n, MPI_DOUBLE, (rnk - 1 + sz) % sz, 0,
            B[m + 1], n, MPI_DOUBLE, (rnk + 1) % sz, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Barrier(MPI_COMM_WORLD);

        log("%d: running algo\n", rnk);
        dloc = 0;
        for (int i = 1 + (fr == 0); i <= mm - (to == n); ++i) {
            //log("%d: i = %d\n", rnk, i);
            for (int j = 1; j < n - 1; ++j) {
                double temp = B[i][j];
                if (rnk == 0) {
                    log("%d: (%d, %d): %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n", rnk, i, j,
                        B[i - 1][j], B[i + 1][j], B[i][j - 1], B[i][j + 1], A[i - 1][j], h);
                }
                B[i][j] = 0.25 * (B[i - 1][j] + B[i + 1][j]
                    + B[i][j - 1] + B[i][j + 1] - h * h * A[i - 1][j]);
                double dx = temp - B[i][j];
                if (dx < 0) dx = -dx;
                if (dx > dloc) {
                    //log("%d: (%d, %d) -> %.3lf\n", rnk, i - 1 + fr, j, dx);
                    dloc = dx;
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);

        log("%d: dloc = %.3lf\n", rnk, dloc);
        MPI_Allreduce(&dloc, &dmax, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    } while (dmax > EPS);

    MPI_Barrier(MPI_COMM_WORLD);
    // Gather the data
    if (rnk == root) {
        for (int i = 0; i < m; ++i) {
            memcpy(U[i], B[i + 1], sizeof(double) * n);
        }
        for (int i = m; i < 2 * m && i < n; ++i) {
            for (int j = i; j < n; j += m) {
                log("root recv from %d. Tag %d\n", j / m, j);
                MPI_Recv(U[j], n, MPI_DOUBLE, j / m, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }
    else {
        for (int i = fr; i < to; ++i) {
            log("%d sends to root. Tag %d\n", rnk, i);
            MPI_Send(B[i - fr + 1], n, MPI_DOUBLE, root, i, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rnk == root) {
        double stop = MPI_Wtime();
        print_ans("Parallel Gauss-Seidel", stop - start, n, U);
    }

    finalise();

    return 0;
}


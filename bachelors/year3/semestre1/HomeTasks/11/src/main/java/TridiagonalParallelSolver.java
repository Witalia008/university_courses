import Jama.Matrix;

/**
 * Created by Witalia on 20.11.2014.
 */
public class TridiagonalParallelSolver {
    public static VectorM solve(Matrix L, VectorM R, int nThreads) {
        return solve(new TridiagonalCompact(L), R, nThreads);
    }
    public static VectorM solve(TridiagonalCompact L, VectorM R, int nThreads) {
        if (nThreads <= 0) {
            return null;
        }
        while (L.getRowDimension() % nThreads != 0) --nThreads;
        if (nThreads == 1) {
            SLETridiagonalSolver s = new SLETridiagonalSolver(L, R);
            s.solve();
            return s.getxR();
        }

        int M = (L.getRowDimension() + nThreads - 1) / nThreads;
        final int P = nThreads;

        Thread[] threads = new Thread[nThreads];
        final SLETridiagonalSolver[] solvers = new SLETridiagonalSolver[nThreads];
        for (int i = 0; i < nThreads; ++i) {
            solvers[i] = new SLETridiagonalSolver(L, R,
                    i * M, Math.min((i + 1) * M, L.getRowDimension()));
            final int fi = i;
            threads[i] = new Thread(() -> {
                solvers[fi].solveSubMatrix();
            });
            threads[i].start();
        }
        joinAll(threads);

        int epsilonD = 2 * (P - 1);
        TridiagonalCompact epsilonM = new TridiagonalCompact(epsilonD);
        VectorM epsilonR = new VectorM(epsilonD);
        generateCoefSLE(epsilonM, epsilonR, solvers, nThreads, M);

        final SLETridiagonalSolver epsilonSolver =
                new SLETridiagonalSolver(epsilonM, epsilonR);
        epsilonSolver.solve();

        for (int i = 0; i < nThreads; ++i) {
            final int fi = i;
            threads[i] = new Thread(() -> {
                double LHcoef = (fi == P - 1 ? 0 : epsilonSolver.getxR().get(fi * 2));
                double UHcoef = (fi == 0 ? 0 : epsilonSolver.getxR().get(fi * 2 - 1));
                solvers[fi].calcFinalSolution(UHcoef, LHcoef);
            });
            threads[i].start();
        }
        joinAll(threads);

        VectorM res = new VectorM(L.getRowDimension());
        for (int i = 0; i < L.getRowDimension(); ++i) {
            res.set(i, solvers[i / M].getxR().get(i % M));
        }

        return res;
    }

    private static void joinAll(Thread[] threads) {
        for (Thread i : threads) {
            try {
                i.join();
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
    }

    private static void generateCoefSLE(TridiagonalCompact L, VectorM R,
                                        SLETridiagonalSolver[] solvers, int P, int M) {
        int length = 2 * (P - 1);
        if (L == null || R == null
                || L.getRowDimension() != length
                || R.getDimension() != length) {
            return;
        }
        L.setB(0, solvers[0].getxLH().get(M - 1));
        L.setC(0, -1);
        R.set(0, -solvers[0].getxR().get(M - 1));
        for (int i = 1; i + 1 < P; ++i) {
            L.setA(i * 2 - 1, -1);
            L.setB(i * 2 - 1, solvers[i].getxUH().get(0));
            L.setC(i * 2 - 1, solvers[i].getxLH().get(0));

            L.setA(i * 2, solvers[i].getxUH().get(M - 1));
            L.setB(i * 2, solvers[i].getxLH().get(M - 1));
            L.setC(i * 2, -1);

            R.set(i * 2 - 1, -solvers[i].getxR().get(0));
            R.set(i * 2, -solvers[i].getxR().get(M - 1));
        }

        L.setA(length - 1, -1);
        L.setB(length - 1, solvers[P - 1].getxUH().get(0));
        R.set(length - 1, -solvers[P - 1].getxR().get(0));
    }
}

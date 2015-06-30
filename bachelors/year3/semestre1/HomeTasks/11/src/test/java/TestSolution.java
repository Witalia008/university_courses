import Jama.Matrix;
import org.junit.Assert;
import org.junit.Test;

/**
 * Created by Witalia on 20.11.2014.
 */
public class TestSolution {
    @Test
    public void testSolution1() throws Exception {
        Matrix L = new Matrix(new double[][]{
                {5, 3, 0, 0},
                {3, 6, 1, 0},
                {0, 1, 4, -2},
                {0, 0, 1, -3}
        });
        VectorM R = new VectorM(new double[]{
                8, 10, 3, -2
        });
        for (int np : new int[] {1, 2, 3, 4}) {
            VectorM x = TridiagonalParallelSolver.solve(L, R, np);
            Assert.assertEquals(x, new VectorM(new double[]{1, 1, 1, 1}));
        }
    }

    @Test
    public void testSolution2() throws Exception {
        Matrix L = new Matrix(new double[][]{
                {1, 2, 0, 0},
                {2, -1, 1, 0},
                {0, 1, -1, 1},
                {0, 0, 1, 1}
        });
        VectorM R = new VectorM(new double[]{
                5, 3, 3, 7
        });
        for (int np : new int[] {1, 2, 3, 4}) {
            VectorM x = TridiagonalParallelSolver.solve(L, R, np);

            Assert.assertEquals(x, new VectorM(new double[]{1, 2, 3, 4}));
        }
    }

    @Test
    public void testSolution3() throws Exception {
        Matrix L = new Matrix(new double[][]{
                {2, 1, 0, 0},
                {2, 3, -1, 0},
                {0, 1, -1, 3},
                {0, 0, 1, -1}
        });
        VectorM R = new VectorM(new double[]{
                4, 9, 12, -4
        });
        for (int np : new int[] {1, 2, 3, 4}) {
            VectorM x = TridiagonalParallelSolver.solve(L, R, np);

            Assert.assertEquals(x, new VectorM(new double[]{1, 2, -1, 3}));
        }
    }

    @Test
    public void testSolution4() throws Exception {
        Matrix L = new Matrix(new double[][]{
                {3, -1, 0, 0, 0, 0, 0, 0},
                {-1, 3, -1, 0, 0, 0, 0, 0},
                {0, -1, 3, -1, 0, 0, 0, 0},
                {0, 0, -1, 3, -1, 0, 0, 0},
                {0, 0, 0, -1, 3, -1, 0, 0},
                {0, 0, 0, 0, -1, 3, -1, 0},
                {0, 0, 0, 0, 0, -1, 3, -1},
                {0, 0, 0, 0, 0, 0, -1, 3}
        });
        VectorM R = new VectorM(new double[]{
            2, 1, 1, 1, 1, 1, 1, 2
        });
        for (int np : new int[] {1, 2, 3, 4, 5, 6, 7, 8}) {
            VectorM x = TridiagonalParallelSolver.solve(L, R, np);

            Assert.assertEquals(x, new VectorM(new double[]{1, 1, 1, 1, 1, 1, 1, 1}));
        }
    }
}

import Jama.Matrix;

/**
 * Created by Witalia on 20.11.2014.
 */
public class Main {
    public static void main(String[] args) {
        Matrix L = new Matrix(new double[][]{
                {1, 2, 0, 0},
                {2, -1, 1, 0},
                {0, 1, -1, 1},
                {0, 0, 1, 1}
        });
        VectorM R = new VectorM(new double[]{
            5, 3, 3, 7
        });
        VectorM x = TridiagonalParallelSolver.solve(L, R, 2);

        outputVector(x);
    }

    public static void outputVector(VectorM v) {
        System.out.print("(");
        for (int i = 0; i < v.getDimension(); i++) {
            System.out.format("%s%.5f", (i > 0 ? ", " : ""), (float)v.get(i));
        }
        System.out.println(")");
    }
}

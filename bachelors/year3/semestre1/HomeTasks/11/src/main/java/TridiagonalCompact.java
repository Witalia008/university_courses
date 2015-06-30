import Jama.Matrix;

/**
 * Created by Witalia on 20.11.2014.
 */
public class TridiagonalCompact {
    private ThreadLocal<Integer> startRow = new ThreadLocal<>();
    private double[] a;
    private double[] b;
    private double[] c;

    public Integer getStartRow() {
        return startRow.get();
    }

    public void setStartRow(Integer startRow) {
        this.startRow.set(startRow);
    }

    private double get(double[] x, int i) {
        if (startRow.get() == null) startRow.set(0);
        i += startRow.get();
        return x[Math.min(i, x.length - 1)];
    }

    public double getA(int i) {
        return get(a, i);
    }

    public double getB(int i) {
        return get(b, i);
    }

    public double getC(int i) {
        return get(c, i);
    }

    public void set(double[] x, int i, double value) {
        if (startRow.get() == null) startRow.set(0);
        i +=  startRow.get();
        x[Math.min(i, x.length - 1)] = value;
    }

    public void setA(int i, double value) {
        set(a, i, value);
    }

    public void setB(int i, double value) {
        set(b, i, value);
    }

    public void setC(int i, double value) {
        set(c, i, value);
    }

    public TridiagonalCompact(Matrix L) {
        this(L.getRowDimension());
        for (int i = 0; i < L.getRowDimension(); i++) {
            if (i > 0) {
                a[i] = L.get(i, i - 1);
            }
            b[i] = L.get(i, i);
            if (i + 1 < L.getRowDimension()) {
                c[i] = L.get(i, i + 1);
            }
        }
    }

    public TridiagonalCompact(int length) {
        startRow.set(0);
        a = new double[length];
        b = new double[length];
        c = new double[length];
    }

    public int getRowDimension() {
        return a.length;
    }
}

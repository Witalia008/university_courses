import Jama.Matrix;

/**
 * Created by Witalia on 20.11.2014.
 */
public class VectorM {
    private ThreadLocal<Integer> startRow = new ThreadLocal();
    private Matrix vector;

    public VectorM(int dimension) {
        vector = new Matrix(1, dimension);
    }

    public VectorM(double[] values) {
        this.vector = new Matrix(new double[][]{values});
    }

    public void setStartRow(Integer startRow1) {
        startRow.set(startRow1);
    }

    public double get(int i) {
        if (startRow.get() == null) {
            startRow.set(0);
        }
        i += startRow.get();
        i = Math.min(i, vector.getColumnDimension() - 1);
        return vector.get(0, i);
    }

    public void set(int i, double value) {
        if (startRow.get() == null) startRow.set(0);
        i += startRow.get();
        i = Math.min(i, vector.getColumnDimension() - 1);
        vector.set(0, i, value);
    }

    public int getDimension() {
        return vector.getColumnDimension();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (obj == this) {
            return true;
        }
        if (!(obj instanceof VectorM)) {
            return false;
        }
        VectorM objV = ((VectorM) obj);
        if (getDimension() != objV.getDimension()) {
            return false;
        }
        double delta = 0;
        for (int i = 0; i < getDimension(); ++i) {
            delta += Math.pow(get(i) - objV.get(i), 2);
        }
        return delta < 1e-3;
    }
}

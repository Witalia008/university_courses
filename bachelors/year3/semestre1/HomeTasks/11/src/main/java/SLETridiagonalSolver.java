import Jama.Matrix;

/**
 * Created by Witalia on 20.11.2014.
 */
public class SLETridiagonalSolver {
    private int startRow;
    private int length;
    private TridiagonalCompact L;
    private VectorM R;
    private VectorM xR;
    private VectorM xUH;
    private VectorM xLH;

    public void setL(TridiagonalCompact l) {
        L = l;
    }

    public VectorM getxR() {
        return xR;
    }

    public VectorM getxUH() {
        return xUH;
    }

    public VectorM getxLH() {
        return xLH;
    }

    public SLETridiagonalSolver(TridiagonalCompact l, VectorM r) {
        L = l;
        R = r;
        length = L.getRowDimension();
    }

    public SLETridiagonalSolver(TridiagonalCompact l, VectorM r, int startRow, int endRow) {
        L = l;
        R = r;
        this.startRow = startRow;
        length = endRow - startRow;
    }

    private boolean isZero(double val) {
        return Math.abs(val) < 1e-7;
    }

    private boolean forwardElimination() {
        if (isZero(L.getB(0))) {
            return false;
        }
        xUH.set(0, L.getC(0) / L.getB(0));                              //xuh(1) = c(1)/b(1)
        xLH.set(0, R.get(0) / L.getB(0));                               //xlh(1) = r(1)/b(1)
        for (int i = 1; i < length; ++i) {
            double denom = L.getB(i) - L.getA(i) * xUH.get(i - 1);      //denom = b(i) - a(i)*xuh(i-1)
            if (isZero(denom)) {
                return false;
            }
            xUH.set(i, L.getC(i) / denom);                              //xuh(i) = c(i)/denom
            xLH.set(i, (R.get(i) - L.getA(i) * xLH.get(i - 1)) / denom);//xlh(i) = (r(i) - a(i)*xlh(i-1))/denom
        }
        return true;
    }

    private boolean backSubstitution() {
        if (isZero(L.getB(length - 1))) {
            return false;
        }
        xR.set(length - 1, xLH.get(length - 1));                        //xr(M) = xlh(M)
        xLH.set(length - 1, -xUH.get(length - 1));                      //xlh(M) = -xuh(M)
        xUH.set(length - 1, L.getA(length - 1) / L.getB(length - 1));   //xuh(M) = a(M)/b(M)
        for (int i = length - 2; i >= 0; --i) {
            xR.set(i, xLH.get(i) - xUH.get(i) * xR.get(i + 1));         //xr(i) = xlh(i) - xuh(i)*xr(i+1)
            xLH.set(i, -xUH.get(i) * xLH.get(i + 1));                   //xlh(i) = -xuh(i)*xlh(i+1)
            double denom = L.getB(i) - L.getC(i) * xUH.get(i + 1);      //denom = b(i) - c(i)*xuh(i+1)
            if (isZero(denom)) {
                return false;
            }
            xUH.set(i, L.getA(i) / denom);                             //xuh(i) = a(i)/denom !!! Probably '-'
        }
        return true;
    }

    private boolean forwardSubstitution() {
        xUH.set(0, -xUH.get(0));                        //xuh(1) = -xuh(1)
        for (int i = 1; i < length; ++i) {
            xUH.set(i, -xUH.get(i) * xUH.get(i - 1));   //xuh(i) = -xuh(i)*xuh(i-1)
        }
        return true;
    }

    public boolean solveSubMatrix() {
        L.setStartRow(startRow);
        R.setStartRow(startRow);
        xLH = new VectorM(length);
        xUH = new VectorM(length);
        xR = new VectorM(length);
        return forwardElimination() && backSubstitution()
                && forwardSubstitution();
    }

    public boolean solve() {
        L.setStartRow(0);
        R.setStartRow(0);
        length = L.getRowDimension();
        return solveSubMatrix();
    }

    public void calcFinalSolution(double UHcoef, double LHcoef) {
        for (int i = 0; i < length; ++i) {
            xR.set(i, xR.get(i) + UHcoef * xUH.get(i) + LHcoef * xLH.get(i));
        }
    }
}

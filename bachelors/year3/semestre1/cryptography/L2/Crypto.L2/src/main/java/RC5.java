import java.util.Arrays;

/**
 * Created by Witalia on 11.11.2014.
 */
public class RC5 {
    private byte[] key;
    private int w;
    private long Pw;
    private long Qw;
    private int r;
    private long[] S;
    private long[] L;

    /*
     * Magic constants:
     * Pw = Odd((e - 2) * 2**W)
     * Qw = Odd((phi - 1) * 2**W)
     */
    private static final long P_16 = 0xb7e1L;
    private static final long Q_16 = 0x9e37L;
    private static final long P_32 = 0xb7e15163L;
    private static final long Q_32 = 0x9e3779b9L;
    private static final long P_64 = 0xb7e151628aed2a6bL;
    private static final long Q_64 = 0x9e3779b97f4a7c15L;

    public RC5(byte[] key, int w, int r) {
        this.key = key;
        this.w = w;
        this.r = r;
        selectConstants();
        convertKey();
        initSArray();
        mixSecretKey();
    }

    private void selectConstants() {
        switch (w) {
            case 16:
                Pw = P_16; Qw = Q_16;
                break;
            case 32:
                Pw = P_32; Qw = Q_32;
                break;
            case 64:
                Pw = P_64; Qw = Q_64;
                break;
            default:
                System.out.println("Wrong word length");
        }
    }

    private long addBase(long a, long b) {
        if (w == 64) {
            return a + b;
        }
        return (a + b) & ((1L << w) - 1);
    }

    private void convertKey() {
        if (key == null) {
            return;
        }
        int u = w / 8;
        int c = (key.length + u - 1) / u;
        L = new long[c];
        for (int i = key.length - 1; i >= 0; i--) {
            L[i / u] = (L[i / u] << 8) + key[i];
        }
    }

    private void initSArray() {
        if (Pw == 0 || Qw == 0) {
            return;
        }
        int t = 2 * (r + 1);
        S = new long[t];
        S[0] = Pw;
        for (int i = 1; i < S.length; i++) {
            S[i] = addBase(S[i - 1], Qw);
        }
    }

    private long rotateLeft(long number, long nPos) {
        nPos %= w;
        return (number << nPos) | (number >>> (w - nPos));
    }

    private long rotateRight(long number, long nPos) {
        nPos %= w;
        return (number >>> nPos) | (number << (w - nPos));
    }

    private void mixSecretKey() {
        if (S == null || L == null) {
            return;
        }
        long a = 0;
        long b = 0;
        for (int i = 0, j = 0, c = 0;
             c < 3 * Math.max(L.length, S.length);
                i = (i + 1) % S.length,
                j = (j + 1) % L.length, c++) {
            a = S[i] = rotateLeft(addBase(S[i], addBase(a, b)), 3);
            b = L[j] = rotateLeft(addBase(L[j], addBase(a, b)), addBase(a, b));
        }
    }

    private void fromLong(long value, byte[] res) {
        Arrays.fill(res, (byte) 0);
        for (int i = res.length - 1; i >= 0; i--) {
            res[i] = (byte) (value & 0xff);
            value >>>= 8;
        }
    }

    private long fromByteArr(byte[] val) {
        long res = 0;
        for (int i = 0; i < val.length; i++) {
            long curVal = (val[i] + 256) % 256;
            res = (res << 8) | curVal;
        }
        return res;
    }

    public void encrypt(byte[] a, byte[] b) {
        if (b.length != w / 8 || a.length != w / 8) {
            return;
        }
        long A = addBase(fromByteArr(a), S[0]);
        long B = addBase(fromByteArr(b), S[1]);
        for (int i = 1; i <= r; ++i) {
            A = addBase(rotateLeft(A ^ B, B), S[i * 2]);
            B = addBase(rotateLeft(B ^ A, A), S[i * 2 + 1]);
        }
        fromLong(A, a);
        fromLong(B, b);
    }

    public void decrypt(byte[] a, byte[] b) {
        if (b.length != w / 8 || a.length != w / 8) {
            return;
        }
        long A = fromByteArr(a);
        long B = fromByteArr(b);
        for (int i = r; i > 0 ; --i) {
            B = rotateRight(addBase(B, -S[i * 2 + 1]), A) ^ A;
            A = rotateRight(addBase(A, -S[i * 2]), B) ^ B;
        }
        fromLong(addBase(A, -S[0]), a);
        fromLong(addBase(B, -S[1]), b);
    }
}

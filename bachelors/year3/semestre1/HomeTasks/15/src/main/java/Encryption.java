import java.io.IOException;
import java.util.Arrays;

/**
 * Created by Witalia on 14.11.2014.
 */
public class Encryption {
    public static int encrypt(int b) {
        return b ^ 24;
    }
    public static int decrypt(int b) {
        return encrypt(b);
    }
    public static byte[] encrypt(byte[] b) {
        byte[] res = new byte[b.length];
        for (int i = 0; i < res.length; i++) {
            res[i] = (byte) encrypt(b[i]);
        }
        return res;
    }
    public static byte[] decrypt(byte[] b) {
        return encrypt(b);
    }
    public static byte[] encrypt(byte[] b, int off, int len)
            throws IOException {
        if (off + len > b.length || off < 0) {
            throw new IOException("Index out of bounds");
        }
        return encrypt(Arrays.copyOfRange(b, off, off + len));
    }
    public static byte[] decrypt(byte[] b, int off, int len)
            throws IOException {
        return encrypt(b, off, len);
    }
}

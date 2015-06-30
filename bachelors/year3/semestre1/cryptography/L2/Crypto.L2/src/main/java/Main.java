import java.util.Arrays;

/**
 * Created by Witalia on 11.11.2014.
 */

public class Main {
    private static byte[] A = {1, 2, 3, 4};
    private static byte[] B = {5, 6, 7, 8};

    public static void main(String[] args) {
        byte[] key = {0x20, (byte) 0xfc, 0x3f, 0x12, 0x00, 0x34};
        int w = 32;
        byte[] a = "Hell".getBytes();
        byte[] b = "o!!!".getBytes();
        RC5 rc5Alg = new RC5(key, w, 10);
        System.out.print(new String(a));
        System.out.println(new String(b));

        rc5Alg.encrypt(a, b);
        System.out.print(new String(a));
        System.out.println(new String(b));

        rc5Alg.decrypt(a, b);
        System.out.print(new String(a));
        System.out.println(new String(b));
    }
}

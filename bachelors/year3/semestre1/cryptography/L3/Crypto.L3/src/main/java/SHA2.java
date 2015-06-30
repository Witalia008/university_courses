import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.BitSet;

/**
 * Created by Witalia on 24.11.2014.
 */
public class SHA2 {
    /**
     * Initialize hash values
     * (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
     */
    private static final int[] H = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    /**
     * Initialize array of round constants:
     * (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
     */
    private static final int[] k = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    public byte[] sha256(byte[] m) {
        // #region Pre-processing

        long length = ((m.length + 9 + 63) / 64) * 64;

        byte[] M = Arrays.copyOf(m, (int) length);
        // append the bit '1' to the message
        M[m.length] = (byte) 0x80;

        /* append length of message in bits, as 64-bit big-endian integer */
        length = m.length * 8;
        for (int i = 0; i < 8; ++i) {
            M[M.length - i - 1] = (byte) (length >>> (i * 8));
        }
//        System.out.println(Arrays.toString(M));

        // #endregion Pre-processing

        int[] h = H.clone();
        // #region Process the message in successive 512-bit chunks:
        for (int chunkN = 0; chunkN < M.length / 64; ++chunkN) {
            /*create a 64-entry message schedule array w[0..63] of 32-bit words
              (The initial values in w[0..63] don't matter) */
            int[] w = new int[64];
            // copy chunk into first 16 words w[0..15] of the message schedule array
            copyChunk(M, w, chunkN * 64);

            //Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
            extendMSA(w);

//            System.out.println(Arrays.toString(w));

            // Initialize working variables to current hash value:
            int[] ww = h.clone();
            // Compression function main loop:
            for (int i = 0; i < 64; ++i) {
                // S1 := (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
                int s1 = rotateRight(ww[4], 6) ^
                         rotateRight(ww[4], 11) ^
                         rotateRight(ww[4], 25);
                // ch := (e and f) xor ((not e) and g)
                int ch = (ww[4] & ww[5]) ^ ((~ww[4]) & ww[6]);
                int temp1 = ww[7] + s1 + ch + k[i] + w[i];
                // S0 := (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
                int s0 = rotateRight(ww[0], 2) ^
                         rotateRight(ww[0], 13) ^
                         rotateRight(ww[0], 22);
                // maj := (a and b) xor (a and c) xor (b and c)
                int maj = (ww[0] & ww[1]) ^ (ww[0] & ww[2]) ^ (ww[1] & ww[2]);
                int temp2 = s0 + maj;

                updateWorkingVariables(ww, temp1, temp2);
            }


            //Add the compressed chunk to the current hash value:
            for (int i = 0; i < 8; ++i) {
                h[i] += ww[i];
            }
        }
        // #endregion Process

        ByteBuffer bb = ByteBuffer.allocate(32);
        for (int i = 0; i < 8; ++i) {
            bb.putInt(i * 4, h[i]);
        }
        return bb.array();
    }

    private void updateWorkingVariables(int[] ww, int temp1, int temp2) {
        for (int j = 7; j > 0; --j) {
            ww[j] = ww[j - 1];
        }
        ww[4] += temp1;
        ww[0] = temp1 + temp2;
    }

    private void extendMSA(int[] w) {
        for (int i = 16; i < 64; ++i) {
            int s0 = rotateRight(w[i - 15], 7) ^
                    rotateRight(w[i - 15], 18) ^
                    (w[i - 15] >>> 3);
            int s1 = rotateRight(w[i - 2], 17) ^
                    rotateRight(w[i - 2], 19) ^
                    (w[i - 2] >>> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
    }

    int rotateRight(int a, int x) {
        x %= 32;
        return (a >>> x) | (a << (32 - x));
    }

    private void copyChunk(byte[] M, int[] w, int offset) {
        for (int i = 0; i < 16; ++i) {
            w[i] = 0;
            for (int j = 0; j < 4; ++j) {
                int val = (M[offset + i * 4 + j] + 0x100) & 0xff;
                w[i] = ((w[i] << 8) | val);
            }
        }
    }

    public byte[] sha256(String m) {
        return sha256(m.getBytes());
    }

    static public String toHex(byte[] b) {
        final char[] digits = "0123456789ABCDEF".toCharArray();
        char[] res = new char[b.length * 2];
        for (int i = 0; i < b.length; i++) {
            int v = b[i] & 0xFF;
            res[i * 2] = digits[v >>> 4];
            res[i * 2 + 1] = digits[v & 0xf];
        }
        return new String(res);
    }
}

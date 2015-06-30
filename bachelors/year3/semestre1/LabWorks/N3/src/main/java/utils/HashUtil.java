package utils;

import org.apache.commons.codec.binary.Base64;
import org.apache.log4j.Logger;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * HashUtil class is for hashing strings with
 * different algorithms
 * Created by Witalia on 18.11.2014.
 */
public class HashUtil {
    private static Logger logger = Logger.getLogger(HashUtil.class);
    /**
     * Arrays for converting integers into hex digits.
     */
    protected static final char[] hexArray =
            "0123456789ABCDEF".toCharArray();

    /**
     * MessageDigest for hashing strings.
     */
    protected MessageDigest md;

    /**
     * Private constructor to forbid creating of objects
     */
    private HashUtil() {}

    /**
     * Creates object of HashUtil class with initialized MessageDigest
     * @param algName name of hashing algorithm
     * @return object of HashUtil class for future use with {@Link algName}
     * @throws NoSuchAlgorithmException if such algorithm doesn't exist
     */
    public static HashUtil forAlg(String algName)
            throws NoSuchAlgorithmException {
        HashUtil res = new HashUtil();
        res.md = MessageDigest.getInstance(algName);
        return res;
    }

    /**
     * Calculates hash of a string with specific algorithm.
     * @param str target of hashing
     * @return hash of a string
     */
    public String hashString(String str) {
        md.reset();
        md.update(str.getBytes());
        byte[] out = md.digest();
        return bytesToHex(out);
    }

    /**
     * Converts sequence of bytes into Hex string
     * @param out array of bytes to convert
     * @return string representation
     */
    public String bytesToHex(byte[] out) {
        char[] res = new char[out.length * 2];
        for (int i = 0; i < out.length; i++) {
            int cur = out[i] & 0xff;
            res[i * 2] = hexArray[cur >> 4];
            res[i * 2 + 1] = hexArray[cur & 0xf];
        }
        return new String(res);
    }

    /**
     * Encrypts string with base64 cipher
     * @param str plain text
     * @return cipher text
     */
    public static String base64(String str) {
        return new String(Base64.encodeBase64(str.getBytes()));
    }
}

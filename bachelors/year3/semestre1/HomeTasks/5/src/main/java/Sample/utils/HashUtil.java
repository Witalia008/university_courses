package Sample.utils;

import org.apache.commons.codec.binary.Base64;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Created by Witalia on 18.11.2014.
 */
public class HashUtil {
    protected static final char[] hexArray =
            "0123456789ABCDEF".toCharArray();

    protected MessageDigest md;

    public static HashUtil forAlg(String algName)
            throws NoSuchAlgorithmException {
        HashUtil res = new HashUtil();
        res.md = MessageDigest.getInstance(algName);
        return res;
    }

    public String hashString(String str) {
        md.reset();
        md.update(str.getBytes());
        byte[] out = md.digest();
        return bytesToHex(out);
    }

    public String bytesToHex(byte[] out) {
        char[] res = new char[out.length * 2];
        for (int i = 0; i < out.length; i++) {
            int cur = out[i] & 0xff;
            res[i * 2] = hexArray[cur >> 4];
            res[i * 2 + 1] = hexArray[cur & 0xf];
        }
        return new String(res);
    }

    public static String base64(String str) {
        return new String(Base64.encodeBase64(str.getBytes()));
    }
}

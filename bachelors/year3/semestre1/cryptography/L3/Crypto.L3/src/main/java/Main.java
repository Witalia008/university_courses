import org.apache.commons.codec.binary.Base64;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

/**
 * Created by Witalia on 24.11.2014.
 */
public class Main {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String s = "Hello, world!";
        System.out.println(SHA2.toHex(new SHA2().sha256(s)));
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        System.out.println(SHA2.toHex(md.digest(s.getBytes())));
    }
}
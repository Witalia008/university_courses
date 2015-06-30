package Sample.utils;

import Sample.utils.HashUtil;

import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

/**
 * Created by Witalia on 17.11.2014.
 */
public class User {
    protected static final char[] SYBM =
            "0123456789QWERTYUIOPLKJHGFDSAZXCVBNM".toCharArray();
    protected static final String STATIC_SALT = "j9g7zZEG";
    protected static final int ITER_COUNT = 1000;
    protected static final SecureRandom random = new SecureRandom();

    protected String password;

    public String getUsername() {
        return username;
    }

    public String getPassHash() {
        return passHash;
    }

    public String getSalt() {
        return salt;
    }

    protected String username;
    protected String passHash;
    protected String salt;

    protected static HashUtil hashUtil;
    static {
        try {
            hashUtil = HashUtil.forAlg("SHA-256");
        } catch (NoSuchAlgorithmException ex) {
            ex.printStackTrace();
        }
    }

    public User(String username, String password) {
        this.password = password;
        this.username = username;
    }

    public void setSalt(String salt) {
        this.salt = salt;
    }

    public void setSalt() {
        setSalt(getRandomSalt(random.nextInt(25) + 8));
    }

    public void hashPass() {
        if (salt == null) {
            return;
        }
        String passStr = password + STATIC_SALT + salt;
        for (int i = 0; i < ITER_COUNT; ++i) {
            passStr = hashUtil.hashString(passStr);
        }
        passHash = hashUtil.base64(passStr);
    }

    public static String getRandomSalt(int length) {
        char[] byteArr = new char[length];
        for (int i = 0; i < byteArr.length; i++) {
            byteArr[i] = SYBM[random.nextInt(SYBM.length)];
        }
        return new String(byteArr);
    }

}

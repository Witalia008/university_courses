package ents;

import org.apache.log4j.Logger;
import utils.HashUtil;

import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

/**
 * Class that represents User entity and
 * supports hashing of passwords for use in database.
 * Created by Witalia on 17.11.2014.
 */
public class User {
    private static Logger logger = Logger.getLogger(User.class);
    /**
     * Possible symbols for random generation of SALT
     */
    protected static final char[] SYBM =
            "0123456789QWERTYUIOPLKJHGFDSAZXCVBNM".toCharArray();
    /**
     * Static salt for protection against rainbow-table attacks.
     */
    protected static final String STATIC_SALT = "j9g7zZEG";
    /**
     * Number of iterations of hash algorithm.
     * For protection against brute force attacks.
     */
    protected static final int ITER_COUNT = 1000;
    /**
     * For better random generation of salt.
     */
    protected static final SecureRandom random = new SecureRandom();

    /** Getters */
    public String getUsername() {
        return username;
    }

    public String getPassHash() {
        return passHash;
    }

    public String getSalt() {
        return salt;
    }

    public int getId() {
        return id;
    }

    /** Setters */

    public void setId(int id) {
        this.id = id;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassHash(String passHash) {
        this.passHash = passHash;
    }

    /**
     * Sets dynamic salt as {@Link salt}
     * @param salt
     */
    public void setSalt(String salt) {
        this.salt = salt;
    }


    protected int id;
    protected String password;
    protected String username;
    protected String passHash;
    /**
     * With dynamic salt when one salt is exposed,
     * it doesn't put all database in danger.
     */
    protected String salt;

    /**
     * Util for hashing password. Uses SHA-256 algorithm.
     */
    protected static HashUtil hashUtil;
    static {
        try {
            hashUtil = HashUtil.forAlg("SHA-256");
        } catch (NoSuchAlgorithmException ex) {
            logger.error("SHA-256 hashing alg is not supported", ex);
        }
    }

    public User() {    }

    /**
     * Constructor
     * @param username User's name
     * @param password Not-encrypted password
     */
    public User(String username, String password) {
        this.password = password;
        this.username = username;
    }

    /**
     * Set dynamic salt as some random sequence.
     * It will have between 8 and 32 characters.
     */
    public void setSalt() {
        setSalt(getRandomSalt(random.nextInt(25) + 8));
    }

    /**
     * Encrypt user's password
     */
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

    /**
     * Generate random salt with length {@Link length}
     * using characters {@Link SYBM}
     * @param length length of desired salt
     * @return random salt
     */
    public static String getRandomSalt(int length) {
        char[] byteArr = new char[length];
        for (int i = 0; i < byteArr.length; i++) {
            byteArr[i] = SYBM[random.nextInt(SYBM.length)];
        }
        return new String(byteArr);
    }

}

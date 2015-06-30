import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PipedInputStream;
import java.util.Arrays;
import java.util.Random;

/**
 * Created by Witalia on 14.11.2014.
 */
public class TestEncryptionStreams {
    Random random = new Random();

    @Test
    public void testEncryption() throws Exception {
        int off = 30;
        int len = 40;
        byte[] b = new byte[100];
        random.nextBytes(b);
        byte[] a = Encryption.encrypt(b, off, len);
        byte[] c = Encryption.decrypt(a);
        Assert.assertArrayEquals(c, Arrays.copyOfRange(b, off, len + off));
    }

    @Test
    public void testStreams() throws Exception {
        byte[] b = new byte[100];
        random.nextBytes(b);
        EncryptOutputStream out = new EncryptOutputStream(new FileOutputStream("test"));
        out.write(b);
        out.close();
        DecryptInputStream in = new DecryptInputStream(new FileInputStream("test"));
        byte[] a = new byte[100];
        in.read(a);
        in.close();
        Assert.assertArrayEquals(a, b);
        new File("test").delete();
    }
}

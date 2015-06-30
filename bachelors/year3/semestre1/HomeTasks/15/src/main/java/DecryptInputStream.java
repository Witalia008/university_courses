import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

/**
 * Created by Witalia on 14.11.2014.
 */
public class DecryptInputStream extends FilterInputStream {
    public DecryptInputStream(InputStream in) {
        super(in);
    }

    @Override
    public int read() throws IOException {
        int res = super.read();
        if (res != -1) {
            res = Encryption.decrypt(res);
        }
        return res;
    }

    @Override
    public int read(byte[] b) throws IOException {
        return read(b, 0, b.length);
    }

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        int res = super.read(b, off, len);
        System.arraycopy(Encryption.decrypt(b, off, len), 0, b, off, res);
        return res;
    }
}

import java.io.FilterOutputStream;
import java.io.IOException;
import java.io.OutputStream;

/**
 * Created by Witalia on 14.11.2014.
 */
public class EncryptOutputStream extends FilterOutputStream {
    public EncryptOutputStream(OutputStream out) {
        super(out);
    }

    @Override
    public void write(int b) throws IOException {
        super.write(Encryption.encrypt(b));
    }
}

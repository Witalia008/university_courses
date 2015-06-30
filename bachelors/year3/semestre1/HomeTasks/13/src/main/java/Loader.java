import java.io.*;

/**
 * Created by Witalia on 13.10.2014.
 */
public class Loader extends ClassLoader {
    private String pathToBin;

    public Loader(ClassLoader parent, String pathToBin) {
        super(parent);
        this.pathToBin = pathToBin;
    }

    @Override
    public Class<?> findClass(String className)
            throws ClassNotFoundException {
        try {
            byte[] byteCode = fetchClassFromFS(pathToBin + className + ".class");
            System.out.println("Loading by my loader\n");
            return defineClass(className, byteCode, 0, byteCode.length);
        } catch (IOException ex) {
            System.out.println("Loading by standard loader\n");
            return super.findSystemClass(className);
        }
    }

    private byte[] fetchClassFromFS(String path)
            throws IOException {
        File file = new File(path);
        InputStream is = new FileInputStream(file);

        long length = file.length();

        if (length > Integer.MAX_VALUE) {
            throw new IOException("File " + path + " is too large");
        }

        byte[] bytes = new byte[(int) length];

        int offset = 0;
        for (; offset < length;) {
            offset += Math.max(is.read(bytes, offset, bytes.length - offset), 0);
        }

        if (offset < length) {
            throw new IOException("Could not completely load file " + path);
        }
        is.close();
        return bytes;
    }
}

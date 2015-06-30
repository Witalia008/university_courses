import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * Created by Witalia on 23.10.2014.
 */
public class ServerClient {
    protected Socket clientSocket;
    protected ObjectOutputStream objectOutputStream;
    protected ObjectInputStream objectInputStream;

    public void init()
            throws IOException {
        if (clientSocket != null) {
            objectOutputStream = new ObjectOutputStream(
                    clientSocket.getOutputStream());
            objectInputStream = new ObjectInputStream(
                    clientSocket.getInputStream());
        }
    }
    public void clear()
            throws IOException {
        if (objectInputStream != null) {
            objectInputStream.close();
        }
        if (objectOutputStream != null) {
            objectOutputStream.close();
        }
    }

    @Override
    protected void finalize() throws Throwable {
        clear();
        super.finalize();
    }
    public void sendObject(Object object)
            throws IOException, NullPointerException {
        objectOutputStream.writeObject(object);
    }
    public Object receiveObject()
            throws IOException, ClassNotFoundException, NullPointerException {
        return objectInputStream.readObject();
    }
}

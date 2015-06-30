import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by Witalia on 23.10.2014.
 */
public class Server extends ServerClient {
    private ServerSocket serverSocket;

    public static void main(String[] args) {
        Server server = new Server();
        Employee employee = null;

        try {
            server.init(27015);

            employee = (Employee) server.receiveObject();
            System.out.println(employee);

            employee.setName("BrandNewName");
            employee.setNumber(666);
            System.out.println(employee);

            server.sendObject(employee);

        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void init(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        System.out.println("Waiting...");
        clientSocket = serverSocket.accept();
        super.init();
    }
}

import java.io.IOException;
import java.net.Socket;

/**
 * Created by Witalia on 23.10.2014.
 */
public class Client extends ServerClient {

    public static void main(String[] args) {
        Client client = new Client();
        Employee employee = new Employee(10, "Vasia");
        System.out.println(employee);

        try {
            client.init("127.0.0.1", 27015);
            client.sendObject(employee);
            employee = (Employee) client.receiveObject();

            System.out.println(employee);
        } catch (IOException | ClassNotFoundException ex) {
            ex.printStackTrace();
        }
    }

    public void init(String address, int port) throws IOException {
        clientSocket = new Socket(address, port);
        super.init();
    }
}

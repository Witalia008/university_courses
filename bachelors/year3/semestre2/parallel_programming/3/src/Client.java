import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    public Client(String ip, int port) throws IOException {
        sock = new Socket(ip, port);
        in = new BufferedReader(
                new InputStreamReader(sock.getInputStream()));
        out = new PrintWriter(sock.getOutputStream(), true);
    }

    public String sendQuery(String query) throws IOException {
        out.println(query);
        return in.readLine();
    }

    public static void main(String[] args) throws IOException {
        Client client = new Client("localhost", 12345);

        System.out.println(client.sendQuery("1#5#Vegetables"));
        System.out.println(client.sendQuery("2#2"));
        System.out.println(client.sendQuery("3#10#Cabbage#1.1#10#0#5"));
        System.out.println(client.sendQuery("4#1"));
        System.out.println(client.sendQuery("5#10#~#1.2#~#~#~"));//Change price
        System.out.println(client.sendQuery("6#3"));
        System.out.println(client.sendQuery("7#Snickers"));
        System.out.println(client.sendQuery("8#3"));
        System.out.println(client.sendQuery("9"));

        client.disconnect();
    }

    private void disconnect() throws IOException {
        sock.close();
    }
}
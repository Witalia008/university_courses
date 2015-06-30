import ents.Product;
import ents.Stock;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;

public class Server {
    private ServerSocket server = null;
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;
    private Stock stock = null;

    public void start(int port) throws IOException {
        server = new ServerSocket(port);
        stock = new Stock();
        while (true) {
            stock.loadFromFile("data\\grocery.xml");
            sock = server.accept();
            in = new BufferedReader(
                    new InputStreamReader(sock.getInputStream()));
            out = new PrintWriter(sock.getOutputStream(), true);
            while (processQuery());
            stock.saveToFile("data\\grocery1.xml");
        }
    }

    private boolean processQuery() {
        try {
            String query = in.readLine();
            if (query == null) {
                return false;
            }
            String[] params = query.split("#");
            for (int i = 0; i < params.length; i++) {
                if (params[i].equals("~")) {
                    params[i] = null;
                }
            }
            System.out.println(Arrays.toString(params));
            try {
                switch (params[0]) {
                    case "1":
                        stock.addCategory(Integer.parseInt(params[1]), params[2]);
                        out.println("0#Category added");
                        break;
                    case "2":
                        stock.deleteCategory(Integer.parseInt(params[1]));
                        out.println("0#Category deleted");
                        break;
                    case "3":
                        stock.addProduct(
                                Integer.parseInt(params[1]),
                                params[2],
                                Double.parseDouble(params[3]),
                                Integer.parseInt(params[4]),
                                Integer.parseInt(params[5]),
                                Integer.parseInt(params[6])
                        );
                        out.println("0#Product added");
                        break;
                    case "4":
                        stock.deleteProduct(Integer.parseInt(params[1]));
                        out.println("0#Product deleted");
                        break;
                    case "5":
                        stock.changeProduct(Integer.parseInt(params[1]),
                                new Product(params[2], params[3], params[4], params[5], params[6]));
                        out.println("0#Product changed");
                        break;
                    case "6":
                        int cnt = stock.productsInCategory(Integer.parseInt(params[1]));
                        out.println(cnt == -1 ? "2#No such category" : "0#Count in category#" + cnt);
                        break;
                    case "7":
                        out.println("0#Product by name#" + stock.getProduct(params[1]));
                        break;
                    case "8":
                        out.println("0#Product by category#" + stock.getProducts(Integer.parseInt(params[1])));
                        break;
                    case "9":
                        out.println("0#Categories#" + stock.getCategory());
                        break;
                }
            } catch (Throwable e) {
                e.printStackTrace();
                out.println("1#" + e.getMessage());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    public static void main(String[] args) {
        try {
            Server srv = new Server();
            srv.start(12345);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
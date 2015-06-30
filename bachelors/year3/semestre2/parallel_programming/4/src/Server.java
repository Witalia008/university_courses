import ents.Stock;

import java.net.MalformedURLException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Server {
    public static void main(String[] args) throws RemoteException, MalformedURLException {
        Stock stock = new Stock();
        stock.loadFromFile("data\\grocery.xml");
        Registry r = LocateRegistry.createRegistry(1099);
        r.rebind("Stock", stock);
    }
}

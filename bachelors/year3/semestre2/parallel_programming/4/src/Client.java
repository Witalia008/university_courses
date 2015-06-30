import ents.Product;
import rmt.StockIntf;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Client {
    public static void main(String[] args) throws Exception {
        StockIntf stock = (StockIntf) Naming.lookup("//127.0.0.1/Stock");

        stock.addCategory(4, "Vegetables");
        stock.deleteCategory(2);
        stock.addProduct(10, "Cabbage", 1.1, 10, 0, 4);
        stock.deleteProduct(1);
        stock.changeProduct(10, new Product(null, null, null, null, "1.2"));
        System.out.println(stock.productsInCategory(3));
        System.out.println(stock.getProduct("Snickers"));
        System.out.println(stock.getProducts(3));
        System.out.println(stock.getCategory());
    }
}

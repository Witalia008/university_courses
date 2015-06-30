package rmt;

import ents.Category;
import ents.Product;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

/**
 * Created by Witalia on 25.03.2015.
 */
public interface StockIntf extends Remote {
    public void addCategory(int id, String name) throws RemoteException;
    public void deleteCategory(int id) throws Exception;
    public void addProduct(
            int id, String name, double price,
            int count, int fat, int catID) throws Exception;
    public void deleteProduct(int id) throws Exception;
    public void changeProduct(int id, Product p) throws Exception;
    public int productsInCategory(int id) throws RemoteException;
    public Product getProduct(String param) throws RemoteException;
    public List<Product> getProducts(int catID) throws RemoteException;
    public List<Category> getCategory() throws RemoteException;
}

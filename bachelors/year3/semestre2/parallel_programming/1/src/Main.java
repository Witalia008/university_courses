import ents.Category;
import ents.Product;
import ents.Stock;

/**
 * Created by Witalia on 24.03.2015.
 */
public class Main {

    public static void main(String[] args) throws Exception {
        Stock stock = new Stock();
        stock.loadFromFile("data\\grocery.xml");

        stock.addCategory(4, "Vegetables");
        stock.addProduct(10, "Cabbage", 1.2, 10, 0, 4);

        System.out.println(stock.getCategory(3));
        System.out.println(stock.getProduct(10));
        stock.deleteCategory(3);
        stock.deleteProduct(4);
        stock.changeCategory(1, new Category(null, "NoName"));
        stock.changeProduct(3, new Product(null, "10", null, null, null));
        stock.addCategory(1, null);

        System.out.println(stock.getCategory());
        System.out.println(stock.getCategory(1).getProduct());

        stock.saveToFile("data\\grocery1.xml");
    }
}

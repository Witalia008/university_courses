import java.sql.*;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Main {
    private Connection connection;

    public Main() throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.jdbc.Driver");
        connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/STOCK",
                "user",
                "password"
        );
    }

    public boolean addCategory(String name) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO categories VALUES (default, ?)"
            );
            statement.setString(1, name);
            statement.executeUpdate();
            System.out.println("Category " + name + " added");
            return true;
        } catch (SQLException e) {
            System.out.println("Error. Category " + name + " not added");
            e.printStackTrace();
        }
        return false;
    }

    public boolean deleteCategory(int id) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "DELETE FROM categories WHERE ID_CAT=?"
            );
            statement.setInt(1, id);
            int count = statement.executeUpdate();
            if (count > 0) {
                System.out.println("Category #" + id + " deleted");
                return true;
            } else {
                System.out.println("Category #" + id + " not found");
            }
        } catch (SQLException e) {
            System.out.println("Error while deleting category #" + id);
            e.printStackTrace();
        }
        return false;
    }

    public boolean addProduct(int catID, String name, int count, double price, int fat) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO products VALUES (?, default, ?, ?, ?, ?)"
            );
            statement.setInt(1, catID);
            statement.setString(2, name);
            statement.setInt(3, count);
            statement.setDouble(4, price);
            statement.setInt(5, fat);
            statement.executeUpdate();
            System.out.println("Product " + name + " added");
            return true;
        } catch (SQLException e) {
            System.out.println("Error: Product " + name + " not added");
            e.printStackTrace();
        }
        return false;
    }

    public boolean deleteProduct(int id) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "DELETE FROM products WHERE ID_PROD=?"
            );
            statement.setInt(1, id);
            int count = statement.executeUpdate();
            if (count > 0) {
                System.out.println("Product #" + id + " deleted");
                return true;
            } else {
                System.out.println("Product #" + id + " not found");
            }
        } catch (SQLException e) {
            System.out.println("Error while deleting product #" + id);
            e.printStackTrace();
        }
        return false;
    }

    public void showAllCategories() {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM categories"
            );
            ResultSet res = statement.executeQuery();
            System.out.println("All categories:");
            while (res.next()) {
                System.out.println(res.getInt(1) + " " + res.getString(2));
            }
            res.close();
        } catch (SQLException e) {
            System.out.println("Error while getting list of categories");
            e.printStackTrace();
        }
    }

    public void showProductsForCategory(int catID) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM products WHERE ID_CAT=?"
            );
            statement.setInt(1, catID);
            ResultSet res = statement.executeQuery();
            System.out.println("All products for category #" + catID + ":");
            while (res.next()) {
                System.out.println(
                        res.getInt(2) + " "
                        + res.getString(2) + " "
                        + res.getInt(3) + " "
                        + res.getDouble(4) + " "
                        + res.getInt(5));
            }
            res.close();
        } catch (SQLException e) {
            System.out.println("Error while getting list of products");
            e.printStackTrace();
        }
    }

    public void findProduct(int id) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM products WHERE ID_PROD=?"
            );
            statement.setInt(1, id);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                System.out.println(
                        res.getInt(2) + " "
                        + res.getString(2) + " "
                        + res.getInt(3) + " "
                        + res.getDouble(4) + " "
                        + res.getInt(5));
            }
            res.close();
        } catch (SQLException e) {
            System.out.println("Error while finding product #" + id);
            e.printStackTrace();
        }
    }

    public void findCategory(int id) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM categories WHERE ID_CAT=?"
            );
            statement.setInt(1, id);
            ResultSet res = statement.executeQuery();
            while (res.next()) {
                System.out.println(
                        res.getInt(2) + " "
                        + res.getString(2));
            }
            res.close();
        } catch (SQLException e) {
            System.out.println("Error while finding category #" + id);
            e.printStackTrace();
        }
    }

    public boolean changeCategory(int id, String newName) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "UPDATE categories SET NAME=? WHERE ID_CAT=?"
            );
            statement.setString(1, newName);
            statement.setInt(2, id);
            statement.executeUpdate();
            System.out.println("Category #" + id + " updated");
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Main m = new Main();
        m.showAllCategories();
        m.addCategory("Beverages");
        m.deleteCategory(1);
        m.deleteCategory(2);
        m.changeCategory(4, "Snacks1");
        m.showAllCategories();
        m.addProduct(1, "a", 1, 1, 1);
        m.addProduct(3, "a", 1, 1, 1);
    }

    @Override
    protected void finalize() throws Throwable {
        connection.close();
    }
}

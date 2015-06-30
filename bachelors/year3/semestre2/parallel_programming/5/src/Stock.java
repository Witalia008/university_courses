import java.sql.*;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Stock {
    private Connection connection;

    public Stock() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/STOCK",
                    "user", "password"
            );
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }

    public void close() {
        try {
            connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
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

    public boolean addProduct(String name, double price, int count, int fat, int catID) {
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

    public String getProducts(int id) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM products WHERE ID_CAT=?"
            );
            statement.setInt(1, id);
            ResultSet res = statement.executeQuery();
            StringBuilder result = new StringBuilder();
            while (res.next()) {
                result.append(
                        res.getInt(2) + "#"
                        + res.getString(3) + "#"
                        + res.getInt(4) + "#"
                        + res.getDouble(5) + "#"
                        + res.getInt(6) + "#"
                );
            }
            res.close();
            return result.toString();
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }

    }

    public String getCategory() {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM categories"
            );
            ResultSet res = statement.executeQuery();
            StringBuilder result = new StringBuilder();
            while (res.next()) {
                result.append(
                        res.getInt(1) + "#"
                        + res.getString(2) + "#");
            }
            res.close();
            return result.toString();
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }
}
